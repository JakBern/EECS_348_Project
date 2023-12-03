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
#include <cctype>
#include <cfloat>

using namespace std;

Parser::Parser(){}

// ========================LEXER SECTION=======================

// Check if a character is/could be an operator or part of one
bool Parser::is_operator(const char& c) {
  char operators[] = {'^', '%', '*', '/', '+', '-'};
  for (int i = 0; i < 6; i++) {
    if (operators[i] == c) {
      return true;
    }
  }
  return false;
}

// Check if a character is in the set used for constants
bool Parser::is_constant_char(const char& c) {
  char constant_chars[]= {'p', 'i', 'e'};
  for (int i = 0; i < 3; i++) {
    if (constant_chars[i] == c) {
      return true;
    }
  }
  return false;
}

// Check if a string matches a constant
bool Parser::is_constant(const string& str) {
  string constants[]= {"pi", "e"};
  for (int i = 0; i < 2; i++) {
    if (constants[i] == str) {
      return true;
    }
  }
  return false;
}

// If a given string is being added to the parsed vector,
// we're checking if it's of type constant and if it
// actually matches a constant.
// If it is a constant but it doesn't match any, we return false.
// Otherwise, we return true.
bool Parser::constant_check(const string& str, LexToken type) {
  if (type != LexToken::constant) {
    return true;
  }
  // We only have 2 constants, but it's better to do this for extensibility
  string constants[] = {"pi", "e"};
  for (int i = 0; i < 2; i++) {
    if (str == constants[i]) {
      return true;
    }
  }
  error = "Error: Unknown word \"" + str + "\" in expression";
  return false;
}

// Get the LexToken for the kind of character we're currently reading
LexToken Parser::get_lex_token(const char& c) {
  if (std::isspace(c)) {
    return LexToken::none;
  }

  if (std::isdigit(c)) {
    return LexToken::number;
  }

  if (is_operator(c)) {
    return LexToken::m_operator;
  }

  if (is_constant_char(c)) {
    return LexToken::constant;
  }

  if (c == '(') {
    return LexToken::l_paren;
  }
  
  if (c == ')') {
    return LexToken::r_paren;
  }

  return LexToken::error;
}



