#ifndef translator_sensor_h
#define translator_sensor_h
#include "../driver_sensors/driver_sensor_array.h"


class translator_sensor{
	
	public:
		struct{
			uint16_t period;
			unsigned ready_flag:1;
			uint32_t last_change = 0;	
		}presets;
		uint8_t data[16];
		translator_sensor(){};
		sensor_driver *main_se_dr;
		void decompose(uint8_t in[16]);
		void compose();
		bool is_longer();
	
	};
#include "translator_sensor.cxx"
#endif
