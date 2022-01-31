#ifndef motorduino_logic_h
#define motorduino_logic_h

#include "../chat/chat.h"
#include "../driver_sensors/driver_sensor_array.h"
#include "../translator_sensor/translator_sensor.h"

enum add_book{IR = 1, GND = 3, MTR = 2, MSR = 0};
enum msg_type{CMD = 0, DAT = 1};
enum msg_kind{
			SND_DAT = 0/*Send data*/,
			SND_CON = 1/*Send data continuously*/,
			SET_ALL = 2			
			}; 
			
class logic{
		uint8_t index = 0;
		struct{
			unsigned is_unapplied:1;
			unsigned is_periodic:1;
			}flags;
		uint8_t internal_serial_buf[msg_std::length];
	public:
		class sensor_driver *main_driver;
		class translator_sensor *main_translator_sensor;
		class chat *main_chat;
		
		enum add_book my_add;
		
		logic(){};
		logic(class chat *c){
			main_chat = c;
			};
		void write_ser(enum msg_kind, enum add_book);
		void decide();
		//rozhodovaci protokol vyhodnocujici hodnotu vstupni zpravy a odpovedi
		void read();
	protected:
		void decide_kind();
		void decide_sender();
		void decide_type();
	private:
	
	};
	#include "daters_logic.cxx"

#endif
