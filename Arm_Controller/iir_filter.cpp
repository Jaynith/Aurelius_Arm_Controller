#include "libraries.h"
#include "iir_filter.h"

iir_filter::iir_filter(float * numerator, uint8_t num_size,  float * denominator, uint8_t den_size, float sample_time){

  int x = 0, y = 0;
  
  _num_size = num_size;
  _den_size = den_size;

  _filter_buffer_width = max(_num_size, _den_size) - 1;

  _denominator = (float*)malloc(_den_size * sizeof(float));
  _numerator = (float*)malloc(_num_size * sizeof(float));

  for (x = 0; x < _den_size; x++){
    _denominator[x] = denominator[x];
  }
  for (x = 0; x < _num_size; x++){
    _numerator[x] = numerator[x];
  }
  
  _sample_time = sample_time; 
  _kickstart_filter = true;

  _filter_buffer = (float**)malloc(_filter_buffer_width * sizeof(float*));
  for (x = 0; x < _filter_buffer_width; x++){
    _filter_buffer[x] = (float*)malloc(FILTER_BUFFER_LENGTH * sizeof(float));
    for (y = 0; y < FILTER_BUFFER_LENGTH; y++)
      _filter_buffer[x][y] = 0.0;
  }
  _previous_time = micros();
}

bool iir_filter::run_filter_instance(float data_in, float * data_out){
  _current_time = micros();
  if ((_current_time-_previous_time) >= _sample_time){
    _previous_time = _current_time;
    
    if (_kickstart_filter == true || (_current_time-_previous_time) >= _sample_time*1.5){
      full_reset_buffer();
      _kickstart_filter = false;
    }
    *data_out = filter_data(data_in);
    return true;
  }
  else {
    return false;
  }
}

float iir_filter::filter_data(float data_in){

  int   x = 0, y = 0;
  float y_n, x_n;

  x_n = data_in;
  y_n = _numerator[0]*x_n + _filter_buffer[0][FILTER_BUFFER_LENGTH-1];

  for (x = 0; x < _filter_buffer_width; x++){
    increment_filter_buffer_index(x);
    _filter_buffer[x][FILTER_BUFFER_LENGTH-1] = 0;
    if (x < _num_size - 1)
      _filter_buffer[x][FILTER_BUFFER_LENGTH-1] += x_n * _numerator[x+1];
    if (x < _den_size - 1)
      _filter_buffer[x][FILTER_BUFFER_LENGTH-1] -= y_n * _denominator[x+1];
    if (x < _filter_buffer_width - 1)
      _filter_buffer[x][FILTER_BUFFER_LENGTH-1] += _filter_buffer[x+1][FILTER_BUFFER_LENGTH-1];
  }

  return y_n;
}

void iir_filter::full_reset_buffer(){
  int x = 0, y = 0;
  for (x = 0; x < _filter_buffer_width; x++){
    for (y = 0; y < FILTER_BUFFER_LENGTH; y++)
      _filter_buffer[x][y] = 0.0;
  }
}

void iir_filter::increment_filter_buffer_index(int b_index){
  int x = 0;
  if (b_index >= 0 && b_index < _filter_buffer_width){
    for (x = 0; x < FILTER_BUFFER_LENGTH-1; x++){
      _filter_buffer[b_index][x] = _filter_buffer[b_index][x+1];
    }
  }
}
