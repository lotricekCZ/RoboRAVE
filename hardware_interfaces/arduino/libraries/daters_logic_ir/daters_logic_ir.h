#ifndef daters_logic_ir_h
#define daters_logic_ir_h

#include "../chat/chat.h"
#include "../driver_sensor_irduino/driver_sensor_irduino.h"
#include "../translator_sensor_ir/translator_sensor_ir.h"

enum add_book{IR = 1, GND = 3, MTR = 2, MSR = 0, STM = 4};
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
			unsigned is_unsent:1;
			unsigned is_pending:1;
			unsigned was_start:1;
			unsigned counts:1;
			}flags;
	uint8_t internal_serial_buf[msg_std::length];
	uint32_t write_ser_time = micros();
		
	public:
		class sensor_driver *main_driver;
		class translator_sensor *main_translator_sensor;
		class chat *main_chat;
		
		enum add_book my_add;
		
		logic(){DDRD |= 1 << 3;};
		logic(class chat *c){
			DDRD |= 1 << 3;
			main_chat = c;
			};
		
		void write_ser(enum msg_kind, enum add_book);
		void write_ser();
		void decide();
		//rozhodovaci protokol vyhodnocujici hodnotu vstupni zpravy a odpovedi
		void read();
	protected:
		void decide_kind();
		void decide_sender();
		void decide_type();
	private:
	
	};
	#include "daters_logic_ir.cxx"

#endif
