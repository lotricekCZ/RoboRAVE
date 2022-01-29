#include <motor.h>

void Motor::write_specific_high(uint8_t pin){
	*motor.stepper_register |= (1 << pin);
			
	//switch((uint8_t)motor.stepper_register){
		//case (uint8_t)&PORTD:
			//PORTD |= (uint8_t)(1 << pin);
			//break;
		//case (uint8_t)&PORTC:
			//PORTC |= (uint8_t)(1 << pin);
			//break;
		//case (uint8_t)&PORTB:
			//PORTB |= (uint8_t)(1 << pin);
			//break;
		//}
	}
	
void Motor::write_specific_low(uint8_t pin){
	*motor.stepper_register &= ~(1 << pin);
			//PORTD &= ~(1 << pin);
			//break;
		//case (uint8_t)&PORTC:
			//PORTC &= ~(1 << pin);
			//break;
		//case (uint8_t)&PORTB:
			//PORTB &= ~(1 << pin);
			//break;
	}
	
void Motor::make_step(){
	motor.step = high;
	write_specific_high(motor.step_pin);
	motor.traveled_steps++;
	motor.last_change = micros();
	}

void Motor::make_step(bool buffer){
	motor.step = high;
	write_specific_high(motor.step_pin);
	motor.traveled_steps++;
	motor.remaining_steps--;
	motor.last_change = micros();
	}
	
void Motor::set_delays(uint16_t lo, uint16_t hi){
	motor.low_interval = lo;
	motor.high_interval = hi;
	}
	
Motor::Motor(){
	DDRD |= 0b11111100;
	}
	
void Motor::use_motor(uint16_t steps, enum dir direct){
	motor.scheduled_steps = steps;
	motor.chain = BUFFER;
	motor.direction = direct;
	motor.remaining_steps = motor.scheduled_steps;
	}

void Motor::use_motor(uint16_t steps, enum dir direct, bool input){ // tahle nesmaze predesle kroky
	((long)((long)motor.scheduled_steps + (long)steps) > 65535)?motor.scheduled_steps = 65535:motor.scheduled_steps += steps;
	motor.remaining_steps = motor.scheduled_steps;
	motor.chain = BUFFER;
	motor.direction = direct;
	}

void Motor::use_motor(uint16_t steps){
	motor.scheduled_steps = steps;
	motor.remaining_steps = motor.scheduled_steps;
	}
	
void Motor::use_motor(uint16_t steps, bool input){
	((long)((long)motor.scheduled_steps + (long)steps) > 65535)?motor.scheduled_steps = 65535:motor.scheduled_steps += steps;
	motor.remaining_steps = motor.scheduled_steps;
	}

void Motor::use_motor(enum unchainer option, enum dir direct){
	motor.chain = option;
	motor.direction = direct;
	motor.remaining_steps = motor.scheduled_steps;
	}

void Motor::use_motor(enum unchainer option){
	motor.chain = option;
	}

void Motor::use_motor(enum dir option){
	motor.direction = option;
	}

void Motor::step_decision(){
	uint32_t mcrs = micros();
	switch(motor.step){
		case high:
			if((uint32_t)((uint32_t)motor.high_interval + (uint32_t)motor.last_change) <= mcrs){
				motor.step = Motor::low;
				motor.last_change = mcrs;
				write_specific_low(motor.step_pin);
					}
			break;
		case low:
			if((uint32_t)((uint32_t)motor.low_interval + (uint32_t)motor.last_change) <= mcrs){
				switch(motor.chain){
					case ON:
						make_step();
						motor.step = Motor::high;
						break;
					
					case OFF://nedelej kroky a mozna vubec nic... mozna vypnout fetaka
						return;
					
					case BUFFER:
					//ber kroky, dokud jsou v Bufferu
						if(motor.remaining_steps == 0){
							motor.chain = OFF;
							break;
							}
						motor.step = Motor::high;
						make_step(true);
						break;
					}
				}
				break;
		}	
	}
	

void Motor::handle_in_background(){
	switch((uint8_t)motor.direction){
		case 1:
			write_specific_high(motor.direction_pin);
			step_decision();
			break;
		case 0:
			write_specific_low(motor.direction_pin);
			step_decision();
			break;
		case 2:
			/// TODO: dělej něco, třeba žer kamení
			break;
		
		}
	}
