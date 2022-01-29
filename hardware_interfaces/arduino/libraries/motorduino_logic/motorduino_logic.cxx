#include <Arduino.h>
#include <Wire.h>
#include "motorduino_logic.h"
#include "../chatchat.h"
#include "../turbine/turbine.h"
#include "../motor/motor.h"
#include "../translator_motor/translator_motor.h"

void Logic::read(){
//Serial.println("N/A");
	if(Serial.available() > 19){
		main_chat -> clear_message();
		//Serial.println(sizeof(main_chat -> buffer));
		Serial.readBytes(main_chat -> buffer, sizeof(main_chat -> buffer));
		//Serial.write(*main_chat -> buffer);
		Serial.flush();
		if(!main_chat -> debufferize(main_chat -> buffer)){
			main_chat -> outcoming.kind = DND_UND;
			main_chat -> outcoming.type = CMD;
			main_chat -> bufferize();
			for(uint8_t i = 0; i < sizeof(main_chat -> buffer); i++){
				Serial.write(main_chat -> buffer[i]);
			}
			return;
			}
		/*Serial.println("f");
		//char *c = (char*)malloc(200);
		/*sprintf(c, "rec:\t%u,\nsen:\t%u\ntype:\t%u\nkind:\t%u,\nmsg_num:\t%u\n%u\t%u\t%u\t%u\n%u\t%u\t%u\t%u\n%u\t%u\t%u\t%u\n%u\t%u\t%u\t%u", main_chat -> incoming.receiver, main_chat -> incoming.sender, main_chat -> incoming.type, main_chat -> incoming.kind, main_chat -> incoming.message_number, 
		main_chat -> incoming.message_space[0], main_chat -> incoming.message_space[1], main_chat -> incoming.message_space[2], main_chat -> incoming.message_space[3], main_chat -> incoming.message_space[4],
		main_chat -> incoming.message_space[5], main_chat -> incoming.message_space[6], main_chat -> incoming.message_space[7], main_chat -> incoming.message_space[8], main_chat -> incoming.message_space[9],
		main_chat -> incoming.message_space[10], main_chat -> incoming.message_space[11], main_chat -> incoming.message_space[12], main_chat -> incoming.message_space[13], main_chat -> incoming.message_space[14],
		main_chat -> incoming.message_space[15]);*/
		
		// Serial.println(c);
		// Serial.println("\n\n\nfok\n\n\n");
		//free(c);*/
		flags.is_unapplied = true;
		Serial.flush();
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

void Logic::decide(){
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
	
void Logic::decide_sender(){
		switch(main_chat -> incoming.sender){
			case MSR:
				// Serial.println("\nSEN->TYP\n");
				decide_type();
				break;
			default:
				return;
		}
	}

void Logic::decide_kind(){
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
				break;
			case SRT_TRB:
				break;
			case STP_TRB:
				break;
			case GTD_MOT:
				main_translator_motor -> compose(*main_chat -> outcoming.message_space, main_motor_r, main_motor_l);
				write_ser(GTD_MOT, MSR);
				break;
			case GTD_TRB:
				main_translator_turbine -> get_data(*main_chat -> outcoming.message_space, main_turbine, sensor);
				write_ser(GTD_TRB, MSR);
				return;
		}
	}	

void Logic::decide_type(){
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
	
void Logic::write_ser(enum msg_kind datatype, enum add_book rec){
	main_chat -> outcoming.kind = datatype;
	main_chat -> outcoming.sender = MTR;
	main_chat -> outcoming.receiver = rec;
	main_chat -> outcoming.message_number = main_chat -> incoming.message_number + 1;
	main_chat -> outcoming.type = DAT;
	if(!flags.is_unsent){
		PORTD |= 1<<2;
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

void Logic::write_ser(){
	if(!flags.is_unsent){
		PORTD |= 1<<2;
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
	
