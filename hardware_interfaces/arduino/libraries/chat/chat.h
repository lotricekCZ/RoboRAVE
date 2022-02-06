#ifndef chat_h
#define chat_h
#include "../../../serial/message_standard.hpp"

class chat {
	
	struct message {
		unsigned receiver:3;
		unsigned sender:3;
		unsigned type:1; //typ zpravy (0 - prikaz, 1 - data, potvrzovac) - data jsou posilana pres UΑRΤ, prikazy pres I2C
		unsigned kind:3;
		unsigned long message_number:22; 
		/*druh zpravy, lze spojit s type 
		 * (0 - pohyb motoru, 1 - posli data 0, 2 - posli data 1, 3 - posli data 2 (vic jich snad nebude),
		 *  4 - natoc foukac, 5 - roztoc foukac, 6 - vypni foukac, 7 - rezervovano) 
		 * a (8 - data0, 9 - data1, 10 - data2, 11 - potvrzovac, 12 - rezervovano, 13 - rezervovano, 14 - rezervovano, 15 - rezervovano)*/
		uint8_t message_space[msg_std::length]; // prinasi 2^128 moznosti vyuziti (10bitova data po osmi - 80b)
		};
	public:
		uint8_t buffer[msg_std::length];
		chat(){
			buffer[0] = msg_std::start;
			buffer[msg_std::length - 1] = msg_std::end;
			}
		message outcoming;
		message incoming;
		void bufferize();						// plni buffer z outcomingu
		void clear_message();					// cisti buffer		
		bool debufferize(uint8_t input[msg_std::length]);	// plni incoming z bufferu
		void fill_message(uint8_t input[msg_std::message_space_size]);	// plni message space outcomingu
	};
	#include "chat.cpp"
#endif
