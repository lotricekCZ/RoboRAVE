#ifndef translator_turbine_h
#define translator_turbine_h
#include "../turbine_sensors/turbine_sensors.h"
#include "../turbine/turbine.h"
enum options{srt_t = 0, stp_t = 1, mov_p = 2, mov_s = 3, sen_d = 4, spd_t = 5, spd_m = 6 };
//Start turbine, Stop turbine, move on position, move by steps, send data, set speed turbine, set speed mover
class translator_turbine{
	uint8_t input[16];
	
	struct decomposed_data{
			unsigned state_duration:14;
			unsigned turbine_tilt:12; //aktualni natoceni na skale od 0-4095 / 1023
			unsigned turbine_steps:12;
			//zalezitosti turbiny
			unsigned stepper_option:2;
			unsigned motor_option:1;
			
			unsigned hold:1;
			
			unsigned option:3;
			unsigned has_data:1;
			
		};
	public:
		decomposed_data data;
		void fill_input(uint8_t in[16]);
		void apply(uint8_t dec, uint8_t *out[16], class turbine *tur, class turbine_sensor *tur_s);
		void get_data(uint8_t *out[16], class turbine *tur, class turbine_sensor *tur_s);
		void decompose();
		translator_turbine(){};
	};
#include "translator_turbine.cxx"
#endif
