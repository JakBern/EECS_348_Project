// Contains helper functions for main and various other parts of the program.
// May need to be split into multiple files if too many helper functions exist.
// 
// Helper function categories:
//  - Config related (read, write, make, exists)
//  - String parsing (TrimStart, TrimEnd, )
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present],
//
// Last update:
//  - 11/23/2023 (Jake):
//    Created file, added config helpers


#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

#include "util/helper.hpp"

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


// =============================================================================
//                           STRING PARSING HELPERS
// =============================================================================

bool helper::str_func::char_is_in(const char* c, const char* comp_list) {
  for (int i = 0; i < sizeof(comp_list) / sizeof(char); i++) {
    if (comp_list[i] == *c) {
        return true;
    }
  }
  return false;
}

std::string& helper::str_func::TrimStart(std::string& str, 
                                      const char* whitespace = " \t\f\n\r\v") {
  str.erase(0, str.find_first_not_of(whitespace));
  return str;
}
    
std::string& helper::str_func::TrimEnd(std::string& str, 
                                      const char* whitespace = " \t\f\n\r\v") {
  str.erase(str.find_last_not_of(whitespace) + 1);
  return str;
}

std::string& Trim(std::string& str, 
                      const char* whitespace = " \t\f\n\r\v") {
  return helper::str_func::TrimEnd(helper::str_func::TrimStart(str));
}

std::string& helper::str_func::RemoveWhitespace(std::string& str) {
  str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
  return str;
}

std::string helper::str_func::GetWord(std::string& str,
                    std::string::iterator& iter,
                    const char* whitespace = " \t\f\n\r\v") {
  std::string::iterator first = iter;
  for (; 
      first != str.end() && helper::str_func::char_is_in(&*first, whitespace); 
      first++){}
  std::string::iterator last = first;
  for (; 
      last != str.end() && !(helper::str_func::char_is_in(&*last, whitespace)); 
      last++) {}
  iter = last;
  std::string output(first, last);
  return output;
}

std::vector<std::string> helper::str_func::Split(std::string& str,
                                const char* whitespace = " \t\f\n\r\v") {
  std::vector<std::string> output;
  std::string word;
  std::string::iterator iter = str.begin();
  while (true) {
    word = helper::str_func::GetWord(str, iter, whitespace);
    if (word != "") {
      output.push_back(word);
    }
    else {
      break;
    }
  }
  return output;
}

// =============================================================================
//                          END STRING PARSING HELPERS
// =============================================================================