#ifndef motorduino_logic_h
#define motorduino_logic_h
#include <chat.h>
#include <turbine.h>
#include <motor.h>
#include <translator_motor.h>
#include <translator_turbine.h>
#include <turbine_sensors.h>
#include <translator_sensor.h>

enum add_book{IR = 1, GND = 3, MTR = 2, MSR = 0};
enum msg_type{CMD = 0, DAT = 1};
enum msg_kind{
			SET_MOT = 0/*Set motor*/,
			MOV_TRB = 1/*move with turbine*/, 
			SRT_TRB = 2/*start turbine*/, 
			STP_TRB = 3/*stop turbine*/, 
			GTD_MOT = 4/*Get data motor*/, 
			GTD_TRB = 5/*Get data turbine*/,
			DND_UND = 6/*Didn`t understand*/
			}; 
			
class Logic{
	uint32_t write_ser_time = micros();
		struct{
			unsigned is_unapplied:1;
			unsigned is_unsent:1;
			unsigned is_pending:1;
			}flags;
	public:
		class Translator_motor *main_translator_motor;
		class Translator_turbine *main_translator_turbine;
		class Motor *main_motor_l;
		class Motor *main_motor_r;
		class Turbine *main_turbine;
		class Chat *main_chat;
		class Turbine_sensor *sensor;
		
		Logic(){DDRD |= 1 <<2; };
		Logic(class Motor *ml, class Motor *mr, class Turbine *t, class Chat *c, class Translator_motor *tm, class Turbine_sensor *ts, class Translator_turbine *tt){
			DDRD |= 1 << 2;
			main_motor_l = ml;
			main_motor_r = mr;
			main_turbine = t;
			main_chat = c;
			main_translator_motor = tm;
			main_translator_turbine = tt;
			sensor = ts;
			};
		void write_ser(enum msg_kind, enum add_book);
		void write_ser();
		void decide();
		//rozhodovaci protokol vyhodnocujici hodnotu vstupni zpravy a odpovedi, rozhoduje za motory
		void read();
	protected:
		void decide_kind();
		void decide_sender();
		void decide_type();
	private:
	
	};
	#include <motorduino_logic.cxx>

#endif
