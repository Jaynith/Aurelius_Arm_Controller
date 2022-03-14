#ifndef _STEP_CTRL_H
#define _STEP_CTRL_H

#define DEFAULT_STEP_SIZE_uS  1000
#define CCW                   false
#define CW                    true

class stepper_controller {
private:
  uint8_t  _motor_pin, _direction_pin, _enable_pin;
  uint16_t _steps_for_full_turn;
  float    _gear_reduction;
  uint8_t  _limit_switch_pin;
  
  uint16_t _step_delay_uS;
  float    _current_angle;
  float    _motor_upper_limit_angle;

  bool _motor_calibrated;
  bool _limit_switch_ready;

  
public:
  stepper_controller(uint8_t motor_pin, uint8_t direction_pin, uint8_t enable_pin, uint16_t steps_for_full_turn, float gear_reduction);
  
  bool calibrateMotor();
  void setUpperLimit(float upper_limit);
  void setupLimitSwitch(uint8_t limit_switch_pin);
  
  void prepMotor(bool turn_direction);
  void turn(float angle);
  void stepMotor();

};

#endif
