#ifndef _IIR_FILTER_H
#define _IIR_FILTER_H

#define FILTER_BUFFER_LENGTH  3 //must be at least 2

class iir_filter{
private:
  float    _sample_time;
  float    _input, _output;  
  float   *_numerator, *_denominator;
  float  **_filter_buffer;
  uint8_t  _num_size, _den_size, _filter_buffer_width;

  double   _current_time, _previous_time;
  bool     _kickstart_filter;

public:
  iir_filter(float * numerator, uint8_t num_size,  float * denominator, uint8_t den_size, float sample_time);
  bool run_filter_instance(float data_in, float * data_out);
  float filter_data(float data_in);
  void increment_filter_buffer_index(int b_index);
  void full_reset_buffer();
};

#endif
