// This class exists to take a user-defined expression as a C++ style string 
// and return the result of evaluating that expression as a string.
//
// The process can be broken down into 3 steps
// (which are separate functions here)
//  - "Lexing"
//    -- Taking the raw user input and separating it into a series of 
//       semantically meaningful strings. Most error checking is done here.
//  - "Parsing"/Converting to Reverse Polish Notation
//    -- Taking the lexed input and ordering it into Reverse Polish Notation
//       using stacks and queues.
//  - "Evaluating"
//    -- Taking the output of the parsing section and evaluating it using
//       the rules of Reverse Polish Notation. Some error checking is done here.
//
// The "parse" function holds all this functionality, and it is the only 
// function expected to be called by outside modules. It returns a string.
//
// Errors are propagated using an internal "error" variable, which holds a 
// string. Between steps, the error variable is checked to see if it holds a 
// value. If it's the empty string, the process continues. If it isn't,
// an error has occured and it will be returned instead of the result of the
// expression.
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

#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <string>
#include <queue>
#include <stack>
#include <vector>

// These are a way of keeping track of the state of the lexer
// I defined them here so I can compare against them in different 
// functions outside of just the main lexer area.
enum class LexToken {
                    kNone, kNumber, kConstant, 
                    kOperator, kL_Paren, kR_Paren, 
                    kError};

class Parser{
  public:
    Parser();

    // The function that performs all internal operations of the parser
    // and returns either the value the expression will evaluate to, or
    // an error.
    std::string Parse(std::string equation);

    // Takes two operators (as strings) and returns "true" if the
    // first one, string "a", has higher precedence than the second
    // one, string "b". 
    // If both strings have the same precedence, it returns true.
    // If a's precedence is lower than b's, it returns false.
    bool precedence_greater_than(std::string a, std::string b);

  private:
    // == Lexer functions and data ==

    // Fairly obvious boolean functions
    // True if the character is in the operator set
    bool is_operator(const char& c);
    // True if the character is in the set that makes up the constants
    bool is_constant_char(const char& c);
    // True if the string is a defined constant
    bool is_constant(const std::string& str);

    // Checks if the passed in type is a constant.
    // If it of constant type, checks if the string is a constant.
    //
    // Returns false if the string is not a constant (not in the constant list) 
    // and it is a constant type.
    //
    // Returns true if the type is not a constant or if the type is a constant 
    // and the string is in the constant list.
    bool constant_check(const std::string& str, LexToken type);

    // Performs lexing operations and outputs the lexed string into the "parsed"
    // vector.
    //
    // Assigns any errors encounted to the "error" member variable and returns.
    void Lexer(std::string expr);

    // Determines what LexToken a given character should correspond to
    LexToken get_lex_token(const char& c);

    // == End lexer functions and data ==

    // Takes the "parsed" vector after the lexer is finished and sorts it into
    // the "parsed queue" using the "shunting yard" algorithm.
    void ToReversePolishNotation();

    // The evaluator takes the ""
    void Evaluator();

    // The purpose of parsed vector is to contain the different values from 
    // the equation in a vector of strings.
    // It represents the earliest logic of the parser.
    // Values are added to the back and removed from the front.
    std::vector<std::string> parsed_;

    // String for storing an error in sub-functions to propagate up to the 
    // "parse" function
    std::string error_;

    // String for storing a result in sub-functions to propagate up to the 
    // "parse" function
    std::string result_;

    // Holds the expression in Reverse Polish notation by the end of the 
    // to_polish_notation function.
    // Used by the evaluator during evaluation.
    std::queue<std::string> parsed_queue_;

    // Used during the conversion to Reverse Polish Notation.
    // Holds operators as the "parsed queue"is being added to until certain 
    // conditions are met, at which point the operators held are popped off and 
    // added the "parsed queue"
    std::stack<std::string> operator_stack_;
    // Note that the output stack is made of float values.
    // During the process of evaluation, strings from the "parsed queue"
    // will be turned into floats.
    std::stack<float> output_stack_;



};

#endif