void Parser::lexer(string expression) {
  // Note: within this I'm using special vocabulary. It might not be the correct
  // vocabulary, so I'll define it here.
  // The terms worth explaining are "word" and "LexToken"
  //
  // Given this expression as an example:
  // 21 + 3 - (pi * 9)
  //
  // "21", "+", "3", "-", "pi", "*", "9", "(", and ")"
  // are all considered to be separate "words".
  //
  // Each word has a lexer token (LexToken) type I've assigned:
  // "21"                 is of type "number"
  // "+"                is of type "operator"
  // "pi"               is of type "constant"
  // "("                 is of type "l_paren"
  // ")"                 is of type "r_paren"
  // any space              is of type "none"
  // an unknown character  is of type "error"

  // Most addition of symbols/numbers to the "parsed" vector occurs at the
  // boundary between symbols, eg in "2 + 3" 2 would be added to the parsed
  // vector when the lexer reaches "+".
  //
  // However, parentheses are added as soon as they're encountered.
  //
  // Any left over symbols are added at the end.

  // The type of the current character
  LexToken current_type = LexToken::none;

  // The current type of word being read
  LexToken is_reading = LexToken::none;

  // The type of the last word read
  LexToken last_read = LexToken::none;

  // Parenthetical balance will be checked throughout the lexing process to
  // catch errors early -- should always end with 0.
  //
  // Left parentheses will add to this counter, while right parentheses
  // will subtract from it.
  int paren_balance = 0;

  // To keep track of where the last parenthesis was for returning errors
  unsigned int last_paren_pos;

  stringstream err_strstream;

  char current_character;
  string current_word = "";

  // Print debugs
  // std::cout << "Lexer print debug\n";
  // std::cout << "Expression is: " << expression << "\n";

  for (unsigned int i = 0; i < expression.length(); i++){
    
    // Print debugs
    // std::cout << "Current character: " << expression[i] << std::endl;
    // std::cout << "Current word: " << current_word << std::endl;
    
    // Check parenthetical balance from last action.
    // Return with an error if it's off.
    // 
    // Parenthetical balance will be < 0 if an expression like:
    // ")(+2)" is encountered, where the initial right parenthesis
    // will decrement the initial balance by one.
    if (paren_balance < 0) {
      err_strstream << "Error: Mismatched parentheses at position " 
                  << last_paren_pos;
      error = err_strstream.str();
      return;
    }

    current_character = expression[i];

    current_type = get_lex_token(current_character);

    // If the character is unrecognized
    if (current_type == LexToken::error) {
      err_strstream << "Error: Unusable character \'"
                    << current_character
                    << "\' at position "
                    << i;
      error = err_strstream.str();
      return;
    }

    // If the current type is not what was being read in before,
    // we've reached the edge of a symbol
    if (current_type != is_reading) {
            
        if (current_word.length() != 0) {
          if (!constant_check(current_word, is_reading)) {
            return;
          }
        parsed.push_back(current_word);
        current_word = "";
      }

      if (is_reading != LexToken::none) {
        last_read = is_reading;
      }   

      is_reading = current_type;
    }

    // If the current character is "none" (a space)
    if (current_type == LexToken::none) {
      continue;
    }

    // Reading: number or constant
    if (is_reading == LexToken::number || is_reading == LexToken::constant) {
      switch (last_read) {
        case LexToken::number  :
        case LexToken::constant:
          err_strstream << "Error: Number follows number at position " << i;
          error = err_strstream.str();
          return;
        case LexToken::r_paren :
          parsed.push_back("*");
          last_read = LexToken::none;
          // I am deliberately not using the fall-through
          // of the switch statement
          current_word += current_character;
          break;
        default:
          current_word += current_character;
          break;
      }
      continue;
    }

    // Reading: operator
    if (is_reading == LexToken::m_operator) {
      // If there's already partially a word read
      if (current_word.length() > 0) {
        switch (current_character) {
          case '*':
            if (current_word[0] == '*') {
              parsed.push_back("^");
              current_word = "";
              last_read = LexToken::m_operator;
              continue;
            }
            else {
              err_strstream << "Error: Operator follows operator at position " 
                            << i;
              error = err_strstream.str();
              return;
            }
          case '-':
            parsed.push_back(current_word);
            current_word = "u-";
            last_read = LexToken::m_operator;
            continue;
        }
      }

      switch (last_read) {
        case LexToken::none      :
        case LexToken::m_operator:
        case LexToken::l_paren   :
          if (current_character == '-') {
            current_word = "u-";
            last_read = LexToken::m_operator;
            continue;
          }
          else {
            err_strstream << "Error: Binary operator \'"
                          << current_character
                          << "\' incorrectly placed at position " 
                          << i;
            error = err_strstream.str();
            return;
          }
        default:
          current_word += current_character;
          break;
      }
      continue;
    }

    // Reading: left parenthesis
    if (is_reading == LexToken::l_paren) {
      switch (last_read) {
        case LexToken::number  :
        case LexToken::constant:
        case LexToken::r_paren :
          parsed.push_back("*");
          parsed.push_back("(");
          current_word = "";
          last_read = LexToken::l_paren;
          paren_balance++;
          last_paren_pos = i;
          break;
        default:
          parsed.push_back("(");
          current_word = "";
          last_read = LexToken::l_paren;
          paren_balance++;
          last_paren_pos = i;
          break;
      }
      continue;
    }

    // Reading: right parenthesis
    if (is_reading == LexToken::r_paren) {
      switch (last_read) {
        case LexToken::l_paren :
          err_strstream << "Error: Empty parentheses at position "
                        << last_paren_pos;
          error = err_strstream.str();
          return;
        case LexToken::m_operator:
          err_strstream << "Error: Operator precedes right parenthesis"
                        << " at position "
                        << i;
          error = err_strstream.str();
          return;
        default:
          parsed.push_back(")");
          current_word = "";
          last_read = LexToken::r_paren;
          paren_balance--;
          last_paren_pos = i;
          break;
      }
      continue;
    }

  }

  if (paren_balance != 0) {
    error = "Error: Parentheses in expression are not balanced";
    return;
  }

  if (is_reading == LexToken::m_operator) {
    error = "Error: Operator at the end of expression";
    return;
  }

  else {
    if (current_word.length() != 0) {
      if (!constant_check(current_word, is_reading)) {
        return;
      }
      parsed.push_back(current_word);
    }

    if (parsed.size() == 0) {
      error = "No input given";
      return;
    }

    return;
  }

}

// ========================END LEXER SECTION=======================


// =======================REVERSE POLISH NOTATION SECTION=====================

