// Contains helper functions for main and various other parts of the program.
// May need to be split into multiple files if too many helper functions exist.
// 
// Helper function categories:
//  - Config related (read, write, make, exists)
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present],
//
// Last update:
//  - 10/17/2023 (Jake):
//    Created file, added config helpers


#include <string>
#include <fstream>

#include "util/helper.h"

// =============================================================================
//                             CONFIG HELPERS
// =============================================================================

void helper::config::WriteConfig(bool use_gui, const std::string &style) {
  // opens/creates the file "config.cfg" in input/truncation mode
  // truncation mode overwrites everything previously in the file.
  std::fstream config("config.cfg", std::ios::out | std::ios::trunc);
  config << "GUI=";

  if (use_gui) {
    config << "true\n";
  }
  else {
    config << "false\n";
  }

  config << "style=" << style;

  config.close();

};


bool helper::config::UseGUI() {

  std::fstream file("config.cfg");

  // If the file doesn't exist, it has to be created
  if (!file.is_open()) {
    WriteConfig(false, "default");
    return false;
  }

  std::string line;

  // testing for errors in the file format
  if (!std::getline(file, line)) {
    file.close();
    WriteConfig(false, "default");
    return false;
  }

  if (line == "GUI=true") {
    file.close();
    return true;
  }

  else if (line != "GUI=false") {
    file.close();
    WriteConfig(false, "default");
    return false;
  }

  file.close();
  return false;

}


std::string helper::config::GetGUIStyle() {
// Works pretty much the same as UseGUI

  std::fstream file("config.cfg");
  
  std::string line;

  if (!std::getline(file, line)) {
    file.close();
    WriteConfig(true, "default");
    return "default";
  }

  if (!std::getline(file, line, '=')) {
    file.close();
    WriteConfig(false, "default");
    return "default";
  }

  if (!std::getline(file, line)) {
    file.close();
    WriteConfig(false, "default");
    return "default";
  }

  else {
    file.close();
    return line;
  }

}

// =============================================================================
//                           END CONFIG HELPERS
// =============================================================================