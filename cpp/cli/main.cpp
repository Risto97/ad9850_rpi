#include <iostream>

#include "cxxopts.hpp"

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
      unsigned int run_time = 0;

      options
        .allow_unrecognised_options()
        .add_options()
        ("start", "start with frequency", cxxopts::value<unsigned int>(freq))
        ("time", "run for time in ms", cxxopts::value<unsigned int>(run_time))
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
          std::cout << "Setting frequency: " << freq << std::endl;
        }
      if(result.count("time"))
        {
          std::cout << "Run time: " << run_time << std::endl;
        }

      return result;

    } catch(const cxxopts::OptionException &e)
    {
      std::cout << "error parsing options: " << e.what() <<std::endl;
      exit(1);
    }
}

int main(int argc, char *argv[]){
  auto result = parse(argc, argv);
  auto arguments = result.arguments();
  std::cout << "Saw " << arguments.size() << " arguments" << std::endl;

  return 0;
}
