#include <wiringPi.h>
#include <cmath>

#include "ad9850.hpp"

void AD9850::init(){
  wiringPiSetup();

  pinMode(clk_pin, OUTPUT);
  pinMode(fq_ud_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  pinMode(rst_pin, OUTPUT);

  digitalWrite(clk_pin, 0);
  digitalWrite(fq_ud_pin, 0);
  digitalWrite(data_pin, 0);
  digitalWrite(rst_pin, 0);
}

void AD9850::rst(){
  digitalWrite(clk_pin, 0);
  digitalWrite(fq_ud_pin, 0);

  _gpio_pulse(rst_pin, 1);
  _gpio_pulse(clk_pin, 1);

  digitalWrite(data_pin, 0);

  _gpio_pulse(fq_ud_pin, 1);
  _gpio_pulse(fq_ud_pin, 1);
}

void AD9850::run(unsigned int freq){
  unsigned long tuning_word = (freq* pow(2,32)) / DDS_CLK;

  digitalWrite(fq_ud_pin, 0);

  _shift_out(data_pin, clk_pin, tuning_word);
  _shift_out(data_pin, clk_pin, tuning_word >> 8);
  _shift_out(data_pin, clk_pin, tuning_word >> 16);
  _shift_out(data_pin, clk_pin, tuning_word >> 24);
  _shift_out(data_pin, clk_pin, 0x00);

  _gpio_pulse(fq_ud_pin, 1);
  digitalWrite(data_pin, 0);
}

void AD9850::run_for(unsigned int freq, unsigned int delay_ms, bool *keep_running){
  run(freq);
  _delay_ms_breakable(delay_ms, keep_running);
  rst();
}

void AD9850::sweep(unsigned start_freq, unsigned int stop_freq, unsigned int step_freq, unsigned int step_time, bool *keep_running){
  unsigned int range = stop_freq - start_freq;
  unsigned int steps = range / step_freq;
  unsigned int freq = start_freq;

  for(int i = 0; i < steps; i++){
    run(freq);

    if(!_delay_ms_breakable(step_time, keep_running))
      break;
    else
      freq += step_freq;
  }
  rst();
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

int _delay_ms_breakable(unsigned int delay_ms, bool *keep_running){
  for(int i=0; i < delay_ms; i++){
    delay(1);
    if(!(*keep_running))
      return 0;
  }
  return 1;
}
