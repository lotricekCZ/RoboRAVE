#include <Servo.h>
#include "turbine.h"
turbine::turbine(){
	//~ DDRB = DDRB | 0b00111100;
	//~ esc_signal.attach(primary.turbine_pin, 1000, 2000);
	//~ esc_signal.write(30);
	}

void turbine::init_servo(){
	//~ esc_signal.attach(9, 1000, 2000);
	//~ delay(2000);
	//~ esc_signal.attach(9, 1000, 2000);
	//~ delay(3000);
	//~ esc_signal.writeMicroseconds(1000);
	//~ delay(5000);
	//~ esc_signal.writeMicroseconds(2000);
	//~ delay(2000);
	//~ esc_signal.writeMicroseconds(1100);
	//~ delay(5000);

	//~ esc_signal.write(0);
	//~ delay(2000);
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
	*primary.selected_register &= !(0b1111 << (primary.first_of_four));
	*primary.selected_register |= (input << (primary.first_of_four));
	//Serial.println(String(*primary.selected_register, BIN));
	//Serial.println(String(primary.pulses[input]));
	}

void turbine::move_stepper_motor(){
	switch(primary.stepper_direction){
		case UP:
			if(primary.turbine_tilt != 4095){
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
	/*
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
		//~ *primary.selected_register &= (!(0b1111 << (primary.first_of_four)));
		}
		*/
	//~ if(*primary.selected_register != 0)
		//~ Serial.println(*primary.selected_register, BIN);
	//~ Serial.println((*primary.selected_register >> 1) & 1, BIN);
	if(primary.motor_option == CALIBRATING){
		static bool had_attached;
		uint32_t micros_now = micros();
		uint32_t sum = primary.warm_up_change + (uint32_t)3000000 + 
				(uint32_t)(primary.warm_up_change >= 512) * (uint32_t)1000000;
		if(micros_now >= sum){
			Serial.println("MIKRA");
			Serial.println(esc_signal.read());
			switch(esc_signal.read()){
				case 0:
					Serial.println("UP");
					esc_signal.write(180);	
					break;
				case 180:
					Serial.println("STABLE");
					turn_on_turbine();
					//~ delay(4000);
					break;
				default:
					Serial.println("DOWN");
					if(had_attached){
						esc_signal.write(0);
						break;
						}
					esc_signal.attach(9, 1000, 2000);
					had_attached = true;
					break;
				}
				primary.warm_up_change = micros_now;
				
			}
		}
	
	
	if(primary.repeatings != 0 && primary.motor_option != CALIBRATING){
		uint32_t timer_motor_micros = micros();
		uint32_t sum = primary.warm_up_change + (uint32_t)((uint32_t)15 * (uint32_t)primary.warm_up_duration);
		if(timer_motor_micros >= sum){
			switch(primary.motor_option){
				case ON:
					primary.repeatings += 1;
					if(primary.repeatings == 0){
						esc_signal.write(res*64);
					}
					else{
						esc_signal.write(res*primary.repeatings);
					}
					break;
				case OFF:
					primary.repeatings -= 1;
					if(primary.repeatings == 0){
							esc_signal.writeMicroseconds(1010);
						}
						else{
							esc_signal.write(res*primary.repeatings + 1);
						}
					break;
				}
			primary.warm_up_change = timer_motor_micros;
			}
		}
	}
