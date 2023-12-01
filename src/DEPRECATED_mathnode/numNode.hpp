#include <stdio.h>
#include <stdlib.h>

class NumNode : public MathNode{
    public:

        NumNode(int value){
            number(value);
        }

        bool isNumber(const std::string& str) {
            // Regular expression to match a number
            std::regex numberRegex("^[-+]?[0-9]*\\.?[0-9]+$");

            // Match the input string against the regular expression
            return std::regex_match(str, numberRegex);
        }

        void is_num() override {
            //This will be changed later, just I think I need to put the number in a vector?
            if(isNumber(number)){
                friend &MathNode.push_back(number);
            }
        }

    protected:
        int number; 
}