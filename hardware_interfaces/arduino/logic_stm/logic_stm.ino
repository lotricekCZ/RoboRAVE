#define RS_enable 	PA8
#define COOLDOWN 	4500
#define INTER_DELAY 10000	// delay that makes sure others have time to express opinions / stop that annoyng thing
#include <Wire.h>

//~ TwoWire Wire2(2, I2C_FAST_MODE);
//~ #define Wire Wire2

#include <AMG88xx.h>

#include "../../libraries/logic_stm/logic.cpp"


Adafruit_AMG88xx 	amg;
lidar 				ldr;
thermo_driver 		thd;

chat				c;
translator_lidar	tl;
translator_therm	tt;
logic 				l;

/* main_thermocam;
 * main_lidar; 
 * main_chat; 
 * main_translator_lidar; 
 * main_translator_therm; 
 */


void setup() {
	
	l.main_thermocam = thd.main_thermocam =	&amg;
	l.main_lidar = tl.main_lidar = 		&ldr;
	tt.main_th_dr = 					&thd;
	l.main_translator_lidar = 			&tl;
	l.main_translator_therm = 			&tt;
	l.main_chat = 						&c;
	// put your setup code here, to run once:
	pinMode(RS_enable, OUTPUT);
	Serial2.begin(115200);
	
	byte error, address;
	int nDevices;
	
	Serial2.println("Scanning...");
	Serial2.println("FIRST...");
	
	nDevices = 0;
	for(address = 1; address < 127; address++) {
	// The i2c_scanner uses the return value of
	// the Write.endTransmisstion to see if
	// a device did acknowledge to the address.
	
	Wire.beginTransmission(address);
	error = Wire.endTransmission();
	
	if (error == 0) {
	  Serial2.print("I2C device found at address 0x");
	  if (address < 16) 
		Serial2.print("0");
	  Serial2.println(address, HEX);
	
	  nDevices++;
	}
	else if (error == 4) {
	  Serial2.print("Unknown error at address 0x");
	  if (address < 16) 
		Serial2.print("0");
	  Serial2.println(address, HEX);
	}    
	}
	if (nDevices == 0)
	Serial2.println("No I2C devices found");
	else
	Serial2.println("done");

	
	
	delay(1000);
	Serial2.print("START");
	Serial1.begin(115200);
	l.flags.has_therm = amg.begin();
	Serial2.print(__LINE__);
	}

void loop() {
	// put your main code here, to run repeatedly:
	l.read();
	ldr.handle_in_background();
	thd.handle_in_background();
	l.decide();
	}
