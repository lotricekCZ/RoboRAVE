#ifndef driver_sensor_ir_h
#define driver_sensor_ir_h
class sensor_driver{
	protected:
		typedef struct dt{
			uint16_t temp_data[8];
			unsigned combination:3;
			unsigned oversampling:5;
			unsigned expo_time:16;
			unsigned reference:10;
			};
			
		typedef struct hw_info{
			volatile uint8_t *mux_reg;
			unsigned adc_pin:3;
			unsigned lowest_bit:3;
			};
	public:
		hw_info hw_presets;
		sensor_driver(){
			DDRB |= 0b00011100;
			};
	protected:
		void set_mux(uint8_t combination);
	public:
		dt data;
		uint8_t t_data_l = (sizeof(data.temp_data) / sizeof(data.temp_data[0]));
		void get_data();
		
	};
#include "driver_sensor_irduino.cxx"
#endif
