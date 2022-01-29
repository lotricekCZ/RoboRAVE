#ifndef turbine_h
#define turbine_h
#include <Arduino.h>
#include <Servo.h>

enum stepper_options {UP = 1, DOWN = 0, STALLED = 2};
enum turbine_options {ON = 1, OFF = 0};
class Turbine{
		protected:
		Servo esc_signal;
		struct turbine{
			//zalezitosti pulsu
			unsigned pulse_number:3;
			uint8_t pulses[8];
			uint16_t state_duration;
			uint32_t last_change; 
			unsigned turbine_tilt:12; //aktualni natoceni na skale od 0-1023 
			unsigned turbine_steps:12;
			//zalezitosti turbiny
			turbine_options motor_option;
			unsigned turbine_pin:4;
			//zalezitosti pinu
			unsigned first_of_four:3; //zada se pouze nejnizsi cislo z registru, do ktereho se zapisuji pulsy
			volatile uint8_t *selected_register;
			stepper_options stepper_direction;
			unsigned hold:1;
			unsigned minimum:6;
			unsigned maximum:8;
			unsigned repeatings:6;
			uint32_t warm_up_change;
			uint16_t warm_up_duration;
			};
			void change_stepper_motor_combination(uint8_t input);
		public:
			struct turbine primary = {0, {8,12,4,6,2,3,1,9}, 1000, 0, 1024, 0, OFF, 9, PB2, &PORTB, STALLED, 0, 50, 180, 0, 0, 9000};
			uint8_t res = (180-50)/64;
			Turbine();
			void move_stepper_motor();
			void turn_on_turbine();
			void turn_off_turbine();
			void handle_in_background();
			void set_steps(uint16_t input);
			void set_direction(stepper_options input);
};
#include "turbine.cxx"
#endif
