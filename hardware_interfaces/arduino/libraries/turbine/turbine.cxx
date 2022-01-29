#include <turbine.h>
turbine::turbine(){
	DDRB = DDRB | 0b00111100;
	esc_signal.attach(primary.turbine_pin,1000,2000);
	esc_signal.write(30);
	}
	
void turbine::turn_on_turbine(){
	primary.motor_option = ON;
	primary.repeatings += 1;
	}
	
void turbine::turn_off_turbine(){
	primary.motor_option = OFF;
	primary.repeatings -= 1;
	}
	
void turbine::change_stepper_motor_combination(uint8_t input){
	*primary.selected_register &= (0b0000 << (primary.first_of_four));
	*primary.selected_register |= (input << (primary.first_of_four));
	//Serial.println(String(*primary.selected_register, BIN));
	//Serial.println(String(primary.pulses[input]));
	}

void turbine::move_stepper_motor(){
	switch(primary.stepper_direction){
		case UP:
			if(primary.turbine_tilt != 2048){
				primary.pulse_number += 1;
				primary.turbine_tilt += 1;
			} else {
				if(!primary.hold){
					*primary.selected_register &= (0b0000 << (primary.first_of_four));
					}
				return;
				}
			break;
		case DOWN:
			if(primary.turbine_tilt != 0){
				primary.pulse_number -= 1;
				primary.turbine_tilt -= 1;
			} else {
				if(!primary.hold){
					*primary.selected_register &= (0b0000 << (primary.first_of_four));
					}
				return;
				}
			break;
		case STALLED:
			if(!primary.hold){
				*primary.selected_register &= (0b0000 << (primary.first_of_four));
				//Serial.println("reached #2");
				}
				//Serial.println("reached #3");
			break;
		}
		change_stepper_motor_combination(primary.pulses[primary.pulse_number]);
		primary.turbine_steps--;
		return;
	}
	
void turbine::set_steps(uint16_t steps){
	//(steps > 1023)?primary.turbine_steps = 1023:primary.turbine_steps = steps;
	primary.turbine_steps = steps;
	//Serial.print("steps: ");
	//Serial.println(primary.turbine_steps);
	}
	
void turbine::set_direction(stepper_options directo){
	stepper_options opt = directo;
	switch(opt){
		case STALLED:
			primary.stepper_direction = STALLED;
			break;
		case DOWN:
			primary.stepper_direction = DOWN;
			break;		
		case UP:
			primary.stepper_direction = UP;
			break;
		}
	}
	
void turbine::handle_in_background(){
	//Serial.println(primary.stepper_direction);
	
	if((primary.turbine_steps != 0 && primary.stepper_direction != STALLED)){
		uint32_t timer_micros = micros();
		uint32_t sum = primary.state_duration + primary.last_change;
		if(timer_micros >= sum){
			move_stepper_motor();
			if(primary.turbine_steps == 0){
				primary.stepper_direction = STALLED;
				//Serial.println("reached #1");
				}
			primary.last_change = timer_micros;
			}
		return;
		}
	if(!primary.hold){
		*primary.selected_register &= (0b0000 << (primary.first_of_four));
		}
	if(primary.repeatings != 0){
		uint32_t timer_motor_micros = micros();
		uint32_t sum = primary.warm_up_change + primary.warm_up_duration;
		if(timer_motor_micros >= sum){
			switch(primary.motor_option){
				case ON:
					primary.repeatings += 1;
					if(primary.repeatings == 0){
						esc_signal.write(180);
					}
					else{
						esc_signal.write(res*primary.repeatings);
					}
					break;
				case OFF:
					primary.repeatings -= 1;
					if(primary.repeatings == 0){
							esc_signal.write(0);
						}
						else{
							esc_signal.write(res*primary.repeatings);
						}
					break;
				}
			}
		}
	}
