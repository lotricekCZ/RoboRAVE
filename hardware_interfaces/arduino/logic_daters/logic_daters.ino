#define IRDUINO
//~ #define GNDUINO
//#define DEBUG   

#ifdef IRDUINO
#undef daters_logic_h
#undef driver_sensor_h
#include "../../libraries/daters_logic_ir/daters_logic_ir.h"

#endif
#ifdef GNDUINO
#undef daters_logic_h
#undef driver_sensor_ir_h
#include "../../libraries/daters_logic/daters_logic.h"
#endif

logic l;
sensor_driver s;
translator_sensor t;
chat c;



void setup() {
	pinMode(4, OUTPUT);
	Serial.begin(57600);
	
	l.main_chat = &c;
	l.main_driver = t.main_se_dr = &s;
	l.main_translator_sensor = &t;
	#ifdef GNDUINO
	l.my_add = GND;
	#endif
	#ifdef IRDUINO
	l.my_add = IR;
	#endif
	
	t.main_se_dr -> data.expo_time = 1300;
	t.main_se_dr -> hw_presets.adc_pin = 6;
	t.main_se_dr -> data.oversampling = 10;
	t.main_se_dr -> hw_presets.lowest_bit = PB2;
}



void loop() {
	//s.get_data();
	l.read();
	l.decide();
	#ifdef DEBUG
	
	for (uint8_t i = 0; i < 8; i++) {
	Serial.print(s.data.temp_data[i]);
	Serial.print("\t");
	
	}
	//digitalWrite(4, HIGH);
	#ifdef IRDUINO
	Serial.print(s.data.reference);
	Serial.print("\n\n\n");
	
	#endif
	#endif
	//~ delay(5);
}
