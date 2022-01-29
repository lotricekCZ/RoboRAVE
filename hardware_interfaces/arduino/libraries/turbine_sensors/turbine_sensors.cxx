#include <turbine_sensors.h>

void Turbine_sensor::get_data(){
	uint16_t out[2] = {0,0};
	for(uint8_t o = 0; o < data.oversampling; o++){
		out[0] += analogRead(data.adc_0);
		out[1] += analogRead(data.adc_1);
		}
	data.data_1 = out[1]/data.oversampling;
	data.data_0 = out[0]/data.oversampling;
	}
	
void Turbine_sensor::compose(){
	data.packspace[0] = data.adc_0 >> 2;
	data.packspace[1] = data.adc_1 >> 2;
	data.packspace[2] = ((data.adc_0 & 0b11) << 2) | ((data.adc_1 & 0b11) << 0);
	}
