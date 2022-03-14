/*
*Authors : Janith Wijekoon, Marko Jurisic
*Date : 28/01/2022
*Purpose : Easily read and keep track of voltage inputs and properties from multiple potentiometers.
*/

#include "libraries.h"
#include "potentiometer.h"

void potentiometerSetup(struct potentiometer_data * setup_data, int input_pin, int max_v, uint16_t scale_upper_bound, uint16_t scale_lower_bound){
  setup_data->pot_pin = input_pin;
  setup_data->max_v = max_v;
  setup_data->scale_upper_bound = scale_upper_bound;
  setup_data->scale_lower_bound = scale_lower_bound;
}

int readPotentiometer(struct potentiometer_data * input_data){
  int potentiometer_val = analogRead(input_data->pot_pin);

  return map(potentiometer_val, 0, input_data->max_v, input_data->scale_lower_bound, input_data->scale_upper_bound);
}
