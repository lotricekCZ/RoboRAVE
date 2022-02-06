#include <daters_logic.h>
#include <Arduino.h>
#include <Wire.h>

void logic::read(){
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
					//~ main_chat -> outcoming.kind = DND_UND;
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
			
	if(Wire.available() > 19){
		main_chat -> clear_message();
		Wire.readBytes(main_chat -> buffer, sizeof(main_chat -> buffer));
		main_chat -> debufferize(main_chat -> buffer);
		flags.is_unapplied = true;
		}
	}

void logic::decide(){
	//Serial.println("c");
	uint32_t cooldown = micros();
	if(flags.is_periodic){
		if(main_translator_sensor -> is_longer()){
			main_chat -> fill_message(main_translator_sensor -> data);
			write_ser(SND_CON, MSR);
			}
		}
	if(flags.is_unapplied){
			if(main_chat -> incoming.receiver == (uint8_t)my_add){			
				decide_sender();
				}
		}
	
	if(flags.is_unsent){
		if(write_ser_time + COOLDOWN < cooldown){
			write_ser();
			write_ser_time = cooldown;
			}
		}
		
	
	if(flags.is_pending){
		if(write_ser_time + COOLDOWN < cooldown){
			PORTD &= ~(1 << 3);
			flags.is_unapplied = 0;
			flags.is_pending = 0;
			flags.is_unsent = 0;
			}
		}
		
	
	flags.is_unapplied = false;
	}
	
		
void logic::decide_sender(){
		switch(main_chat -> incoming.sender){
			case MSR:
				decide_type();
				break;
			default:
				return;
		}
	}

void logic::decide_kind(){
		switch(main_chat -> incoming.kind){
			case SET_ALL:
				//main_translator_motor -> fill_input(main_chat -> incoming.message_space);
				//main_translator_motor -> decompose();
				//main_translator_motor -> apply(main_motor_r, main_motor_l);
				main_translator_sensor -> decompose(main_chat -> incoming.message_space);
				break;
			
			case SND_CON:
				//main_translator_motor -> compose(*main_chat -> outcoming.message_space, main_motor_r, main_motor_l);
				
				flags.is_periodic = !flags.is_periodic;
				break;
				
			case SND_DAT:
				main_driver -> get_data();
				main_translator_sensor -> compose();
				main_chat -> fill_message(main_translator_sensor -> data);
				write_ser(SND_DAT, MSR);
				break;
		}
	}	

void logic::decide_type(){
		switch(main_chat -> incoming.type){
			case CMD:
				decide_kind();
				break;
			case DAT:
				return;
		}
	}	
	


	
void logic::write_ser(enum msg_kind datatype, enum add_book rec){
	main_chat -> outcoming.kind = datatype;
	main_chat -> outcoming.sender = GND;
	main_chat -> outcoming.receiver = rec;
	main_chat -> outcoming.message_number = main_chat -> incoming.message_number + 1;
	main_chat -> outcoming.type = DAT;
	main_chat -> bufferize();
	if(!flags.is_unsent){
		PORTD |= 1 << 3; // That is the RS485 chip leg (I guess)
		write_ser_time = micros();
		flags.is_unsent = 1;
		return;
		}
	Serial.write(main_chat -> buffer, msg_std::length);
	flags.is_unsent = 0; // message has been sent
	Serial.flush();
	flags.is_pending = 1;
	write_ser_time = micros();
	}



void logic::write_ser(){
	if(!flags.is_unsent){
		PORTD |= 1 << 3; // That is the RS485 chip leg (I guess)
		write_ser_time = micros();
		flags.is_unsent = 1;
		return;
		}
	main_chat -> bufferize();
	for(uint8_t i = 0; i < msg_std::length; i++){
		Serial.write(main_chat -> buffer[i]);
		}
	flags.is_unsent = 0;
	Serial.flush();
	flags.is_pending = 1;
	write_ser_time = micros();
	}
	
