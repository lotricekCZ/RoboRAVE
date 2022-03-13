void motor::write_specific_high(uint8_t pin){
	*_motor.stepper_register |= (1 << pin);
	//~ Serial.println("Input type\t" + String(data.input_type));
	//~ Serial.print("I");
	//switch((uint8_t)_motor.stepper_register){
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
	
void motor::write_specific_low(uint8_t pin){
	*_motor.stepper_register &= ~(1 << pin);
	//~ Serial.print("L");
			//PORTD &= ~(1 << pin);
			//break;
		//case (uint8_t)&PORTC:
			//PORTC &= ~(1 << pin);
			//break;
		//case (uint8_t)&PORTB:
			//PORTB &= ~(1 << pin);
			//break;
	}
	
void motor::make_step(){
	_motor.step = high;
	write_specific_high(_motor.step_pin);
	_motor.traveled_steps++;
	_motor.last_change = micros();
	}

void motor::make_step(bool buffer){
	_motor.step = high;
	write_specific_high(_motor.step_pin);
	_motor.traveled_steps++;
	_motor.remaining_steps--;
	_motor.last_change = micros();
	}
	
void motor::set_delays(uint16_t lo, uint16_t hi){
	_motor.low_interval = lo;
	_motor.high_interval = hi;
	}
	
motor::motor(){
	DDRD |= 0b11111100;
	}
	
void motor::use_motor(uint16_t steps, enum dir direct){
	_motor.scheduled_steps = steps;
	_motor.chain = BUFFER;
	_motor.direction = direct;
	_motor.remaining_steps = _motor.scheduled_steps;
	}

void motor::use_motor(uint16_t steps, enum dir direct, bool input){ // tahle nesmaze predesle kroky
	((long)((long)_motor.scheduled_steps + (long)steps) > 65535)?_motor.scheduled_steps = 65535:_motor.scheduled_steps += steps;
	_motor.remaining_steps = _motor.scheduled_steps;
	_motor.chain = BUFFER;
	_motor.direction = direct;
	}

void motor::use_motor(uint16_t steps){
	_motor.scheduled_steps = steps;
	_motor.remaining_steps = _motor.scheduled_steps;
	}
	
void motor::use_motor(uint16_t steps, bool input){
	((long)((long)_motor.scheduled_steps + (long)steps) > 65535)?_motor.scheduled_steps = 65535:_motor.scheduled_steps += steps;
	_motor.remaining_steps = _motor.scheduled_steps;
	}

void motor::use_motor(enum unchainer option, enum dir direct){
	_motor.chain = option;
	_motor.direction = direct;
	_motor.remaining_steps = _motor.scheduled_steps;
	}

void motor::use_motor(enum unchainer option){
	_motor.chain = option;
	}

void motor::use_motor(enum dir option){
	_motor.direction = option;
	}

void motor::step_decision(){
	uint32_t mcrs = micros();
	switch(_motor.step){
		case high:
			if((uint32_t)((uint32_t)_motor.high_interval + (uint32_t)_motor.last_change) <= mcrs){
				_motor.step = motor::low;
				_motor.last_change = mcrs;
				write_specific_low(_motor.step_pin);
					}
			break;
		case low:
			if((uint32_t)((uint32_t)_motor.low_interval + (uint32_t)_motor.last_change) <= mcrs){
				switch(_motor.chain){
					case ON:
						make_step();
						_motor.step = motor::high;
						break;
					
					case OFF://nedelej kroky a mozna vubec nic... mozna vypnout fetaka
						return;
					
					case BUFFER:
					//ber kroky, dokud jsou v Bufferu
						if(_motor.remaining_steps == 0){
							_motor.chain = OFF;
							break;
							}
						_motor.step = motor::high;
						make_step(true);
						break;
					}
				}
				break;
		}	
	}
	

void motor::handle_in_background(){
	switch((uint8_t)_motor.direction){
		case 1:
			//~ Serial.print("REMAINS: ");
			//~ Serial.println(_motor.remaining_steps);
			write_specific_high(_motor.direction_pin);
			step_decision();
			break;
		case 0:
			//~ Serial.print("REMAINS: ");
			//~ Serial.println(_motor.remaining_steps);
			write_specific_low(_motor.direction_pin);
			step_decision();
			break;
		case 2:
			/// TODO: dělej něco, třeba žer kamení
			break;
		
		}
	}
