#ifndef translator_motor_cxx
#define translator_motor_cxx

void translator_motor::fill_input(uint8_t in[16]){
	for(uint8_t i = 0; i < sizeof(input); i++){
		input[i] = in[i];
		}
	}
	
void translator_motor::compose(uint8_t *out[16], class motor *Mr, class motor *Ml){
	*out[0] = Mr -> _motor.remaining_steps >> 8;
	*out[1] = Mr -> _motor.remaining_steps >> 0;
	
	*out[2] = Ml -> _motor.remaining_steps >> 8;
	*out[3] = Ml -> _motor.remaining_steps >> 0;
	
	*out[4] = Mr -> _motor.high_interval >> 6;
	*out[5] = Mr -> _motor.high_interval << 2  | Mr -> _motor.direction;
	
	*out[6] = Ml -> _motor.high_interval >> 6;
	*out[7] = Ml -> _motor.high_interval << 2  | Ml -> _motor.direction;
	
	*out[8] = Mr -> _motor.traveled_steps >> 24;
	*out[9] = Mr -> _motor.traveled_steps >> 16;
	
	*out[10] = Mr -> _motor.traveled_steps >> 8;
	*out[11] = Mr -> _motor.traveled_steps >> 0;
	
	*out[12] = Ml -> _motor.traveled_steps >> 24;
	*out[13] = Ml -> _motor.traveled_steps >> 16;
	
	*out[14] = Ml -> _motor.traveled_steps >> 8;
	*out[15] = Ml -> _motor.traveled_steps >> 0;
	}
	
void translator_motor::decompose(){
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

void translator_motor::apply(class motor *Mri, class motor *Mle){
	//~ Serial.println("\nAPPLYING\n");
	class motor *Mr = Mri;
	class motor *Ml = Mle;	

	if(data.input_type & 0b1){ // right motor
		//~ Serial.print("RIGHT\t");
		if((data.input_type >> 5) & 0b1){ // chaining
			//~ Serial.print("C");
			right_set_chain(Mr);
			}
		if((data.input_type >> 4) & 0b1){ // direction
			//~ Serial.print("D");
			right_set_dir(Mr);
			}
		if((data.input_type >> 3) & 0b1){ // rewrite
			//~ Serial.print("R");
			right_rewrite(Mr);
			}
		if((data.input_type >> 2) & 0b1){ // speed
			//~ Serial.println("S\n");
			right_set_speed(Mr);
			}
		}

	if(data.input_type >> 1 & 0b1){ // right motor
		//~ Serial.print("LEFT\t");
		if((data.input_type >> 5) & 0b1){ // chaining
			//~ Serial.print("C");
			left_set_chain(Ml);
			}
		if((data.input_type >> 4) & 0b1){ // direction
			//~ Serial.print("D");
			left_set_dir(Ml);
			}
		if((data.input_type >> 3) & 0b1){ // rewrite
			//~ Serial.print("R");
			left_rewrite(Ml);
			}
		if((data.input_type >> 2) & 0b1){ // speed
			//~ Serial.println("S");
			left_set_speed(Ml);
			}
		}	
	}
	
void translator_motor::left_rewrite(class motor *Ml){
		if(data.left_erase){
			Ml -> use_motor(data.left_steps, true);
		}else{
			Ml -> use_motor(data.left_steps);
		}
	}

void translator_motor::right_rewrite(class motor *Mr){
		if(data.right_erase){
			Mr -> use_motor(data.right_steps, true);
			}else{
			Mr -> use_motor(data.right_steps);
		}
	}
	
void translator_motor::left_set_speed(class motor *Ml){
	Ml -> _motor.high_interval = data.left_mcrs_hi;
	Ml -> _motor.low_interval = data.left_mcrs_lo; 
	}

void translator_motor::right_set_speed(class motor *Mr){
	Mr -> _motor.high_interval = data.right_mcrs_hi;
	Mr -> _motor.low_interval = data.right_mcrs_lo; 
	}

void translator_motor::left_set_dir(class motor *Ml){
	Ml -> _motor.direction = (motor::dir) data.left_dir;
	}
	
void translator_motor::right_set_dir(class motor *Mr){
	Mr -> _motor.direction = (motor::dir) data.right_dir;
	}

void translator_motor::left_set_chain(class motor *Ml){
	Ml -> _motor.chain = (motor::unchainer) data.left_unchainer;
	}

void translator_motor::right_set_chain(class motor *Mr){
	Mr -> _motor.chain = (motor::unchainer) data.right_unchainer;
	}
	
#endif
