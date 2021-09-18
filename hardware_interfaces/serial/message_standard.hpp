#ifndef MSG_STD
#define MSG_STD

namespace msg_std{
	// this is a format of all messages that are sent
	const uint8_t length 		= 22;
	const uint8_t head			= 1;
	const uint8_t head_size		= 4;
	const uint8_t message_space	= head + head_size;
	
	const uint8_t start		 	= '$';
	const uint8_t end	 		= ';';
	const uint8_t message_space_size = length - (2 + head + head_size);
	};

#endif
