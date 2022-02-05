#include "../../libraries/lidar/lidar.cpp"
lidar l;
void setup() {
  // put your setup code here, to run once:
	pinMode(LED_BUILTIN, OUTPUT);
	Serial2.begin(115200);
	//~ Serial2.begin(57600);
	Serial1.begin(115200);
}

void loop() {
	// put your main code here, to run repeatedly:
	l.handle_in_background();
}
