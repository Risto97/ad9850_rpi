#ifndef AD9850_HPP_
#define AD9850_HPP_

#define W_CLK 1
#define FQ_UD 4
#define DATA 5
#define RST 6

#define DDS_CLK 125000000

void ad9850_init();
void ad9850_rst();
void _gpio_pulse(unsigned int pin, unsigned int delay_us);
void _shift_out(unsigned int pin, unsigned int clk, unsigned int val);
void ad9850_set_freq(unsigned int freq);
void ad9850_run_for(unsigned int freq, unsigned int delay_ms);

#endif
