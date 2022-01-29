#include <driver_sensor_array.h>
#include <Arduino.h>

void sensor_driver::get_data(){
	uint16_t out[8] = {0,0,0,0,0,0,0,0};
	for(uint8_t o = 0; o < data.oversampling; o++){
		do{
			set_mux(data.combination);
			delayMicroseconds(data.expo_time);
			out[data.combination] += analogRead(hw_presets.adc_pin);
			//Serial.println("\t\t\t\t\t"+String((uint8_t)*hw_presets.mux_reg)+"\n");
			delayMicroseconds(data.expo_time/2);
			}while(++data.combination != 0);
		}
	for(uint8_t i = 0; i < 8; i++){
		data.temp_data[i] = out[i] / data.oversampling;
		}
	}

void sensor_driver::set_mux(uint8_t combination){
	PORTB = (PORTB &~(0b111 << hw_presets.lowest_bit)) | (combination << hw_presets.lowest_bit);
	//Serial.println(PORTB, BIN);
	//switch((uint8_t)hw_presets.mux_reg){
		//case (uint8_t)&PORTD:
			//PORTD = (PORTD &~(0b111 << hw_presets.lowest_bit)) | (combination << hw_presets.lowest_bit);
			//// PORTD &= ~ 0b111 << hw_presets.lowest_bit;
			//// PORTD |= combination << hw_presets.lowest_bit;
			//break;
		//case (uint8_t)&PORTC:
			//PORTC = (PORTC &~(0b111 << hw_presets.lowest_bit)) | (combination << hw_presets.lowest_bit);
			//// PORTC &= ~ 0b111 << hw_presets.lowest_bit;
			//// PORTC |= combination << hw_presets.lowest_bit;
			//break;
		//case (uint8_t)&PORTB:
			//PORTB = (PORTB &~(0b111 << hw_presets.lowest_bit)) | (combination << hw_presets.lowest_bit);
			//break;
		//}
	}
