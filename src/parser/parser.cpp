// Implementation file for the Parser class.
//
// Rather lengthy, so comments are used to break it up by sections.
//
// There is a lexing section, a conversion section, an evaluation section, and 
// a general parser section.
//
// Author(s): 
// Nick Reinig [from 11/27/2023 - Present],
// Jake Bernard [from 12/3/2023 - Present]
//
//
// Last update:
//  - 12/3/2023 (Jake): 
//    Refactored some areas and updated code to match standards, 
//    made comments more concise in some areas.
//

#include "parser.hpp"
// iostream was included for print debugs previously.
// #include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cfloat>

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
bool Parser::is_constant(const std::string& str) {
  std::string constants[]= {"pi", "e"};
  for (int i = 0; i < 2; i++) {
    if (constants[i] == str) {
      return true;
    }
  }
  return false;
}

// If a given string is being added to the parsed_ vector,
// we're checking if it's of type constant and if it
// actually matches a constant.
// If it is a constant but it doesn't match any, we return false.
// Otherwise, we return true.
bool Parser::constant_check(const std::string& str, LexToken type) {
  if (type != LexToken::kConstant) {
    return true;
  }
  // We only have 2 constants, but it's better to do this for extensibility
  std::string constants[] = {"pi", "e"};
  for (int i = 0; i < 2; i++) {
    if (str == constants[i]) {
      return true;
    }
  }
  error_ = "Error: Unknown word \"" + str + "\" in expression";
  return false;
}

// Get the LexToken for the kind of character we're currently reading
LexToken Parser::get_lex_token(const char& c) {
  if (std::isspace(c)) {
    return LexToken::kNone;
  }

  if (std::isdigit(c)) {
    return LexToken::kNumber;
  }

  if (is_operator(c)) {
    return LexToken::kOperator;
  }

  if (is_constant_char(c)) {
    return LexToken::kConstant;
  }

  if (c == '(') {
    return LexToken::kL_Paren;
  }
  
  if (c == ')') {
    return LexToken::kR_Paren;
  }

  return LexToken::kError;
}



