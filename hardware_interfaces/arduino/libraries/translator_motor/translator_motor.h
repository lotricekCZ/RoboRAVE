#ifndef translator_motor_h
#define translator_motor_h
#include "../motor.h"

class Translator_motor{
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
		
		void left_set_speed(class Motor *Ml);
		void left_set_dir(class Motor *Ml);
		void left_set_chain(class Motor *Ml);
		void left_rewrite(class Motor *Ml);
		
		void right_set_speed(class Motor *Mr);
		void right_set_dir(class Motor *Mr);
		void right_set_chain(class Motor *Mr);
		void right_rewrite(class Motor *Mr);
		
	public:
		Translator_motor(){};
		void apply(class Motor *Mr, class Motor *Ml);
		void compose(uint8_t *out[16], class Motor *Mr, class Motor *Ml);
		void decompose();
		void fill_input(uint8_t in[16]);
	};

#endif
