#include "translator_motor.h"

void Translator_motor::fill_input(uint8_t in[16]){
	for(uint8_t i = 0; i < sizeof(input); i++){
		input[i] = in[i];
		}
	}
	
void Translator_motor::compose(uint8_t *out[16], class Motor *Mr, class Motor *Ml){
	*out[0] = Mr -> motor.remaining_steps >> 8;
	*out[1] = Mr -> motor.remaining_steps >> 0;
	
	*out[2] = Ml -> motor.remaining_steps >> 8;
	*out[3] = Ml -> motor.remaining_steps >> 0;
	
	*out[4] = Mr -> motor.high_interval >> 6;
	*out[5] = Mr -> motor.high_interval << 2  | Mr -> motor.direction;
	
	*out[6] = Ml -> motor.high_interval >> 6;
	*out[7] = Ml -> motor.high_interval << 2  | Ml -> motor.direction;
	
	*out[8] = Mr -> motor.traveled_steps >> 24;
	*out[9] = Mr -> motor.traveled_steps >> 16;
	
	*out[10] = Mr -> motor.traveled_steps >> 8;
	*out[11] = Mr -> motor.traveled_steps >> 0;
	
	*out[12] = Ml -> motor.traveled_steps >> 24;
	*out[13] = Ml -> motor.traveled_steps >> 16;
	
	*out[14] = Ml -> motor.traveled_steps >> 8;
	*out[15] = Ml -> motor.traveled_steps >> 0;
	
	
	}
	
void Translator_motor::decompose(){
	data.left_steps = ((input[0] << 8) | input[1]);
	data.right_steps = ((input[2] << 8) | input[3]);
	
	data.left_mcrs_hi = ((input[4] << 6) | ((input[5] & 0b11111100)  >> 2));
	data.left_dir = (0b11 & input[5]);
	data.right_mcrs_hi = ((input[6] << 6) | (input[7] & 0b11111100) >> 2);
	data.right_dir = (0b11 & input[7]);
	
	data.left_mcrs_lo = ((input[8] << 6) | ((input[9] & 0b11111100) >> 2));
	data.left_unchainer = (0b11 & input[9]);
	data.right_mcrs_lo = ((input[10] << 6) | ((input[11] & 0b11111100) >> 2));
	data.right_unchainer = (0b11 & input[11]);
	
	data.left_erase = (0b1 & (input[12] & 0b00000001));
	data.right_erase = (0b1 & ((input[12] & 0b00000010) >> 1));
	data.input_type = input[12] >> 2;
	// Serial.println("LEFT:\t" + String(data.left_mcrs_hi)+"  "+ String(data.left_mcrs_lo)+" STEPS: "+String(data.left_steps)+ " " + String(data.left_dir)+"  "+ String(data.left_unchainer));
	// Serial.println("RIGHT:\t" + String(data.right_mcrs_hi)+"  "+ String(data.right_mcrs_lo)+" STEPS: "+String(data.right_steps)+" " +String(data.right_dir)+"  "+ String(data.right_unchainer));
	}