void Parser::Lexer(std::string expression) {
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
  // an unknown character  is of type "error_"

  // Most addition of symbols/numbers to the "parsed_" vector occurs at the
  // boundary between symbols, eg in "2 + 3" 2 would be added to the parsed_
  // vector when the lexer reaches "+".
  //
  // However, parentheses are added as soon as they're encountered.
  //
  // Any left over symbols are added at the end.

  bool number_encountered = false;

  // The type of the current character
  LexToken current_type = LexToken::kNone;

  // The current type of word being read
  LexToken is_reading = LexToken::kNone;

  // The type of the last word read
  LexToken last_read = LexToken::kNone;

  // Parenthetical balance will be checked throughout the lexing process to
  // catch errors early -- should always end with 0.
  //
  // Left parentheses will add to this counter, while right parentheses
  // will subtract from it.
  int paren_balance = 0;

  // To keep track of where the last parenthesis was for returning errors
  unsigned int last_paren_pos;

  std::stringstream err_strstream;

  char current_character;
  std::string current_word = "";

  // Print debugs
  // std::cout << "Lexer print debug\n";
  // std::cout << "Expression is: " << expression << "\n";

  for (unsigned int i = 0; i < expression.length(); i++){
    
    // Print debugs
    // std::cout << "Current character: " << expression[i] << std::endl;
    // std::cout << "Current word: " << current_word << std::endl;
    
    // Check parenthetical balance from last action.
    // Return with an error_ if it's off.
    // 
    // Parenthetical balance will be < 0 if an expression like:
    // ")(+2)" is encountered, where the initial right parenthesis
    // will decrement the initial balance by one.
    if (paren_balance < 0) {
      err_strstream << "Error: Mismatched parentheses at position " 
                  << last_paren_pos;
      error_ = err_strstream.str();
      return;
    }

    current_character = expression[i];

    current_type = get_lex_token(current_character);

    // If the character is unrecognized
    if (current_type == LexToken::kError) {
      err_strstream << "Error: Unusable character \'"
                    << current_character
                    << "\' at position "
                    << i;
      error_ = err_strstream.str();
      return;
    }

    // If the current type is not what was being read in before,
    // we've reached the edge of a symbol
    if (current_type != is_reading) {
            
        if (current_word.length() != 0) {
          if (!constant_check(current_word, is_reading)) {
            return;
          }
        parsed_.push_back(current_word);
        current_word = "";
      }

      if (is_reading != LexToken::kNone) {
        last_read = is_reading;
      }   

      is_reading = current_type;
    }

    // If the current character is "none" (a space)
    if (current_type == LexToken::kNone) {
      continue;
    }

    // Reading: number or constant
    if (is_reading == LexToken::kNumber || is_reading == LexToken::kConstant) {
      number_encountered = true;
      switch (last_read) {
        case LexToken::kNumber  :
        case LexToken::kConstant:
          err_strstream << "Error: Number follows number at position " << i;
          error_ = err_strstream.str();
          return;
        case LexToken::kR_Paren :
          parsed_.push_back("*");
          last_read = LexToken::kNone;
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
    if (is_reading == LexToken::kOperator) {
      // If there's already partially a word read
      if (current_word.length() > 0) {
        switch (current_character) {
          case '*':
            if (current_word[0] == '*') {
              parsed_.push_back("^");
              current_word = "";
              last_read = LexToken::kOperator;
              continue;
            }
            else {
              err_strstream << "Error: Operator follows operator at position " 
                            << i;
              error_ = err_strstream.str();
              return;
            }
          case '-':
            parsed_.push_back(current_word);
            current_word = "u-";
            last_read = LexToken::kOperator;
            continue;
        }
      }

      switch (last_read) {
        case LexToken::kNone      :
        case LexToken::kOperator  :
        case LexToken::kL_Paren   :
          if (current_character == '-') {
            current_word = "u-";
            last_read = LexToken::kOperator;
            continue;
          }
          else {
            err_strstream << "Error: Binary operator \'"
                          << current_character
                          << "\' incorrectly placed at position " 
                          << i;
            error_ = err_strstream.str();
            return;
          }
        default:
          current_word += current_character;
          break;
      }
      continue;
    }

    // Reading: left parenthesis
    if (is_reading == LexToken::kL_Paren) {
      switch (last_read) {
        case LexToken::kNumber  :
        case LexToken::kConstant:
        case LexToken::kR_Paren :
          parsed_.push_back("*");
          parsed_.push_back("(");
          current_word = "";
          last_read = LexToken::kL_Paren;
          paren_balance++;
          last_paren_pos = i;
          break;
        default:
          parsed_.push_back("(");
          current_word = "";
          last_read = LexToken::kL_Paren;
          paren_balance++;
          last_paren_pos = i;
          break;
      }
      continue;
    }

    // Reading: right parenthesis
    if (is_reading == LexToken::kR_Paren) {
      switch (last_read) {
        case LexToken::kL_Paren :
          err_strstream << "Error: Empty parentheses at position "
                        << last_paren_pos;
          error_ = err_strstream.str();
          return;
        case LexToken::kOperator:
          err_strstream << "Error: Operator precedes right parenthesis"
                        << " at position "
                        << i;
          error_ = err_strstream.str();
          return;
        default:
          parsed_.push_back(")");
          current_word = "";
          last_read = LexToken::kR_Paren;
          paren_balance--;
          last_paren_pos = i;
          break;
      }
      continue;
    }

  }

  if (paren_balance != 0) {
    error_ = "Error: Parentheses in expression are not balanced";
    return;
  }

  if (is_reading == LexToken::kOperator 
      || (is_reading == LexToken::kNone 
         && last_read == LexToken::kOperator ) ) {
    error_ = "Error: Operator at the end of expression";
    return;
  }

  else {
    if (current_word.length() != 0) {
      if (!constant_check(current_word, is_reading)) {
        return;
      }
      parsed_.push_back(current_word);
    }

    if (parsed_.size() == 0) {
      error_ = "No input given";
      return;
    }

    // No number was ever encountered, so the expression is invalid by default
    if (!number_encountered) {
      error_ = "Error: No numbers in expression.";
      return;
    }

    return;
  }

}

// ========================END LEXER SECTION=======================


// =======================REVERSE POLISH NOTATION SECTION=====================

void Parser::ToReversePolishNotation() {
      //we will iterate through the values of the parsed_ vector
    for (unsigned int i = 0; i < parsed_.size(); i++){
        //we will look at the value we have from parsed_ to see if it is an operator other than ( )
        if (parsed_[i] == "*" || parsed_[i] == "/" || parsed_[i] == "+" || parsed_[i] == "-" || parsed_[i] == "^" || parsed_[i] == "%" || parsed_[i] == "u-" ){
            //if the stack is empty, or the operator is lower precedence, then it should be added to the opStack
            if (operator_stack_.size() == 0 
                || !(precedence_greater_than(operator_stack_.top(), parsed_[i]))){    
                operator_stack_.push(parsed_[i]);
                
            }else{
                //otherwise, take the first value out and put it in the queue
                parsed_queue_.push(operator_stack_.top());
                operator_stack_.pop();
                //now I will simply set i back one, meaning the for loop will reevaluate the current one
                i--;
            }
        }else if (parsed_[i] == "("){
            //if we come across an open parentheses, add it to the stack
            //its low precedence will ensure it doesn't get removed
            operator_stack_.push(parsed_[i]);
        }else if (parsed_[i] == ")"){
            if (operator_stack_.top() != "("){
                parsed_queue_.push(operator_stack_.top());
                operator_stack_.pop();
                //once again using i-- to test this value again
                i--;
            }else{
                operator_stack_.pop();
            }

        }else{
            parsed_queue_.push(parsed_[i]);
        }
        

    }
    //now any leftover values in the operator stack should be added
    while (!operator_stack_.empty()){
        parsed_queue_.push(operator_stack_.top());
        operator_stack_.pop();
    }
}

// ====================END REVERSE POLISH NOTATION SECTION=====================


// =======================EVALUATOR SECTION=====================

void Parser::Evaluator() {
      //now we will evaluate the parsed_queue_ down to one value
    // we will use the output stack to do this
    // as long as the parsed_ queue has values in it, we will continue to perform operations
    while (!parsed_queue_.empty()){

        // Check for unruly values (-0, +/-inf, NaN) and correct them or return 
        // an error_.
        if (!output_stack_.empty()) {
          // - 0.0
          if (output_stack_.top() == -0.0f) {
            output_stack_.pop();
            output_stack_.push(0.0f);
          }
          // detecting NaN
          else if (std::isnan(output_stack_.top())) {
            error_ = "Error: Expression generated NaN during evaluation";
            return;
          }
          else if (std::isinf(output_stack_.top())) {
            error_ = "Error: Exceeds floating point size limit"
                    " (generated infinity during evaluation)";
            return;
          }
        }
        
        // Print debugs
        // std::cout << "ParsedQueue front: " 
        //           << parsed_queue_.front() 
        //           << std::endl;
        // if (!output_stack_.empty()) {
        //   std::cout << "OutputStack top: " << output_stack_.top() << std::endl;
        // }

        //if the value is a number, it should simply be added to the output_stack_
        // we can check if a value is a number, by checking if its first character is a digit
        // or if it is a "-" and its length is more than 1, in case of unary minus ex. "-6"
        // this will handle any multiple digit numbers
        if(parsed_queue_.front()[0] == 'e' ){
            //now we check if it is a constant e or a negative constant
            // it is easiest to do these with seperate statements
            float floatValue = 2.718281828;
            output_stack_.push(floatValue);
            parsed_queue_.pop();
        }else if (parsed_queue_.front() == "-e"){
            float floatValue = -2.718281828;
            output_stack_.push(floatValue);
            parsed_queue_.pop();
        }else if (parsed_queue_.front() == "pi"){
            float floatValue = 3.1415926;
            output_stack_.push(floatValue);
            parsed_queue_.pop();
        }else if (parsed_queue_.front() == "-pi"){
            float floatValue = -3.1415926;
            output_stack_.push(floatValue);
            parsed_queue_.pop();
        }else if (parsed_queue_.front()[0] == '0' || parsed_queue_.front()[0] == '1' || parsed_queue_.front()[0] == '2' || parsed_queue_.front()[0] == '3' || parsed_queue_.front()[0] == '4' || parsed_queue_.front()[0] == '5' || parsed_queue_.front()[0] == '6' || parsed_queue_.front()[0] == '7' || parsed_queue_.front()[0] == '8' || parsed_queue_.front()[0] == '9' ||(parsed_queue_.front()[0] == '-' && parsed_queue_.front().length() != 1)){
            //change the string to a float, add it to the stack, then remove it from the queue
            float floatValue;
            try {
              floatValue = std::stof(parsed_queue_.front());
            }
            catch (const std::exception& e) {
              error_ = "Error: Input was larger than allowed";
              return;
            }
            output_stack_.push(floatValue);
            parsed_queue_.pop();
        }else{
          
            // if it is not a number, then it must be an operator
            // in which case we should start by popping off the top 
            // two values from the output stack
            
            // But first, we should make sure the output stack isn't empty
            if (output_stack_.empty()) {
              error_ = "Error: Malformed expression";
              return;
            }

            // Negation/unary minus
            if (parsed_queue_.front() == "u-"){
                float a = output_stack_.top();
                output_stack_.pop();
                output_stack_.push(a * -1.0f);
                parsed_queue_.pop();
                continue;
            }


            // these values will then have the corresponding operation 
            // performed on them
            // and a new value will be added to the stack
            //
            // we will create values a and b to be used in the operations,
            // the shape of a stack means that for the operation a/b, we will 
            // first pop off b, then a
            float b = output_stack_.top();
            output_stack_.pop();
            float a = output_stack_.top();
            output_stack_.pop();

            // we will now perform the operation based on the front 
            // value of parsed_ queue.
            // this value will be added to the output stack
            if (parsed_queue_.front() == "+"){
                output_stack_.push(float (a + b));
            }else if (parsed_queue_.front() == "-"){
                output_stack_.push(float (a - b));
            }else if (parsed_queue_.front() == "*"){
                output_stack_.push(float (a * b));
            }else if (parsed_queue_.front() == "/"){
                if (b == 0.f) {
                  error_ = "Error: Division by zero encountered in expression";
                  return;
                }
                output_stack_.push(float (a / b));
            }else if (parsed_queue_.front() == "^"){
                output_stack_.push(float(pow(a, b)));
            }else if (parsed_queue_.front() == "%"){
               if ((int)b == 0) {
                  error_ = "Error: Modulo by zero encountered in expression";
                  return;
                }
                output_stack_.push(float (int(a) % int(b)));
            }

            // now pop the front of parsed_queue_ off
            parsed_queue_.pop();
            

        }
    }




    // now we will just print the parsed_queue_ for the sake of testing
    // later we will repurpose this code to the clean out section,
    // just remove the part that prints the values
    // however, they should also be cleared out naturallly during the 
    // evaluation process
    while (!parsed_queue_.empty()){
        // cout << parsed_queue_.front() << " ";
        parsed_queue_.pop();
    }

    while (!operator_stack_.empty()){
        // cout << operator_stack_.top() << " ";
        operator_stack_.pop();
    }






    ///////Cleanup
    //because this is a class, and not a function, any values it keeps must be reset
    //down here we will clear the stacks, queues, and vectors
    //it will also mean that we can start running multiple test cases from the test.cpp
    Parser::parsed_.clear();


    // Once again checking for unruly values

    // - 0.0
    if (output_stack_.top() == -0.0f) {
      output_stack_.pop();
      output_stack_.push(0.0f);
    }
    // detecting NaN
    else if (std::isnan(output_stack_.top())) {
      error_ = "Error: Expression generated NaN during evaluation";
      return;
    }
    // infinity
    else if (std::isinf(output_stack_.top())) {
      error_ = "Error: Exceeds floating point size limit"
              " (generated infinity during evaluation)";
      return;
    }

   


    // Using a stringstream to store the intermediate value
    std::stringstream returnable_value;
    // Checking if the value is small enough to be put into scientific notation
    if (   (output_stack_.top() < 0.01f && output_stack_.top() > 0.f)
        || (output_stack_.top() > -0.01f && output_stack_.top() < 0.f) ) {
      returnable_value << std::scientific 
                       << std::setprecision(2) 
                       << output_stack_.top();
    }
    else {
      returnable_value << std::fixed 
                       << std::setprecision(2) 
                      << output_stack_.top();
    }
    while (!output_stack_.empty()){
        output_stack_.pop();
    }

    result_ = returnable_value.str();
}

// ===================END EVALUATOR SECTION=====================


// ===================GENERAL PARSING SECTION===================

std::string Parser::Parse(std::string equation){

  // Initialize result_ and error_ to empty strings
  result_ = "";
  error_ = "";
  // clear parsed_ vector
  parsed_.clear();
  // clear parsed_queue_
  while (!parsed_queue_.empty()){
      parsed_queue_.pop();
  }
  // clear operator_stack_
  while (!operator_stack_.empty()){
      operator_stack_.pop();
  }
  // clear output_stack_
  while (!output_stack_.empty()){
      output_stack_.pop();
  }

  // Input is lexed -- now available in the vector of strings called "parsed_"
  // reminder: "u-" means unary minus
  Lexer(equation);
  if (error_ != "") {
    return error_;
  }

  // Print debugs
  // std::cout << "Parsed vector looks like: \n";
  // for (unsigned int i = 0; i < parsed_.size(); i++) {
  //   std::cout << parsed_[i] << ", ";
  // }
  // std::cout << std::endl;

  // All input will be parsed_ into Reverse Polish Notation and put
  // into the parsed_queue_
  ToReversePolishNotation();
  if (error_ != "") {
    return error_;
  }

  // The parsed_queue_ is evaluated
  Evaluator();
  if (error_ != "") {
    return error_;
  }
  return result_;
}



//the precedence function will receive two strings
//it will return true (1) if a > b, and false otherwise
bool Parser::precedence_greater_than(std::string a, std::string b) {

    //we must define our precedence at this point
    // we will do this using an array, where the low index values have the highest priority
    // it will be a string array, to make comparing values easier

    std::string precedence[8] = {"u-", "^", "%", "*", "/", "+", "-", "("};

    //however, we want "*", "%", and "/" to have equal precedence
    // same with "+" "-"
    // so we will just check here if the parameters are the specific operators, and return 1 if so
    // this means the operators will move into the proper location in the stack
    if ((a == "*" || a == "/" || a == "%") && (b == "*" || b == "/" || b == "%")){
        return true;
    }
    if ((a == "+" || a == "-") && (b == "+" || b == "-")){
        return true;
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
        return true;
    }
    return false;
}

// ===============END GENERAL PARSING SECTION=====================