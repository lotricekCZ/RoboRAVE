#include <Arduino.h>
#include <Wire.h>

//~ #include "motorduino_logic.h"

void logic::read(){
//Serial.println("N/A");
	if(Serial.available() != 0){ // read if there is something to read
		uint8_t read = Serial.read();
		internal_serial_buf[index] = read;
	    uint8_t ri = index + 1;
	    ri = (ri < msg_std::length? ri: 0);
		if(internal_serial_buf[index] == msg_std::end){
			if(internal_serial_buf[ri] == msg_std::start){				
				for(uint8_t i = ri; i < msg_std::length; i++){
					main_chat -> buffer[i - ri] = internal_serial_buf[i];
					} // copy them with an offset of sth
				for(uint8_t i = 0; i < ri; i++){
					main_chat -> buffer[i] = internal_serial_buf[ri + i];
					} // copy them with an offset of sth
				if(!main_chat -> debufferize(main_chat -> buffer)){
					// executed if the message was not understood
					main_chat -> clear_message();
					main_chat -> outcoming.kind = DND_UND;
					main_chat -> outcoming.type = CMD;
					main_chat -> bufferize();
					for(uint8_t i = 0; i < msg_std::length; i++){
						Serial.write(main_chat -> buffer[i]);
						}
					Serial.flush();
					return;
					}
				flags.is_unapplied = true;			
				}
			}
		index = ri;
		}
		
			
	if(Wire.available() > 20){
		main_chat -> clear_message();
		Wire.readBytes(main_chat -> buffer, sizeof(main_chat -> buffer));
		main_chat -> debufferize(main_chat -> buffer);
		if(!main_chat -> debufferize(main_chat -> buffer)){
			main_chat -> outcoming.kind = DND_UND;
			main_chat -> outcoming.type = CMD;
			return;
			}
		flags.is_unapplied = true;
		
		
		}
	
	
	}

void logic::decide(){
	uint32_t cooldown = micros();
	if(flags.is_unapplied){
		switch((main_chat -> incoming.receiver)){
			// Serial.println("\nDEC\n");
			case MTR:
				// Serial.println("\nDEC->SEN\n");
				decide_sender();
				break;
			default:
				break;
			}
		flags.is_unapplied = false;
		}
	if(flags.is_unsent){
		if(write_ser_time + COOLDOWN < cooldown){
			write_ser();
			}
		
		}
	if(flags.is_pending){
		if(write_ser_time + COOLDOWN < cooldown){
			PORTD &= ~(1 << 2);
			flags.is_unapplied = 0;
			}
		
		}
	}
	
void logic::decide_sender(){
		switch(main_chat -> incoming.sender){
			case MSR:
				// Serial.println("\nSEN->TYP\n");
				decide_type();
				break;
			default:
				return;
		}
	}

void logic::decide_kind(){
		//Serial.println("Ki");
		switch(main_chat -> incoming.kind){
			case SET_MOT:
				//Serial.println("\n\nSET_MOT\n\n");
				main_translator_motor -> fill_input(main_chat -> incoming.message_space);
				main_translator_motor -> decompose();
				main_translator_motor -> apply(main_motor_r, main_motor_l);
				break;
			
			case MOV_TRB:
				//Serial.println("MOV_TRB");
				main_translator_turbine -> fill_input(main_chat -> incoming.message_space);
				main_translator_turbine -> decompose();
				main_translator_turbine -> apply((uint8_t)main_chat -> incoming.kind, *main_chat -> incoming.message_space, main_turbine, sensor);
				main_translator_motor -> compose(*main_chat -> outcoming.message_space, main_motor_r, main_motor_l);
				write_ser(GTD_MOT, MSR);
				break;
			case SRT_TRB:
				main_translator_turbine -> fill_input(main_chat -> incoming.message_space);
				main_translator_turbine -> decompose();
				main_translator_turbine -> apply((uint8_t)options::srt_t, *main_chat -> incoming.message_space, main_turbine, sensor);
				break;
			case STP_TRB:
				main_translator_turbine -> fill_input(main_chat -> incoming.message_space);
				main_translator_turbine -> decompose();
				main_translator_turbine -> apply((uint8_t)options::stp_t, *main_chat -> incoming.message_space, main_turbine, sensor);
				break;
			case GTD_MOT:
				main_translator_motor -> compose(*main_chat -> outcoming.message_space, main_motor_r, main_motor_l);
				write_ser(GTD_MOT, MSR);
				break;
			case GTD_TRB:
				main_translator_turbine -> get_data(*main_chat -> outcoming.message_space, main_turbine, sensor);
				write_ser(GTD_TRB, MSR);
				return;
			case SET_TRB: // set speed mover (TODO: IMPROVE to set other things too)
				main_translator_turbine -> fill_input(main_chat -> incoming.message_space);
				main_translator_turbine -> decompose();
				main_translator_turbine -> apply((uint8_t)options::spd_m, *main_chat -> incoming.message_space, main_turbine, sensor);
				return;
		}
	}	

void logic::decide_type(){
		switch(main_chat -> incoming.type){
			// Serial.println("\nTYP\n");
			case CMD:
				// Serial.println("\nTYP->KIN\n");
				decide_kind();
				break;
			case DAT:
				return;
		}
	}	
	
void logic::write_ser(enum msg_kind datatype, enum add_book rec){
	main_chat -> outcoming.kind = datatype;
	main_chat -> outcoming.sender = MTR;
	main_chat -> outcoming.receiver = rec;
	main_chat -> outcoming.message_number = main_chat -> incoming.message_number + 1;
	main_chat -> outcoming.type = DAT;
	if(!flags.is_unsent){
		PORTD |= 1<<2; // That is the RS485 chip leg (I guess)
		write_ser_time = micros();
		flags.is_unsent = 1;
		return;
		}
	main_chat -> bufferize();
	for(uint8_t i = 0; i < sizeof(main_chat -> buffer); i++){
			Serial.write(main_chat -> buffer[i]);
		}
	Serial.flush();
	flags.is_pending = 1;
	write_ser_time = micros();
	}

void logic::write_ser(){
	if(!flags.is_unsent){
		PORTD |= 1<<2; // That is the RS485 chip leg (I guess)
		write_ser_time = micros();
		flags.is_unsent = 1;
		return;
		}
	for(uint8_t i = 0; i < sizeof(main_chat -> buffer); i++){
			Serial.write(main_chat -> buffer[i]);
		}
	Serial.flush();
	flags.is_pending = 1;
	write_ser_time = micros();
	}
	
