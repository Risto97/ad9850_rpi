#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <filesystem>

class Cfg {
public:
  int w_clk;
  int fq_ud;
  int data;
  int rst;
  int dds_clk;

  Cfg(int w_clk_p, int fq_ud_p, int data_p, int rst_p, int dds_clk_p) : w_clk(w_clk_p), fq_ud(fq_ud_p), data(data_p), rst(rst_p), dds_clk(dds_clk_p){}

  Cfg(){}

  int read();
  void write();

  std::filesystem::path get_cfg_path();

};

#endif
