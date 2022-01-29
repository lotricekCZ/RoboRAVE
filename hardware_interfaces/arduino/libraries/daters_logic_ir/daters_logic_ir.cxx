#include <daters_logic_ir.h>
#include <Arduino.h>
#include <Wire.h>

void Logic::read(){
	//Serial.println(Serial.available());
	if(Serial.available() > 19){
		main_chat -> clear_message();
		Serial.readBytes(main_chat -> buffer, sizeof(main_chat -> buffer));
		main_chat -> debufferize(main_chat -> buffer);
		flags.is_unapplied = true;
		decide();
		}
			
	if(Wire.available() > 19){
		main_chat -> clear_message();
		Wire.readBytes(main_chat -> buffer, sizeof(main_chat -> buffer));
		main_chat -> debufferize(main_chat -> buffer);
		flags.is_unapplied = true;
		}
	Serial.flush();
	
	}

void Logic::decide(){
	if(flags.is_periodic){
		if(main_translator_sensor -> is_longer()){
			main_chat -> fill_message(main_translator_sensor -> data);
			write_ser(SND_CON, MSR);
			}
		}
	if(flags.is_unapplied){
			if(main_chat -> incoming.receiver == (uint8_t)my_add){
				//Serial.println("d");			
				decide_sender();
				
				}
		}
		flags.is_unapplied = false;
	
	}
	
		
void Logic::decide_sender(){
		switch(main_chat -> incoming.sender){
			case MSR:
				//Serial.println("e");
				decide_type();
				break;
			default:
				return;
		}
	}

void Logic::decide_kind(){
	//Serial.println("g");
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
				write_ser(SND_CON, MSR);
				break;
		}
	}	

void Logic::decide_type(){
		switch(main_chat -> incoming.type){
			case CMD:
				//Serial.println("f");
				decide_kind();
				break;
			case DAT:
				return;
		}
	}	
	
void Logic::write_ser(enum msg_kind datatype, enum add_book rec){
	main_chat -> outcoming.kind = datatype;
	main_chat -> outcoming.sender = my_add;
	main_chat -> outcoming.receiver = rec;
	main_chat -> outcoming.message_number = main_chat -> incoming.message_number + 1;
	main_chat -> outcoming.type = DAT;
	
	main_chat -> bufferize();
	for(uint8_t i = 0; i < sizeof(main_chat -> buffer); i++){
			Serial.write(main_chat -> buffer[i]);
		}
	Serial.flush();
	}
	
