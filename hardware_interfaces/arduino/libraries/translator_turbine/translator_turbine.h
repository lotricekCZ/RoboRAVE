#ifndef translator_turbine_h
#define translator_turbine_h
#include "../turbine_sensors/turbine_sensors.h"
#include "../turbine/turbine.h"


enum options{srt_t = 0,	//Start turbine
	stp_t = 1,	// Stop turbine
	mov_p = 2,	// Move on position
	mov_s = 3,	// Move by steps
	sen_d = 4,	// Send data
	spd_t = 5,	// Set speed turbine
	spd_m = 6 	// Set speed mover
	};

class translator_turbine{
	uint8_t input[msg_std::message_space_size];
	
	struct decomposed_data{
		unsigned state_duration: 14;
		unsigned turbine_steps: 12;
		unsigned turbine_tilt: 12; //aktualni natoceni na skale od 0-4095 / 1023
		//zalezitosti turbiny
		unsigned stepper_option: 2;
		uint8_t fan_speed;
		unsigned motor_option: 2; // fan
		
		unsigned hold: 1;
		
		unsigned option: 3;
		unsigned has_data: 1;			
		};
		
	public:
		decomposed_data data;
		void fill_input(uint8_t in[msg_std::message_space_size]);
		void apply(uint8_t dec, uint8_t *out[msg_std::message_space_size], class turbine *tur, class turbine_sensor *tur_s);
		void get_data(uint8_t *out[msg_std::message_space_size], class turbine *tur, class turbine_sensor *tur_s);
		void decompose();
		translator_turbine(){};
	};
#include "translator_turbine.cxx"
#endif
