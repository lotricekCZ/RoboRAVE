#include <translator_turbine.h>
#include <turbine.h>

void Translator_turbine::fill_input(uint8_t in[16]){
	//Serial.println("fill");
	for(uint8_t i = 0; i < sizeof(input); i++){
		input[i] = in[i];
		//Serial.println(in[i]);
		}
	//Serial.println("fillend");
	}
	
void Translator_turbine::decompose(){
	data.state_duration = (input[0] << 8 | input[1]) >> 2;
	data.turbine_steps = ((input[1] & 0b11) << 10 | input[2] << 2 | input[3] >> 6);
	data.stepper_option = input[3] >> 4;
	data.motor_option = input[3] >> 3;
	data.option = input[3];
	data.hold = input[4] >> 7;
	data.turbine_tilt = input[4] << 5 | input[5] >> 3;
	Serial.println(data.hold);//Serial.println(data.turbine_steps);
	}
	
void Translator_turbine::get_data(uint8_t *out[16], class Turbine *tur, class Turbine_sensor *tur_s){
	*out[0] = tur -> primary.turbine_steps >> 4;
	*out[1] = (tur -> primary.turbine_steps << 8) | (tur -> primary.turbine_tilt >> 8);
	*out[2] = (tur -> primary.turbine_tilt);
	*out[3] = (tur -> primary.motor_option << 7) | (tur -> primary.stepper_direction << 5) |  (tur -> primary.hold << 4) | tur_s -> data.packspace[2];
	
	*out[4] = tur_s -> data.packspace[0];
	*out[5] = tur_s -> data.packspace[1];
	*out[6] = (tur -> primary.state_duration >> 8);
	*out[7] = (tur -> primary.state_duration);
	}


void Translator_turbine::apply(uint8_t dec, uint8_t *out[16], class Turbine *tur, class Turbine_sensor *tur_s){
	//Serial.println("Apply");
	uint16_t act_pos = (uint16_t)tur -> primary.turbine_tilt;
	int16_t dest_pos = data.turbine_tilt - act_pos;
	switch((uint8_t)dec){
		case (uint8_t)srt_t:
			tur -> turn_on_turbine();
			break;
		
		case (uint8_t)stp_t:
			tur -> turn_off_turbine();
			break;

		//case mov_p: 
			
		//	tur -> set_direction(((dest_pos > 0)? 1: 0));
		//	tur -> set_steps(((dest_pos > 0)? dest_pos : dest_pos * -1));
		//	break;
			
		case (uint8_t)mov_s:
			tur -> primary.state_duration = data.state_duration;
			tur -> primary.hold = data.hold;
			tur -> set_direction(data.stepper_option);
			tur -> set_steps(data.turbine_steps);Serial.println(data.hold);
			//Serial.println(tur -> primary.hold);
			//Serial.println("dir" +String(tur -> primary.stepper_direction));
			break;
			
		case (uint8_t)sen_d:
			tur_s -> get_data();
			tur_s -> compose();
			get_data(out, tur, tur_s);
			data.has_data = true;
			break;
			
		//case spd_t:
		//	break;
			
		//case spd_m:
		//	tur -> primary.state_duration = data.state_duration;
		//	break;
	 
		}
		//Serial.println("Apply end");
	}
