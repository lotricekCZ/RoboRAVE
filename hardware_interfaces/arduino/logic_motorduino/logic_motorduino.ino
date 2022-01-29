#define COOLDOWN 4500 
#include <Wire.h>
#include "../../libraries/motorduino_logic/motorduino_logic.h"

motor m1;
motor m2;

translator_turbine trans_t;
turbine_sensor trans_s;
turbine t;
chat c;
translator_motor tr;
Logic l(&m1, &m2, &t, &c, &tr, &trans_s, &trans_t);
void setup() {
  m1._motor.direction_pin = PD4 ;
  m1._motor.step_pin = PD3;
  m1.set_delays(10000, 10000);

  m2._motor.direction_pin = PD5 ;
  m2._motor.step_pin = PD6 ;
  m2.set_delays(10000, 10000);
  Wire.begin(7);
  Serial.begin(57600); 
  l.read();
  // put your setup code here, to run once:
  l.decide();
}

void loop() {
  // put your main code here, to run repeatedly:
  l.read();
  l.decide();
  m1.handle_in_background();
  m2.handle_in_background();
  t.handle_in_background();
//  Serial.println(String(m1.motor.remaining_steps)+"  "+String(m2.motor.remaining_steps));
//Serial.println(String(t.primary.turbine_steps));
}

void SerialEvent(){
  
  }
