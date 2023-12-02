#include "parser.hpp"
//iostream is included because im making some tests where I print out values
// from within this file
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <math.h>
#include <sstream>
#include <iomanip>

using namespace std;

Parser::Parser(){}


//to do stuff


//might change from float to double

//need to add mod (%) and exponents (** or ^)

//my goal is to have this method contain all the logic for the parser
//it should eventually recieve the single parameter, the equation as a string,
// then return a single value, either the result or a specific error message
// I have not done anything to deal with errors yet
string Parser::parse(string equation){

    //cleanup passed equation
    //at the top of the code we will check for instances of implied multiplication using parentheses
    // like 6(2+1)
    // we will change the equation so these look like 6*(2+1)
    //we will also check for "**" to change to "^"
    for (int i = 0; i < equation.length(); i++){
        //if it is not an operator before the "(", insert the "*"
        if (!(equation[i] == '*' || equation[i] == '/' || equation[i] == '+' || equation[i] == '-' || equation[i] == '%') && equation[i+1] == '('){
            equation.insert(i+1, 1, '*');
        }else if (equation[i] == '*' && equation[i+1] == '*'){
            equation.erase(i, 2);
            equation.insert(i, 1, '^');
        }

    }
    // cout << equation << "\n";


    //the following block of code serves to cut the string into pieces and add it
    // to the Parser class's private vector of strings
    // the values added will either be a number or a operator, but will all be stored as a string
    // the code needs to be able to deal with ints that have multiple digits,
    // that is why it took on the structure that it does
    // for example if equation = "10+3-4*(9-2)/10"
    // then the Parser class vector, parsed, will contain:
    //      "10" "+" "3" "-" "4" "*" "(" "9" "-" "2" ")" "/" "10"


    //I defined this string value outside the for loop, because it will be used to hold on to
    // digits while the for loop continues
    string individual_value;
    //we must also prepare for an unary minus for operations involving negative numbers
    // we declare unaryMinus, if a "-" is encountered while it is true, that - will be added to the individual_value
    // otherwise it is an operator, and should be added normally
    // if we the last bit of string was an operator, we know it is an unaryMinus, so it will be set to true
    // if the last bit of string was a number, we will make it false
    // we initialize it as true,  to deal with equations involving a leading negative ex. -6+2
    bool unaryMinus = true;
    //this for loop will iterate through the equation, allowing us to index any character
    for (int i = 0; i < equation.size(); i++){
        //if it is a number, we should add it to individual_value, in case the next value is a digit too
        // we see if it is a number by just checking if it is any digit 0-9
        // we also see if it is a constant by comparing to any characters from constants
        if (equation[i] == '0' || equation[i] == '1' || equation[i] == '2' || equation[i] == '3' || equation[i] == '4' || equation[i] == '5' || equation[i] == '6' || equation[i] == '7' || equation[i] == '8' || equation[i] == '9' || equation[i] == 'e' || equation[i] == 'p' || equation[i] == 'i'){
            individual_value += equation[i];
            unaryMinus = false;
        //ignoring white space could be the first if statement, but it doesn't make any difference
        }else if (equation[i] == ' '){
            //if the current character is just white space, it will be skipped
        //if we already know what we have is not a number, then there are two cases
        // if the individual_value is not a length of zero, that means it is holding some digits
        //  those digits should be added to parsed before the equation[i] is also added
        }else if (individual_value.size() != 0){
            //we will never encounter an unary minus when individual_size != 0
            // so we dont worry about it here
            Parser::parsed.push_back(individual_value);
            individual_value = "";
            individual_value += equation[i];
            Parser::parsed.push_back(individual_value);
            individual_value = "";
            unaryMinus = true;
        //otherwise individual value is empty, and we don't have to worry about adding anything before equation[i]
        }else{
            if (unaryMinus == false || !(equation[i] == '-')){
                individual_value += equation[i];
                Parser::parsed.push_back(individual_value);
                individual_value = "";
                unaryMinus = true;
            }else{
                individual_value += equation[i];
                unaryMinus = false;
            }
            
        } 
    }
    //if the last thing from the equation was a number, then it will still be in individual_value
    // we check if that is the case, and add it to parsed
    if (individual_value.size() != 0){
        Parser::parsed.push_back(individual_value);
        individual_value = "";
    }


    //this just prints out the values in parsed, its in here for testing
    for (int i = 0; i < parsed.size(); i++){
        // cout << parsed[i] << " ";
    }
    // cout<< "\n";





    //now we will use parsed to begin to follow the serious logic
    //in the next blocks of code we will work through the parsed values
    // and manipulate the parsedQueue and operatorStack
    //at this point we are still assuming good input
    // and it will begin to affect the functionality if we got bad input

    //////to learn about the logic I am following in this section, refer to 'parsing_example.png' on the git




    //we will iterate through the values of the parsed vector
    for (int i = 0; i < parsed.size(); i++){
        //we will look at the value we have from parsed to see if it is an operator other than ( )
        // right now we check for the following operators:  * / + - ^ %
        if (parsed[i] == "*" || parsed[i] == "/" || parsed[i] == "+" || parsed[i] == "-" || parsed[i] == "^" || parsed[i] == "%" ){
            //if the stack is empty, or the operator is lower precedence, then it should be added to the opStack
            if (operatorStack.size() == 0 || !(precedence(operatorStack.top(), parsed[i]))){    
                operatorStack.push(parsed[i]);
                
            }else{
                //otherwise, take the first value out and put it in the queue
                parsedQueue.push(operatorStack.top());
                operatorStack.pop();
                //now I will simply set i back one, meaning the for loop will reevaluate the current one
                i--;
            }
        }else if (parsed[i] == "("){
            //if we come across an open parentheses, add it to the stack
            //its low precedence will ensure it doesn't get removed
            operatorStack.push(parsed[i]);
        }else if (parsed[i] == ")"){
            if (operatorStack.top() != "("){
                parsedQueue.push(operatorStack.top());
                operatorStack.pop();
                //once again using i-- to test this value again
                i--;
            }else{
                operatorStack.pop();
            }

        }else{
            parsedQueue.push(parsed[i]);
        }
        

    }
    //now any leftover values in the operator stack should be added
    while (!operatorStack.empty()){
        parsedQueue.push(operatorStack.top());
        operatorStack.pop();
    }




    //now we will evaluate the parsedQueue down to one value
    // we will use the output stack to do this
    // as long as the parsed queue has values in it, we will continue to perform operations
    while (!parsedQueue.empty()){
        //if the value is a number, it should simply be added to the outputStack
        // we can check if a value is a number, by checking if its first character is a digit
        // or if it is a "-" and its length is more than 1, in case of unary minus ex. "-6"
        // this will handle any multiple digit numbers
        if(parsedQueue.front()[0] == 'e' ){
            //now we check if it is a constant e or a negative constant
            // it is easiest to do these with seperate statements
            float floatValue = 2.718281828;
            outputStack.push(floatValue);
            parsedQueue.pop();
        }else if (parsedQueue.front() == "-e"){
            float floatValue = -2.718281828;
            outputStack.push(floatValue);
            parsedQueue.pop();
        }else if (parsedQueue.front() == "pi"){
            float floatValue = 3.1415926;
            outputStack.push(floatValue);
            parsedQueue.pop();
        }else if (parsedQueue.front() == "-pi"){
            float floatValue = -3.1415926;
            outputStack.push(floatValue);
            parsedQueue.pop();
        }else if (parsedQueue.front()[0] == '0' || parsedQueue.front()[0] == '1' || parsedQueue.front()[0] == '2' || parsedQueue.front()[0] == '3' || parsedQueue.front()[0] == '4' || parsedQueue.front()[0] == '5' || parsedQueue.front()[0] == '6' || parsedQueue.front()[0] == '7' || parsedQueue.front()[0] == '8' || parsedQueue.front()[0] == '9' ||(parsedQueue.front()[0] == '-' && parsedQueue.front().length() != 1)){
            //change the string to a float, add it to the stack, then remove it from the queue
            float floatValue = std::stof(parsedQueue.front());
            outputStack.push(floatValue);
            parsedQueue.pop();
        }else{
            //if it is not a number, then it must be an operator
            // in which case we should start by popping off the top two values from the output stack
            // these values will then have the corresponding operation performed on them
            // and a new value will be added to the stack
            //
            //we will create values a and b to be used in the operations,
            // the shape of a stack means that for the operation a/b, we will first pop off b, then a
            float b = outputStack.top();
            outputStack.pop();
            float a = outputStack.top();
            outputStack.pop();

            //we will now perform the operation based on the front value of parsedQueue
            // this value will be added to the outputStack
            if (parsedQueue.front() == "+"){
                outputStack.push(float (a + b));
            }else if (parsedQueue.front() == "-"){
                outputStack.push(float (a - b));
            }else if (parsedQueue.front() == "*"){
                outputStack.push(float (a * b));
            }else if (parsedQueue.front() == "/"){
                outputStack.push(float (a / b));
            }else if (parsedQueue.front() == "^"){
                outputStack.push(float(pow(a, b)));
            }else if (parsedQueue.front() == "%"){
                outputStack.push(float (int(a) % int(b)));
            }

            //now pop the front of parsedQueue off
            parsedQueue.pop();
            

        }
    }




    //now we will just print the parsedQueue for the sake of testing
    // later we will repurpose this code to the clean out section,
    // just remove the part that prints the values
    // however, they should also be cleared out naturallly during the evaluation process
    while (!parsedQueue.empty()){
        // cout << parsedQueue.front() << " ";
        parsedQueue.pop();
    }

    while (!operatorStack.empty()){
        // cout << operatorStack.top() << " ";
        operatorStack.pop();
    }






    ///////Cleanup
    //because this is a class, and not a function, any values it keeps must be reset
    //down here we will clear the stacks, queues, and vectors
    //it will also mean that we can start running multiple test cases from the test.cpp
    Parser::parsed.clear();

   


    //lets print off the entire contents of output stack, which will hopefully be one value
    // lets also save that value to return it at the very bottom
    std::stringstream returnable_value;
    returnable_value << std::fixed << std::setprecision(2) << outputStack.top();
    while (!outputStack.empty()){
        // cout << outputStack.top() << "\n";
        outputStack.pop();
    }

    return returnable_value.str();

}



//the precedence function will receive two strings
//it will return true (1) if a > b, and false otherwise
int Parser::precedence(string a, string b){

    //we must define our precedence at this point
    // we will do this using an array, where the low index values have the highest priority
    // it will be a string array, to make comparing values easier

    string precedence[7] = {"^", "%", "*", "/", "+", "-", "("};

    //however, we want "*", "%", and "/" to have equal precedence
    // same with "+" "-"
    // so we will just check here if the parameters are the specific operators, and return 1 if so
    // this means the operators will move into the proper location in the stack
    if ((a == "*" || a == "/" || a == "%") && (b == "*" || b == "/" || b == "%")){
        return 1;
    }
    if ((a == "+" || a == "-") && (b == "+" || b == "-")){
        return 1;
    }

    int indexA = 0;
    for (indexA; precedence[indexA] != a; indexA++){
        //doesn't actually need any code, because the for loop itself will set the value
    }
    int indexB = 0;
    for (indexB; precedence[indexB] != b; indexB++){

    }
    //both indexes will be one higher than the actual index of their corresponding character
    // but this does not affect comparing them
    if (indexA < indexB){
        return 1;
    }
    return 0;
}