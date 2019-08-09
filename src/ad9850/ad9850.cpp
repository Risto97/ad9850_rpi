#include <wiringPi.h>
#include <cmath>

#include "ad9850.hpp"

void ad9850_init(){
  wiringPiSetup();

  pinMode(W_CLK, OUTPUT);
  pinMode(FQ_UD, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(RST, OUTPUT);

  digitalWrite(W_CLK, 0);
  digitalWrite(FQ_UD, 0);
  digitalWrite(DATA, 0);
  digitalWrite(RST, 0);
}

void _shift_out(unsigned int pin, unsigned int clk, unsigned int val){
  int i = 0;
  for(i=0; i<8; i++){
    digitalWrite(pin, !!(val & (1 << i)));

    _gpio_pulse(clk, 1);
  }

}

void _gpio_pulse(unsigned int pin, unsigned int delay_us){
  digitalWrite(pin, 0);
  delayMicroseconds(delay_us);
  digitalWrite(pin, 1);
  delayMicroseconds(delay_us);
  digitalWrite(pin, 0);

}
void ad9850_rst(){
  digitalWrite(W_CLK, 0);
  digitalWrite(FQ_UD, 0);

  _gpio_pulse(RST, 1);
  _gpio_pulse(W_CLK, 1);

  digitalWrite(DATA, 0);

  _gpio_pulse(FQ_UD, 1);
  _gpio_pulse(FQ_UD, 1);
}

int _delay_ms_breakable(unsigned int delay_ms, bool *keep_running){
  for(int i=0; i < delay_ms; i++){
    delay(1);
    if(!(*keep_running))
      return 0;
  }
  return 1;
}

void ad9850_run(unsigned int freq){
  unsigned long tuning_word = (freq* pow(2,32)) / DDS_CLK;

  digitalWrite(FQ_UD, 0);

  _shift_out(DATA, W_CLK, tuning_word);
  _shift_out(DATA, W_CLK, tuning_word >> 8);
  _shift_out(DATA, W_CLK, tuning_word >> 16);
  _shift_out(DATA, W_CLK, tuning_word >> 24);
  _shift_out(DATA, W_CLK, 0x00);

  _gpio_pulse(FQ_UD, 1);
  digitalWrite(DATA, 0);
}

void ad9850_run_for(unsigned int freq, unsigned int delay_ms, bool *keep_running){
  ad9850_run(freq);
  _delay_ms_breakable(delay_ms, keep_running);
  ad9850_rst();
}

void ad9850_sweep(unsigned start_freq, unsigned int stop_freq, unsigned int step_freq, unsigned int step_time, bool *keep_running){
  unsigned int range = stop_freq - start_freq;
  unsigned int steps = range / step_freq;
  unsigned int freq = start_freq;

  for(int i = 0; i < steps; i++){
    ad9850_run(freq);

    if(!_delay_ms_breakable(step_time, keep_running))
      break;
    else
      freq += step_freq;
  }
  ad9850_rst();
}
