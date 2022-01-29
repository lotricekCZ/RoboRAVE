#include <chat.h>

void Chat::bufferize(){
	buffer[1] = (outcoming.receiver << 5) | (outcoming.sender << 2) | (outcoming.type << 1) | (outcoming.kind >> 2);
	buffer[2] = (outcoming.kind << 6) | (outcoming.message_number >> 16);
	buffer[3] = (outcoming.message_number >> 8);
	buffer[4] = (outcoming.message_number);
	for(uint8_t i = 0; i < 16; i++){
		buffer[i+5] = outcoming.message_space[i];
		}
	}
	
void Chat::fill_message(uint8_t input_message[16]){
	for(uint8_t i = 0; i < sizeof(outcoming.message_space); i++){
		outcoming.message_space[i] = input_message[i];
		}
	}
bool Chat::debufferize(uint8_t input[20]){
	//~ if(input[0] != '$' && input[21] != ';'){
		//~ return false;
		//~ }
	incoming.receiver = (input[0] & 0b11100000) >> 5;
	incoming.sender = (input[0] & 0b00011100) >> 2;
	incoming.type = (input[0] & 0b00000010) >> 1;
	incoming.kind = 0b000 | ((0b1 & input[0]) << 2) | (input[1]  >> 6);
	incoming.message_number	= (((input[1] & 0b111111) << 16) | (input[2] << 8) | input[3]);
	for(uint8_t i = 0; i < sizeof(incoming.message_space); i++){
			incoming.message_space[i] = input[i+4];
			//Serial.println("msg "+String(input[i+4]));
		}
	return true;
	}
	
void  Chat::clear_message(){
	for(uint8_t i = 0; i < sizeof(outcoming); i++){
			buffer[i] = 0;
		}
	
	}
