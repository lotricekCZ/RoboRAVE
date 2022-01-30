#include "chat.h"

void chat::bufferize(){
	buffer[msg_std::head] = (outcoming.receiver << 5) | (outcoming.sender << 2) | (outcoming.type << 1) | (outcoming.kind >> 2);
	buffer[msg_std::head + 1] = (outcoming.kind << 6) | (outcoming.message_number >> 16);
	buffer[msg_std::head + 2] = (outcoming.message_number >> 8);
	buffer[msg_std::head + 3] = (outcoming.message_number);
	for(uint8_t i = 0; i < 16; i++){
		buffer[i + msg_std::message_space] = outcoming.message_space[i];
		}
	}

	
void chat::fill_message(uint8_t input_message[msg_std::message_space_size]){
	for(uint8_t i = 0; i < sizeof(outcoming.message_space); i++){
		outcoming.message_space[i] = input_message[i];
		}
	}


bool chat::debufferize(uint8_t input[msg_std::length]){
	//~ if(input[0] != '$' && input[21] != ';'){
		//~ return false;
		//~ }
	
	incoming.receiver = (input[msg_std::head] & 0b11100000) >> 5;
	incoming.sender = 	(input[msg_std::head] & 0b00011100) >> 2;
	incoming.type = 	(input[msg_std::head] & 0b00000010) >> 1;
	incoming.kind = 	((0b1 & input[msg_std::head]) << 2) | (input[msg_std::head + 1]  >> 6);
	incoming.message_number	= (((input[msg_std::head + 1] & 0b111111) << 16) | (input[msg_std::head + 2] << 8) | input[msg_std::head + 3]);
	
	if(input[0] != msg_std::start || input[msg_std::length - 1] != msg_std::end){
		return false; // objective here is to at least try to read the head
		}
		
	for(uint8_t i = 0; i < msg_std::message_space_size; i++){
		incoming.message_space[i] = input[i + msg_std::message_space];
		//Serial.println("msg "+String(input[i+4]));
		}
	return true;
	}

	
void chat::clear_message(){
	for(uint8_t i = msg_std::head; i < (msg_std::length - 1); i++){
		buffer[i] = 0;
		}
	
	}
