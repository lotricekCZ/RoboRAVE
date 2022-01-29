#ifndef translator_motor_h
#define translator_motor_h
#include "../motor/motor.h"

class translator_motor {
	private:
		uint8_t	 input[16];
		struct decomposed_data{
			uint16_t left_steps;
			uint16_t right_steps; // 4b
			unsigned left_mcrs_hi:14;
			unsigned right_mcrs_hi:14;
			unsigned left_mcrs_lo:14;
			unsigned right_mcrs_lo:14;	//	11b
			unsigned right_unchainer:2;
			unsigned left_unchainer:2;
			unsigned left_dir:2;
			unsigned right_dir:2; // 12b
			unsigned left_erase:1;
			unsigned right_erase:1;
			unsigned input_type:6; // 13b
			} data {0,0,0,0,0,0,0,0,0,0,0,0,0};
		//~ struct decomposed_data data{0,0,0,0,0,0,0,0,0,0,0,0,0};
		
		void left_set_speed(class motor *Ml);
		void left_set_dir(class motor *Ml);
		void left_set_chain(class motor *Ml);
		void left_rewrite(class motor *Ml);
		
		void right_set_speed(class motor *Mr);
		void right_set_dir(class motor *Mr);
		void right_set_chain(class motor *Mr);
		void right_rewrite(class motor *Mr);
		
	public:
		translator_motor(){};
		void apply(class motor *Mr, class motor *Ml);
		void compose(uint8_t *out[16], class motor *Mr, class motor *Ml);
		void decompose();
		void fill_input(uint8_t in[16]);
	};
#include "translator_motor.cxx"
#endif
