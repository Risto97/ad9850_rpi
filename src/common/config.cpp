#include "config.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <libconfig.h++>
#include <sstream>

using namespace libconfig;
namespace fs = std::filesystem;

int Cfg::read() {
  Config cfg;
  fs::path cfg_path = get_cfg_path();

  try {
    cfg.readFile(cfg_path.c_str());
  } catch (const FileIOException &fioex) {
    // write();
    std::cerr << "I/O error while reading file." << std::endl;
    return (EXIT_FAILURE);
  } catch (const ParseException &pex) {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    return (EXIT_FAILURE);
  }

  Setting &root = cfg.getRoot();

  try {
    w_clk = cfg.lookup("w_clk");
    fq_ud = cfg.lookup("fq_ud");
    data = cfg.lookup("data");
    rst = cfg.lookup("rst");
    dds_clk = cfg.lookup("dds_clk");
  } catch (const SettingNotFoundException &nfex) {
    std::cerr << "Setting missing in configuration file." << std::endl;
    return (EXIT_FAILURE);
  }

  return 0;
}

void Cfg::write() {
  fs::path cfg_path = get_cfg_path();
  fs::path cfg_dir = cfg_path.parent_path();
  Config cfg;

  try {
    fs::create_directories(cfg_dir);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  Setting &root = cfg.getRoot();

  root.add("w_clk", Setting::TypeInt) = w_clk;
  root.add("fq_ud", Setting::TypeInt) = fq_ud;
  root.add("data", Setting::TypeInt) = data;
  root.add("rst", Setting::TypeInt) = rst;
  root.add("dds_clk", Setting::TypeInt) = dds_clk;

  try {
    cfg.writeFile(cfg_path.c_str());

  } catch (const FileIOException &fioex) {
    // cerr << "I/O error while writing file: " << output_file << endl;
    std::cout << "Error while writing cfg file" << std::endl;
    // return(EXIT_FAILURE);
  }
}

std::filesystem::path Cfg::get_cfg_path() {
  char *config_home;
  fs::path config_dir;
  fs::path config_file;

  config_home = std::getenv("XDG_CONFIG_HOME");
  if (config_home != NULL) {
    config_dir = config_home;
  } else {
    config_home = std::getenv("HOME");
    config_dir = config_home;
    config_dir /= ".config";
  }

  config_dir /= "ad9850_rpi";
  config_file = config_dir / "ad9850.cfg";

  return config_file;
}
