#ifndef AD9850_HPP_
#define AD9850_HPP_

#include "config.hpp"

// #define W_CLK 1
// #define FQ_UD 4
// #define DATA 5
// #define RST 6

#define DDS_CLK 125000000

class AD9850 {
private:
  unsigned int clk_pin, fq_ud_pin, data_pin, rst_pin;
  unsigned int dds_clk;

public:
  AD9850(unsigned int w_clk_p, unsigned int fq_ud_p, unsigned int data_p,
         unsigned int rst_p, unsigned int dds_clk_p)
      : clk_pin(w_clk_p), fq_ud_pin(fq_ud_p), data_pin(data_p), rst_pin(rst_p),
        dds_clk(dds_clk_p) {}

  AD9850(Cfg *cfg)
    : clk_pin(cfg->w_clk), fq_ud_pin(cfg->fq_ud), data_pin(cfg->data), rst_pin(cfg->rst),
      dds_clk(cfg->dds_clk) {}

  void set_vals(Cfg *cfg){
    clk_pin = cfg->w_clk;
    fq_ud_pin = cfg->fq_ud;
    data_pin = cfg->data;
    rst_pin = cfg->rst;
    dds_clk = cfg->dds_clk;
  }

  void init();
  void rst();

  void run(unsigned int freq);

  void run_for(unsigned int freq, unsigned int delay_ms,
               bool *keep_running);

  void sweep(unsigned start_freq, unsigned int stop_freq,
             unsigned int step_freq, unsigned int step_time,
             bool *keep_running);

};

void _gpio_pulse(unsigned int pin, unsigned int delay_us);
void _shift_out(unsigned int pin, unsigned int clk, unsigned int val);
int _delay_ms_breakable(unsigned int delay_ms, bool *keep_running);

#endif
