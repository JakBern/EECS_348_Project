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

#include "flags.h"

namespace helper {

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

}

#endif