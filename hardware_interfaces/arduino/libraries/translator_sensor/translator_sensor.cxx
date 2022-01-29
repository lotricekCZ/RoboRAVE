#include <translator_sensor.h>


void Translator_sensor::decompose(uint8_t in[16]){
	presets.period = in[0] << 8 | in[1];
	main_se_dr -> data.oversampling = in[2] & 0b11111;
	main_se_dr -> data.expo_time = in[3] << 8 | in[4] >> 4;
	#ifdef DEBUG
	Serial.println(String(presets.period) +"     "+ String(main_se_dr -> data.oversampling) + "    " + String(main_se_dr -> data.expo_time));
	#endif
	}
	
bool Translator_sensor::is_longer(){
	uint32_t now = micros();
	if((presets.last_change + presets.period * 6) < now){
		main_se_dr -> get_data();
		presets.last_change = now;
		return true;
		}
	return false;
	}

void Translator_sensor::compose(){
	for(uint8_t i = 0; i < main_se_dr ->t_data_l; i++){
		data[i] = main_se_dr -> data.temp_data[i] >> 2;
		data[main_se_dr -> t_data_l + i/4] = ((main_se_dr -> data.temp_data[i] & 0b11) << (6 -(i%4)*2));
		}
	}
