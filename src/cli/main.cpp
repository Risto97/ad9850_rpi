#include <iostream>
// #include <wiringPi.h>

#include "cxxopts.hpp"
#include "ad9850.hpp"
#include "config.hpp"

cxxopts::ParseResult
parse(int argc, char * argv[], AD9850 *ad9850)
{
  try
    {
      cxxopts::Options options("AD9850", "AD9850 cli application.");

      options
        .positional_help("[optional args]")
        .show_positional_help();

      unsigned int freq = 0;
      unsigned int run_time_ms = 0;

      options
        .allow_unrecognised_options()
        .add_options()
        ("run", "Run with frequency arg", cxxopts::value<unsigned int>(freq))
        ("run-for", "Run with frequency arg[0] for time arg[1] in ms", cxxopts::value<std::vector<unsigned int>>())
        ("sweep", "Sweep from freq arg[0] to freq arg[1] with step freq arg[2] and step time arg[3] in Hz and ms", cxxopts::value<std::vector<unsigned int>>())
        ("stop", "Stop ad9850")
        ("read-cfg", "Prints tuple of configuration parameters to stdout")
        ("write-cfg", "Write cfg, arg is tuple = w_clk,fq_ud,data,rst,dds_clk", cxxopts::value<std::vector<unsigned int>> ())
        ("help", "Show help");

      auto result = options.parse(argc, argv);

      if(result.count("help"))
        {
          std::cout << options.help({"", "Group"}) << std::endl;
          exit(0);
        }

      if(result.count("run"))
        {
          std::cout << "Running with frequency: " << freq << " Hz" << std::endl;
          ad9850->run(freq);
        }

      if(result.count("run-for")){
        const auto values = result["run-for"].as<std::vector<unsigned int>>();
        std::cout << "Running with frequency " << values[0] << " Hz" << " for " << values[1] << " ms" << std::endl;

        bool t_val = true;
        ad9850->run_for(values[0], values[1], &t_val);
      }

      if(result.count("sweep")){
        const auto values = result["sweep"].as<std::vector<unsigned int>>();
        std::cout << "Sweeping from " << values[0] << " Hz" << " to " << values[1] << " Hz, ";
        std::cout << "with step " << values[2] << " Hz" << " and step time " << values[3] << " ms" << std::endl;

        bool t_val = true;
        ad9850->sweep(values[0], values[1], values[2], values[3], &t_val);
      }

      if(result.count("stop"))
        {
          std::cout << "Stoping AD9850: " << std::endl;
          ad9850->rst();
        }

      return result;

    } catch(const cxxopts::OptionException &e)
    {
      std::cout << "error parsing options: " << e.what() <<std::endl;
      exit(1);
    }
}

int main(int argc, char *argv[]){
  Cfg *cfg = new Cfg();
  int ret = cfg->read();
  AD9850 *ad9850 = new AD9850(cfg);
  ad9850->init();
  ad9850->rst();

  auto result = parse(argc, argv, ad9850);
  auto arguments = result.arguments();

  return 0;
}
