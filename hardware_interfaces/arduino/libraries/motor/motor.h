#ifndef motor_h
#define motor_h
#include <Arduino.h>

class motor{
		public:
		enum dir{FRONT = 0, BACK = 1, STALLED = 2};
		enum step_cycle{high = 1, low = 0};
		enum unchainer{ON = 2, OFF = 0, BUFFER = 1}; //jeho ukolem je osvobodit arduino od kroku, proste je na pozadi provadi a pripocitava
		protected:
		struct properties{
			//kroky
			uint16_t scheduled_steps; //zadany pocet kroku
			uint16_t remaining_steps; //zbyvajici pocet kroku
			uint32_t traveled_steps;
			//intervaly
			unsigned high_interval:14; //cas v us pro vysokou - 0 - 2^14-1 us (16383 us)
			unsigned low_interval:14; // cas v mikrosekundach pro nizkou uroven 
			uint32_t last_change; 
			//porty
			volatile uint8_t *stepper_register;
			unsigned step_pin:3;
			unsigned direction_pin:3;
			enum dir direction;
			enum step_cycle step;
			enum unchainer chain; //moznosti on off a buffer - zapnuto, vypnuto, bere kroky ze zasobniku
			};
			
		void make_step();
		void make_step(bool input);
		void step_decision();
		void write_specific_high(uint8_t pin);
		void write_specific_low(uint8_t pin);
	public:
		properties _motor = {0, 0, 0, 0, 0, 0, &PORTD, 0, 0, STALLED, low, BUFFER};
		motor();
		// pro provoz na pozadi
		void handle_in_background();
		//moznosti, jak nastavit motor
		void use_motor(uint16_t steps, enum dir direct, bool input);	 //nepremaze kroky, prida je, nastavi smer
		void use_motor(uint16_t steps, enum dir direct); 				//premaze kroky, prida je, nastavi smer
		void use_motor(uint16_t steps);									//premaze kroky, prida je	
		void use_motor(uint16_t steps, bool input); 					//nepremaze kroky, prida je
		void use_motor(enum unchainer option, enum dir direct);
		void use_motor(enum unchainer option);
		void use_motor(enum dir direct);
		void set_delays(uint16_t low, uint16_t high);
	
	};
	#include "motor.cxx"
#endif
