#include <iostream>
#include <wiringPi.h>

#include "cxxopts.hpp"
#include "ad9850.hpp"

cxxopts::ParseResult
parse(int argc, char * argv[])
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
        ("start", "start with frequency", cxxopts::value<unsigned int>(freq))
        ("time", "run for time in ms", cxxopts::value<unsigned int>(run_time_ms))
        ("stop", "stop ad9850")
        ("help", "Print help");

      auto result = options.parse(argc, argv);

      if(result.count("help"))
        {
          std::cout << options.help({"", "Group"}) << std::endl;
          exit(0);
        }

      if(result.count("start"))
        {
          std::cout << "Starting with frequency: " << freq << std::endl;
          ad9850_run(freq);
        }
      if(result.count("time") and result.count("start"))
        {
          std::cout << "Run time: " << run_time_ms << std::endl;
          bool t_val = true;
          ad9850_run_for(freq, run_time_ms, &t_val);
        }
      else if(result.count("time") and !result.count("start")){
        std::cout << "Please enter frequency" << std::endl;
      }
      if(result.count("stop"))
        {
          std::cout << "Stoping AD9850: " << std::endl;
          ad9850_rst();
        }

      return result;

    } catch(const cxxopts::OptionException &e)
    {
      std::cout << "error parsing options: " << e.what() <<std::endl;
      exit(1);
    }
}

int main(int argc, char *argv[]){
  ad9850_init();
  ad9850_rst();

  auto result = parse(argc, argv);
  auto arguments = result.arguments();

  return 0;
}
