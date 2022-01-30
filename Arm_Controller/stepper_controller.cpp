/*
*Authors : Janith Wijekoon, Marko Jurisic
*Date : 28/01/2022
*Purpose : Precisely drive multiple unipolar stepper motors and keep track of each motor's unique properties/settings.
*/

#include "libraries.h"
#include "stepper_controller.h"

uint8_t stepper_controller::_motor_pin, stepper_controller::_direction_pin, stepper_controller::_enable_pin;
uint16_t stepper_controller::_steps_for_full_turn;
float   stepper_controller::_gear_reduction;
uint8_t stepper_controller::_limit_switch_pin;

uint16_t stepper_controller::_step_delay_uS;
float stepper_controller::_current_angle;
float stepper_controller::_motor_upper_limit_angle;

bool stepper_controller::_motor_calibrated;
bool stepper_controller::_limit_switch_ready;

stepper_controller::stepper_controller(uint8_t motor_pin, uint8_t direction_pin, uint8_t enable_pin, uint16_t steps_for_full_turn, float gear_reduction){
  _motor_pin = motor_pin;
  _direction_pin = direction_pin;
  _enable_pin = enable_pin;

  _steps_for_full_turn = steps_for_full_turn;
  _gear_reduction = gear_reduction;
  _current_angle = 0;
  _motor_upper_limit_angle = 150;

  _motor_calibrated = false;
  _limit_switch_ready = false;
  
  pinMode(_motor_pin, OUTPUT);
  pinMode(_direction_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);


  digitalWrite(_motor_pin, LOW);
  digitalWrite(_direction_pin, LOW);
  digitalWrite(_enable_pin, LOW);
  
  _motor_calibrated = false; 
  _step_delay_uS = DEFAULT_STEP_SIZE_uS;
}

void stepper_controller::setUpperLimit(float upper_limit){
  if (upper_limit > 0)
    _motor_upper_limit_angle = upper_limit;
}

void stepper_controller::setupLimitSwitch(uint8_t limit_switch_pin){
  _limit_switch_pin = limit_switch_pin;
  _limit_switch_ready = true;

  pinMode(_limit_switch_pin, INPUT);
}

void stepper_controller::turn(float angle){
  if (angle > _motor_upper_limit_angle)
    angle = _motor_upper_limit_angle;
  else if (angle < 0)
    angle = 0;
  float delta_angle = angle - _current_angle;
  int steps = _steps_for_full_turn * _gear_reduction * delta_angle / 360;
  if (_motor_calibrated == true){
    if (steps >= 0)
      prepMotor(CCW);
    else {
      prepMotor(CW);
      steps = abs(steps);
    }
    for (int x = 0; x < steps; x++){
      stepMotor();
    }
    _current_angle = angle;
  }
}

bool stepper_controller::calibrateMotor(){
  int switch_hit = HIGH;
  uint16_t step_count = 0;
  if (_limit_switch_ready == false){
    _motor_calibrated = false;
    return false;
  }
  else {
    prepMotor(CW);
    while (switch_hit == HIGH && step_count <= 10000){
      switch_hit = digitalRead(_limit_switch_pin);
      step_count++;
      stepMotor();
    }
    if (step_count <= 10000){
      _current_angle = 0;
      _motor_calibrated = true;
      return true;
    }
    else {
      _motor_calibrated = false;
      return false;    
    }
  }
}

void stepper_controller::prepMotor(bool turn_direction){
  digitalWrite(_enable_pin, LOW);
  if (turn_direction == CW)
    digitalWrite(_direction_pin, LOW);
  else if (turn_direction == CCW)
    digitalWrite(_direction_pin, HIGH);
}

void stepper_controller::stepMotor(){
  digitalWrite(_motor_pin, HIGH);
  delayMicroseconds(_step_delay_uS);
  digitalWrite(_motor_pin, LOW);
  delayMicroseconds(_step_delay_uS);
}