void Parser::to_reverse_polish_notation() {
      //we will iterate through the values of the parsed vector
    for (unsigned int i = 0; i < parsed.size(); i++){
        //we will look at the value we have from parsed to see if it is an operator other than ( )
        // right now we check for the following operators:  * / + - ^ %
        if (parsed[i] == "*" || parsed[i] == "/" || parsed[i] == "+" || parsed[i] == "-" || parsed[i] == "^" || parsed[i] == "%" || parsed[i] == "u-" ){
            //if the stack is empty, or the operator is lower precedence, then it should be added to the opStack
            if (operatorStack.size() == 0 
                || !(precedence_greater_than(operatorStack.top(), parsed[i]))){    
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
}

// ====================END REVERSE POLISH NOTATION SECTION=====================


// =======================EVALUATOR SECTION=====================

void Parser::evaluator() {
      //now we will evaluate the parsedQueue down to one value
    // we will use the output stack to do this
    // as long as the parsed queue has values in it, we will continue to perform operations
    while (!parsedQueue.empty()){

        // Check for unruly values (-0, +/-inf, NaN) and correct them or return 
        // an error.
        if (!outputStack.empty()) {
          // - 0.0
          if (outputStack.top() == -0.0f) {
            outputStack.pop();
            outputStack.push(0.0f);
          }
          // detecting NaN
          else if (std::isnan(outputStack.top())) {
            error = "Error: Expression generated NaN during evaluation";
            return;
          }
          else if (std::isinf(outputStack.top())) {
            error = "Error: Exceeds floating point size limit"
                    " (generated infinity during evaluation)";
            return;
          }
        }
        
        // Print debugs
        // std::cout << "ParsedQueue front: " 
        //           << parsedQueue.front() 
        //           << std::endl;
        // if (!outputStack.empty()) {
        //   std::cout << "OutputStack top: " << outputStack.top() << std::endl;
        // }

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
          
            // Negation/unary minus
            if (parsedQueue.front() == "u-"){
                float a = outputStack.top();
                outputStack.pop();
                outputStack.push(a * -1.0f);
                parsedQueue.pop();
                continue;
            }

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
                if (b == 0.f) {
                  error = "Error: Division by zero encountered in expression";
                  return;
                }
                outputStack.push(float (a / b));
            }else if (parsedQueue.front() == "^"){
                outputStack.push(float(pow(a, b)));
            }else if (parsedQueue.front() == "%"){
               if ((int)b == 0) {
                  error = "Error: Modulo by zero encountered in expression";
                  return;
                }
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


    // Once again checking for unruly values

    // - 0.0
    if (outputStack.top() == -0.0f) {
      outputStack.pop();
      outputStack.push(0.0f);
    }
    // detecting NaN
    else if (std::isnan(outputStack.top())) {
      error = "Error: Expression generated NaN during evaluation";
      return;
    }
    else if (std::isinf(outputStack.top())) {
      error = "Error: Exceeds floating point size limit"
              " (generated infinity during evaluation)";
      return;
    }

   


    //lets print off the entire contents of output stack, which will hopefully be one value
    // lets also save that value to return it at the very bottom
    std::stringstream returnable_value;
    if (outputStack.top() < 0.01f) {
      returnable_value << std::scientific 
                       << std::setprecision(2) 
                       << outputStack.top();
    }
    else {
      returnable_value << std::fixed 
                       << std::setprecision(2) 
                      << outputStack.top();
    }
    while (!outputStack.empty()){
        // cout << outputStack.top() << "\n";
        outputStack.pop();
    }

    result = returnable_value.str();
}

// ===================END EVALUATOR SECTION=====================




string Parser::parse(string equation){

  // Initialize result and error to empty strings
  result = "";
  error = "";
  // clear parsed vector
  parsed.clear();
  // clear parsedQueue
  while (!parsedQueue.empty()){
      parsedQueue.pop();
  }
  // clear operatorStack
  while (!operatorStack.empty()){
      operatorStack.pop();
  }
  // clear outputStack
  while (!outputStack.empty()){
      outputStack.pop();
  }

  // Input is lexed -- now available in the vector of strings called "parsed"
  // reminder: "u-" means unary minus
  lexer(equation);
  if (error != "") {
    return error;
  }

  // Print debugs
  // std::cout << "Parsed vector looks like: \n";
  // for (unsigned int i = 0; i < parsed.size(); i++) {
  //   std::cout << parsed[i] << ", ";
  // }
  // std::cout << std::endl;

  // All input will be parsed into Reverse Polish Notation and put
  // into the parsedQueue
  to_reverse_polish_notation();
  if (error != "") {
    return error;
  }

  // The parsedQueue is evaluated
  evaluator();
  if (error != "") {
    return error;
  }
  return result;
}



//the precedence function will receive two strings
//it will return true (1) if a > b, and false otherwise
int Parser::precedence_greater_than(string a, string b) {

    //we must define our precedence at this point
    // we will do this using an array, where the low index values have the highest priority
    // it will be a string array, to make comparing values easier

    string precedence[8] = {"u-", "^", "%", "*", "/", "+", "-", "("};

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
    for (; precedence[indexA] != a; indexA++){
        //doesn't actually need any code, because the for loop itself will set the value
    }
    int indexB = 0;
    for (; precedence[indexB] != b; indexB++){

    }
    //both indexes will be one higher than the actual index of their corresponding character
    // but this does not affect comparing them
    if (indexA < indexB){
        return 1;
    }
    return 0;
}