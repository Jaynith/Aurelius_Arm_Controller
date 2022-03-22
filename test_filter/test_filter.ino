#include "libraries.h"
#include "iir_filter.h"

/*
float numerator[] = {0.02145, 0.0429, 0.02145};
float denominator[] = {1, -1.696, 0.7815};
*/

float numerator[] =   {0.1046, 0.2091, 0.1046};
float denominator[] = {1, -0.9827, 0.4009};


float f1, f2, amp1, amp2;
float S1, S2, S3, S4;
float current_time, previous_time;

float time_step_uS;
int time_incr_uS;


iir_filter filt1 = iir_filter(numerator, 3, denominator, 3, 15*1000);

void setup () {

  Serial.begin(115200);

  f1 = 1;
  amp1 = 100;

  f2 = 16;
  amp2 = 20;

  time_incr_uS = 2; 
  time_step_uS = 0.0;

  previous_time = micros();

}

void loop(){

  float time_diff;

  current_time = micros();
  if (current_time - previous_time >= time_incr_uS){
    time_step_uS += (current_time - previous_time);
    time_diff = current_time - previous_time;
    previous_time = current_time;

    S1 = amp1 * sin(2 * PI * f1 * time_step_uS / 1000000);
    S2 = amp2 * sin(2 * PI * f2 * time_step_uS / 1000000);

    S3 = S1 + S2;
    filt1.run_filter_instance(S2, &S4);
    
  /*


  */
    Serial.println(S2);

    //Serial.print(" | ");
    //Serial.println(S4);
    
  }

}