#ifndef _POTEN_H
#define _POTEN_H


//function declarations 

void potentiometerSetup(struct potentiometer_data * setup_data, int input_pin, int max_v, uint16_t scale_upper_bound, uint16_t scale_lower_bound);
uint16_t readPotentiometer(struct potentiometer_data * input_data);

//structures

typedef struct potentiometer_data{
  int       pot_pin;
  int       max_v;
  uint16_t  scale_upper_bound;
  uint16_t  scale_lower_bound;
}potentiometer_data;

#endif 