void Translator_motor::apply(class Motor *Mri, class Motor *Mle){
	// Serial.println("\nAPPLYING\n");
	class Motor *Mr = Mri;
	class Motor *Ml = Mle;	
	// Serial.println(data.input_type);
	// Serial.println(data.left_steps);
	// Serial.println(data.right_steps);
	switch((uint8_t)data.input_type){
		case 1: 						// premaze left
			left_rewrite(Ml);
			break;
			
		case 2:							// premaze right
			right_rewrite(Mr); 
			break;
			
		case 3:							// premaze r&l
			right_rewrite(Mr);
			left_rewrite(Ml);
			break;
			
		case 4:							// nastavi velikost impulzu left
			left_set_speed(Ml);
			break;
			
		case 5:							// nastavi velikost impulzu right
			right_set_speed(Mr);
			break;
			
		case 6:							// nastavi velikost impulzu r&l
			left_set_speed(Ml);
			right_set_speed(Mr);
			break;
			
		case 7:
			left_set_dir(Ml);			//  nastavi smer left
			break;
			
		case 8:
			right_set_dir(Mr);			//  nastavi smer right
			break;
			
		case 9:
			right_set_dir(Mr);			//  nastavi smer r&l
			left_set_dir(Ml);
			break;
			
		case 10:
			left_set_dir(Ml);			//  nastavi smer a prepise left
			left_rewrite(Ml);
			break;
			
		case 11:
			right_set_dir(Mr);			//  nastavi smer a prepise right
			right_rewrite(Mr);
			break;
			
		case 12:						//  nastavi smer a prepise r&l
			right_set_dir(Mr);
			left_set_dir(Ml);
			right_rewrite(Mr);
			left_rewrite(Ml);
			break;
			
		case 13:						//  nastavi retezeni left
			left_set_chain(Ml);
			break;
			
		case 14:						//  nastavi retezeni right
			right_set_chain(Mr);
			break;
			
		case 15:						//  nastavi retezeni r&l
			right_set_chain(Mr);
			left_set_chain(Ml);
			break;
			
		case 16:						//  nastavi retezeni a smer left
			left_set_chain(Ml);
			left_set_dir(Ml);
			break;
			
		case 17:						//  nastavi retezeni a smer right
			right_set_chain(Mr);
			right_set_dir(Mr);
			break;
			
		case 18:						//  nastavi retezeni a smer r&l
			right_set_chain(Mr);
			left_set_chain(Ml);
			right_set_dir(Mr);
			left_set_dir(Ml);
			break;
		case 19:
			left_rewrite(Ml);
			left_set_chain(Ml);
			left_set_dir(Ml);
			left_set_speed(Ml);
			break;
			
		case 20:
			right_rewrite(Mr);
			right_set_chain(Mr);
			right_set_dir(Mr);
			right_set_speed(Mr);
			break;
		case 21:
			right_rewrite(Mr);
			right_set_chain(Mr);
			right_set_dir(Mr);
			right_set_speed(Mr);
			left_rewrite(Ml);
			left_set_chain(Ml);
			left_set_dir(Ml);
			left_set_speed(Ml);
			break;
			
		case 22:
			//left_rewrite(Ml);
			left_set_chain(Ml);
			left_set_dir(Ml);
			left_set_speed(Ml);
			break;
			
		case 23:
			//right_rewrite(Mr);
			right_set_chain(Mr);
			right_set_dir(Mr);
			right_set_speed(Mr);
			break;
			
		case 24:
			//right_rewrite(Mr);
			right_set_chain(Mr);
			right_set_dir(Mr);
			right_set_speed(Mr);
			//left_rewrite(Ml);
			left_set_chain(Ml);
			left_set_dir(Ml);
			left_set_speed(Ml);
			break;
			
		}
	}
	
void Translator_motor::left_rewrite(class Motor *Ml){
		if(data.left_erase){
			Ml -> use_motor(data.left_steps, true);
		}else{
			Ml -> use_motor(data.left_steps);
		}
	}

void Translator_motor::right_rewrite(class Motor *Mr){
		if(data.right_erase){
			Mr -> use_motor(data.right_steps, true);
			}else{
			Mr -> use_motor(data.right_steps);
		}
	}
	
void Translator_motor::left_set_speed(class Motor *Ml){
	Ml -> motor.high_interval = data.left_mcrs_hi;
	Ml -> motor.low_interval = data.left_mcrs_lo; 
	}

void Translator_motor::right_set_speed(class Motor *Mr){
	Mr -> motor.high_interval = data.right_mcrs_hi;
	Mr -> motor.low_interval = data.right_mcrs_lo; 
	}

void Translator_motor::left_set_dir(class Motor *Ml){
	Ml -> motor.direction = (Motor::dir) data.left_dir;
	}
	
void Translator_motor::right_set_dir(class Motor *Mr){
	Mr -> motor.direction = (Motor::dir) data.right_dir;
	}

void Translator_motor::left_set_chain(class Motor *Ml){
	Ml -> motor.chain = (Motor::unchainer) data.left_unchainer;
	}

void Translator_motor::right_set_chain(class Motor *Mr){
	Mr -> motor.chain = (Motor::unchainer) data.right_unchainer;
	}
	
