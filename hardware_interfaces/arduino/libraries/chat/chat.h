#ifndef chat_h
#define chat_h
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
		uint8_t message_space[16]; // prinasi 2^128 moznosti vyuziti (10bitova data po osmi - 80b)
		};
		public:
			uint8_t buffer[22];
			chat(){
				buffer[0] = "$";
				buffer[21] = ";";
				}
			message outcoming;
			message incoming;
			void bufferize();						// plni buffer z outcomingu
			void clear_message();					// cisti buffer		
			bool debufferize(uint8_t input[20]);	// plni incoming z bufferu
			void fill_message(uint8_t input[16]);	// plni message space outcomingu
	};
	#include "chat.cpp"
#endif
