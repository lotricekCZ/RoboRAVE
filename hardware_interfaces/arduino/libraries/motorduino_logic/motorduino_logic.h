#include "../chat/chat.h"
#include "../turbine/turbine.h"
#include "../motor/motor.h"
#include "../translator_motor/translator_motor.h"
#include "../translator_turbine/translator_turbine.h"
#include "../turbine_sensors/turbine_sensors.h"
#include "../translator_sensor/translator_sensor.h"

#ifndef motorduino_logic_h
#define motorduino_logic_h

enum add_book{IR = 1, GND = 3, MTR = 2, MSR = 0};
enum msg_type{CMD = 0, DAT = 1};
enum msg_kind{
			SET_MOT = 0, 	/*Set motor*/
			MOV_TRB = 1, 	/*move with turbine*/ 
			SRT_TRB = 2, 	/*start turbine*/ 
			STP_TRB = 3, 	/*stop turbine*/ 
			GTD_MOT = 4, 	/*Get data motor*/ 
			GTD_TRB = 5, 	/*Get data turbine*/
			DND_UND = 6, 	/*Didn`t understand*/
			SET_TRB = 7		/*Setup turbine*/
			}; 
			
class logic {
	uint8_t internal_serial_buf[msg_std::length];
	uint32_t write_ser_time = micros();
		struct {
			unsigned is_unapplied:1;
			unsigned is_unsent:1;
			unsigned is_pending:1;
			unsigned was_start:1;
			unsigned counts:1;
			} flags;
	uint8_t index = 0;
	public:
		translator_motor *main_translator_motor;
		translator_turbine *main_translator_turbine;
		motor *main_motor_l;
		motor *main_motor_r;
		turbine *main_turbine;
		chat *main_chat;
		turbine_sensor *sensor;
		
		logic(){DDRD |= 1 << 2;};
		logic(motor *ml, 
				motor *mr, 
				turbine *t, 
				chat *c, 
				translator_motor *tm, 
				turbine_sensor *ts, 
				translator_turbine *tt){
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
	
#include "motorduino_logic.cxx"

#endif
