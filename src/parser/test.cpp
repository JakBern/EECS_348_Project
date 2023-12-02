//this is only included for testing
//Nick (me) created this to test the parser class as he made it
//it might be left in the code that i push back in case drew is starting to work on this stuff too



///////instructions
// to run a test, edit this file or make changes to the code in parser.cpp or parser.hpp
// in my case I am using the command line to compile a new test.exe literally every time i run
// its probably not a good approach, but to do it
//
// 1. navigate to the parser folder in the terminal : project\EECS_348_Project\src\parser

// 2. make sure parser.cpp/hpp and test.cpp are all saved

// 3. run the following command in the terminal
//    ...project\EECS_348_Project\src\parser> g++ .\test.cpp .\parser.cpp -o test
// this will compile the test.exe

// 4. run the following command in the terminal
//    ...project\EECS_348_Project\src\parser> .\test.exe
// this is just call the .exe file and the output would be shown

#include "parser.hpp"
#include <string>
#include <iostream>

using namespace std;

int main(){
    //we just define the Parser class as parser
    Parser parser;

    // right now the program should accomplish everything in the parsing example png
    // the output for the following line would  be "10 3 + 4 9 2 - * -"
    parser.parse("e+-e");
    cout << "done \n";



    parser.parse("6+-2");

    parser.parse("6-(1+1)");

    parser.parse("e+1");



    
    cout << parser.parse("pi + 1") << "\n";

  
    cout << parser.parse("6/2(1+2)") << "\n";

    cout << parser.parse("6^2") << "\n";

    cout << parser.parse("6**2") << "\n";

    cout << parser.parse("7%2") << "\n";






    cout << "all complete";



    return 0;
}