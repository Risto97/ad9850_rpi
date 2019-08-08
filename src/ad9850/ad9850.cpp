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

void ad9850_run_for(unsigned int freq, unsigned int delay_ms){
  ad9850_set_freq(freq);
  delay(delay_ms);
  ad9850_rst();
}

void ad9850_set_freq(unsigned int freq){
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
