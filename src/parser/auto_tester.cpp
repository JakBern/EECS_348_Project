// A small program for automatically running through test cases given in a
// an input file named tests.txt and outputting those test cases results + pass/
// fail condition to a CSV (comma separated values) text file
//
// CSV files can be easily turned into a table in Word/LibreOffice Writer.
//
// Format for test cases in the input file is as follows:
// Test Case ID
// Test Case Description
// Input
// Expected Output
//
// So, two consecutive examples in the input file would look like:
// BF-01
// Test Addition
// 3+4
// 7
// BF-02
// Test Subtraction
// 4-1
// 3
//
// This format was chosen because when I copy/paste values from a table
// in LibreOffice Writer into a plaintext document it defaults to this
// format.
//
//
// Author(s): 
// Jake Bernard [from 12/2/2023 - Present],
//
//
// Last update:
//  - 12/2/2023 (Jake): 
//    Created file
#include "parser.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main() {
  Parser parser;
  
  std::fstream output("output.csv", std::ios::out | std::ios::trunc);
  std::fstream input("tests.txt", std::ios::in);
  if (!input.is_open()) {
    std::cout << "No input file exists.";
    return 0;
  }
  int line_num = 0;
  std::string line;
  std::string expr;
  std::string output_line = "";
  std::string expected;
  std::string actual;
  while (std::getline(input, line)) {
    if (line == "") {
      continue;
    }
    switch (line_num) {
      case 0:
      case 1:
        output_line += line + ",";
        break;
      case 2:
        expr = line;
        output_line += line + ",";
        break;
      case 3:
        expected = line;
        output_line += expected + ",";
        actual = parser.parse(expr);
        output_line += actual + ",";
        output_line += (expected == actual) ? "Pass\n" : "Fail\n";
        output << output_line;
        output_line = "";
        break;
    }
    line_num = (line_num + 1) % 4;
  }
  output.close();
  input.close();
  return 0;
}