#include <string.h>
#include "../turbine/turbine.h"
#include "translator_turbine.h"

void translator_turbine::fill_input(uint8_t in[msg_std::message_space_size]){
	//Serial.println("fill");
	for(uint8_t i = 0; i < msg_std::message_space_size; i++){
		input[i] = in[i];
		//Serial.println(in[i]);
		}
	//Serial.println("fillend");
	}
	
void translator_turbine::decompose(){
	data.state_duration = (input[0] << 8 | input[1]) >> 2;
	data.turbine_steps = ((input[1] & 0b11) << 10 | input[2] << 2 | input[3] >> 6);
	data.turbine_tilt = input[4] << 5 | input[5] >> 3;
	data.stepper_option = input[3] >> 4;
	data.motor_option = input[3] >> 3;
	data.option = input[3];
	data.hold = input[4] >> 7;
	Serial.println(data.hold);//Serial.println(data.turbine_steps);
	}
	
void translator_turbine::get_data(uint8_t *out[msg_std::message_space_size], class turbine *tur, class turbine_sensor *tur_s){
	memset(out[0], 0, msg_std::message_space_size); // set array to zero
	translator_turbine::decomposed_data payload{
		tur -> primary.state_duration,
		tur -> primary.turbine_steps,
		tur -> primary.turbine_tilt,
		tur -> primary.stepper_direction,
		0, /// TODO: fan_speed
		tur -> primary.motor_option,
		tur -> primary.hold,
		0,
		0
		};
	//~ data.packspace[2],
	
	//~ *out[4] = tur_s -> data.packspace[0];
	//~ *out[5] = tur_s -> data.packspace[1];
	}


void translator_turbine::apply(uint8_t dec, uint8_t *out[msg_std::message_space_size], class turbine *tur, class turbine_sensor *tur_s){
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

		case (uint8_t)mov_p:
			tur -> set_direction((uint8_t)(dest_pos > (tur -> primary.turbine_tilt)));
			tur -> set_steps(abs((int32_t)((int32_t)dest_pos - (int32_t)tur -> primary.turbine_tilt)));
			break;
			
		case (uint8_t)mov_s:
			tur -> primary.state_duration = data.state_duration;
			tur -> primary.hold = data.hold;
			tur -> set_direction(data.stepper_option);
			tur -> set_steps(data.turbine_steps);
			Serial.println(data.hold);
			//Serial.println(tur -> primary.hold);
			//Serial.println("dir" +String(tur -> primary.stepper_direction));
			break;
			
		case (uint8_t)sen_d:
			tur_s -> get_data();
			tur_s -> compose();
			get_data(out, tur, tur_s);
			data.has_data = true;
			break;
			
		case (uint8_t)spd_t:
			tur -> res = ((data.fan_speed <= 180)? data.fan_speed: 180) / 64 ;
			break;
			
		case (uint8_t)spd_m:
			tur -> primary.state_duration = data.state_duration;
			break;
	 
		}
		//Serial.println("Apply end");
	}
