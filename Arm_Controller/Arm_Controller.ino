/*
*Authors : Janith Wijekoon, Marko Jurisic
*Date : 28/01/2022
*Purpose : Drive 6 axis robot arm actuated by stepper and servo motors.
*/

#include "potentiometer.h"
#include "stepper_controller.h"

struct potentiometer_data pot_1;
struct potentiometer_data pot_2;
struct potentiometer_data pot_3;
struct potentiometer_data pot_4;

stepper_controller motor_1 = stepper_controller(7, 8, 9, 200, 30);

String read_string;
float motor_angle;

void setup() {
  Serial.begin(115200);
  
  potentiometerSetup(&pot_1, (int)A1, 887, 0, 180);
  potentiometerSetup(&pot_2, (int)A2, 887, 0, 180);
  potentiometerSetup(&pot_3, (int)A3, 887, 0, 180);
  potentiometerSetup(&pot_4, (int)A4, 887, 0, 180);
  
  
  motor_1.setupLimitSwitch(10);
  motor_1.setUpperLimit(180);
  motor_1.calibrateMotor(); 
  
}

void loop() {

  motor_angle = readPotentiometer(&pot_2);
  motor_1.turn(motor_angle);

  Serial.print("P1: ");
  Serial.print(readPotentiometer(&pot_1));
  Serial.print("| P2: ");
  Serial.print(readPotentiometer(&pot_2));
  Serial.print("| P3: ");
  Serial.print(readPotentiometer(&pot_3));
  Serial.print("| P4: ");
  Serial.println(readPotentiometer(&pot_4));
  
  
  delay(50);
}
