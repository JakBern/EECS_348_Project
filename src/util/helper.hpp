// Contains helper functions for main and various other parts of the program.
// May need to be split into multiple files if too many helper functions exist.
// 
// Helper function categories:
//  - Config related (exists, write, make)
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present],
//
// Last update:
//  - 10/17/2023 (Jake): Created file, added config helpers

#ifndef UTIL_HELPER_H_
#define UTIL_HELPER_H_

#include <string>
#include <vector>
#include <iterator>

#include "flags.hpp"

namespace helper {


  // helper functions related to the config file
  namespace config {

    // Writes to a config file, overwriting the previous settings.
    // These settings are used on launch to determine if the program should be
    // in GUI or command line mode, and what style the GUI should be in if in 
    // GUI mode.
    //
    // Writes to the file like this (remove <> and interpret values)
    // GUI=<UseGUI>
    // style=<style>
    //
    // Note that UseGUI is written to the file as a string, ie "true" or "false"
    // (no quotes).
    void WriteConfig(bool UseGUI, const std::string& style);

    // Reads from the config file and returns whether or not the program will be
    // running in GUI mode. If not, the program will run in command line mode.
    //
    // If the config file is missing or contains errors, a new config file
    // is created using the default settings:
    // GUI=false
    // style=default
    //
    // Returns false if no config file exists or config file is errored.
    bool UseGUI();

    // Reads from the config file and returns a string representing the
    // GUI style to be used. If the config file doesn't exist or has errors,
    // a new config file is created and the old one overwritten and this
    // 
    // If the config file is missing or contains errors, a new config file
    // is created using the settings:
    // GUI=true
    // style=default
    //
    // This function is assumed to be called after determining the GUI is
    // being used, so it defaults to setting GUI config to true.
    //
    // Returns "default" if no config file exists or config file is errored.
    std::string GetGUIStyle();

  }

  // Helper functions related to parsing strings.
  //
  // Some of these implementations taken from: 
  // https://stackoverflow.com/questions/1798112/
  // removing-leading-and-trailing-spaces-from-a-string
  namespace str_func {

    // Checks if the passed in character c matches any characters in the passed
    // in string literal comp_list, eg "if 'a' in 'abcd' (true)".
    bool char_is_in(const char& c, const char* comp_list);

    // Trims leading whitespace* from a string
    // modifies the input string, but also returns it as a reference
    //
    // Example usage: 
    // std::string a = "    test";
    // std::cout << helper::str_func::TrimStart(a);
    //    (prints "test" and "a" now has the value "test")
    //
    // * can also pass it a string of other characters to replace
    // instead of whitespace
    std::string& TrimStart(std::string&, 
                          const char* whitespace = " \t\f\n\r\v");
    
    // Trims trailing whitespace* from a string
    // modifies the input string, but also returns it as a reference
    //
    // Example usage: 
    // std::string a = "test     ";
    // std::cout << helper::str_func::TrimEnd(a);
    //    (prints "test" and "a" now has the value "test")
    //
    // * can also pass it a string of other characters to replace
    // instead of whitespace
    std::string& TrimEnd(std::string&, 
                        const char* whitespace = " \t\f\n\r\v");

    // Trims whitespace* from start and end of a string.
    // Modifies the input string and returns it as a reference.
    //
    // Example usage:
    // std::string a = "    test text    ";
    // std::cout << helper::str_func::Trim(a);
    //     (prints "test text" and a now has the value "test")
    //
    // * can also pass it a string of other characters to replace
    // instead of whitespace
    std::string& Trim(std::string&, 
                      const char* whitespace = " \t\f\n\r\v");

    
    // Removes all whitespace* from a string
    // modifies the input string, but also returns it as a reference
    //
    // Example usage: 
    // std::string a = "  t e st     ";
    // std::cout << helper::str_func::RemoveWhitespace(a);
    //    (prints "test" and "a" now has the value "test")
    std::string& RemoveWhitespace(std::string&);

    // Takes an iterator to a string (position in a string)
    // and returns the first group of characters (as a string) between the 
    // whitespace* starting at the iterator and the whitespace after
    // the group of characters.
    // Also advances the iterator forward to the next whitespace/separator
    // after the word.
    //
    // Example usage:
    // std::string a = "--IWantThisWordAsB---ButThisAsC--";
    // std::iterator itr = a.begin();
    // std::string b = helper::str_func::GetWord(itr, '-');
    //    (b will be equal to "IwantThisWordAsB")
    // std::string c = helper::str_func::GetWord(itr, '-');
    //    (c will be equal to "ButThisAsC")
    // std::string d = helper::str_func::GetWord(itr, '-');
    //    (d will be equal to "")
    std::string GetWord(std::string& str,
                        std::string::iterator&,
                        const char* whitespace = " \t\f\n\r\v");

    // Takes a string and returns all words separated by the
    // whitespace characters passed in as a vector of strings.
    //
    // Example usage:
    // std::string a = " this  will be a vector.";
    // std::vector<std::string> b = helper::str_func::Split(a);
    // std::cout << b[0] << ' ' << b[2] ' ' << b[3] << ' ' << b[4];
    //    (prints "this be a vector")
    std::vector<std::string> Split(std::string&,
                                  const char* whitespace = " \t\f\n\r\v");

  }

}

#endif