#include "parser.hpp"
//iostream is included because im making some tests where I print out values
// from within this file
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

Parser::Parser(){}

//my goal is to have this method contain all the logic for the parser
//it should eventually recieve the single parameter, the equation as a string,
// then return a single value, either the result or a specific error message
// I have not done anything to deal with errors yet
string Parser::parse(string equation){

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
    //this for loop will iterate through the equation, allowing us to index any character
    for (int i = 0; i < equation.size(); i++){
        //if it is a number, we should add it to individual_value, in case the next value is a digit too
        // we see if it is a number by just checking if it is any digit 0-9
        if (equation[i] == '0' || equation[i] == '1' || equation[i] == '2' || equation[i] == '3' || equation[i] == '4' || equation[i] == '5' || equation[i] == '6' || equation[i] == '7' || equation[i] == '8' || equation[i] == '9'){
            individual_value += equation[i];
        //ignoring white space could be the first if statement, but it doesn't make any difference
        }else if (equation[i] == ' '){
            //if the current character is just white space, it will be skipped
        //if we already know what we have is not a number, then there are two cases
        // if the individual_value is not a length of zero, that means it is holding some digits
        //  those digits should be added to parsed before the equation[i] is also added
        }else if (individual_value.size() != 0){
            Parser::parsed.push_back(individual_value);
            individual_value = "";
            individual_value += equation[i];
            Parser::parsed.push_back(individual_value);
            individual_value = "";
        //otherwise individual value is empty, and we don't have to worry about adding anything before equation[i]
        }else{
            individual_value += equation[i];
            Parser::parsed.push_back(individual_value);
            individual_value = "";
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
        cout << parsed[i] << " ";
    }
    cout<< "\n";



    //now we will use parsed to begin to follow the serious logic
    //in the next blocks of code we will work through the parsed values
    // and manipulate the parsedQueue and operatorStack
    //at this point we are still assuming good input
    // and it will begin to affect the functionality if we got bad input

    //////to learn about the logic I am following in this section, refer to 'parsing_example.png' on the git




    //we will iterate through the values of the parsed vector
    for (int i = 0; i < parsed.size(); i++){
        //we will look at the value we have from parsed to see if it is an operator other than ( )
        // right now we check for the following operators:  * / + -
        if (parsed[i] == "*" || parsed[i] == "/" || parsed[i] == "+" || parsed[i] == "-" ){
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


    //now we will just print the parsedQueue for the sake of testing
    while (!parsedQueue.empty()){
        cout << parsedQueue.front() << " ";
        parsedQueue.pop();
    }
    cout << "\n";

    while (!operatorStack.empty()){
        cout << operatorStack.top() << " ";
        operatorStack.pop();
    }






    ///////Cleanup
    //because this is a class, and not a function, any values it keeps must be reset
    //down here we will clear the stacks, queues, and vectors
    //it will also mean that we can start running multiple test cases from the test.cpp
    Parser::parsed.clear();

}



//the precedence function will receive two strings
//it will return true (1) if a > b, and false otherwise
int Parser::precedence(string a, string b){

    //we must define our precedence at this point
    // we will do this using an array, where the low index values have the highest priority
    // it will be a string array, to make comparing values easier
    // we arbitrarily decide that * and + are of higher precedence than / and -, respectively

    string precedence[5] = {"*", "/", "+", "-", "("};

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