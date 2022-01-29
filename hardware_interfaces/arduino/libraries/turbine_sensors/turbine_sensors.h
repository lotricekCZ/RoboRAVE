#ifndef turbine_sensors_h
#define turbine_sensors_h
#include <Arduino.h>

class turbine_sensor{
	typedef struct d{
		unsigned data_0:10;
		unsigned data_1:10;
		unsigned oversampling:6;
		unsigned adc_0:3;
		unsigned adc_1:3;
		uint8_t packspace[3];
	};
	public:
		d data;
		void get_data();
		void compose();
		turbine_sensor(){
			data.adc_0 = 6;
			data.adc_1 = 7;
			data.oversampling = 5;
			};
};

#include "turbine_sensors.cxx"
#endif // turbine_sensors_h
