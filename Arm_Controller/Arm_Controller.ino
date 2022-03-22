/*
*Authors : Janith Wijekoon, Marko Jurisic
*Date : 28/01/2022
*Purpose : Drive 6 axis robot arm actuated by stepper and servo motors.
*/

#include "libraries.h"
#include "potentiometer.h"
#include "stepper_controller.h"

struct potentiometer_data pot_1;
struct potentiometer_data pot_2;
struct potentiometer_data pot_3;
struct potentiometer_data pot_4;


stepper_controller motor_1 = stepper_controller(4, 2, 12, 200, 30);
stepper_controller motor_2 = stepper_controller(6, 5, 3, 200, 30);

String read_string; 
float motor_angle_1, motor_angle_2;

void setup() {
  Serial.begin(115200);

  
  potentiometerSetup(&pot_1, (int)A0, 1023, 0, 180);
  potentiometerSetup(&pot_2, (int)A1, 1023, 0, 180);
  potentiometerSetup(&pot_3, (int)A2, 1023, 0, 180);
  potentiometerSetup(&pot_4, (int)A3, 1023, 0, 180);

  /*
  motor_1.setupLimitSwitch(A7);
  motor_1.setUpperLimit(180);
  motor_1.calibrateMotor();*/
  
  
  motor_2.setupLimitSwitch(A7);
  motor_2.setUpperLimit(90);
  motor_2.calibrateMotor();  
}

void loop() { 

  motor_angle_1= readPotentiometer(&pot_2);
  motor_angle_2 = readPotentiometer(&pot_1);
  //motor_1.turn(motor_angle_1);
  motor_2.turn(motor_angle_2);

  
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
