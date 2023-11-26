//this is only included for testing
//Nick (me) created this to test the parser class as he made it
//it might be left in the code that i push back in case drew is starting to work on this stuff too

#include "parser.hpp"
#include <string>
#include <iostream>

using namespace std;

int main(){
    //we just define the Parser class as parser
    Parser parser;

    //dont include the \n in the test cases, shouldn't break anything but would just mess with it
    cout << "10+ 3- 4*(9-2) /10 \n";
    parser.parse("10+ 3- 4*(9-2)");


    return 0;
}