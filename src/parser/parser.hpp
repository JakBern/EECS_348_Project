#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <string>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

// These are a way of keeping track of the state of the lexer
// I defined them here so I can compare against them in different 
// functions outside of just the main lexer area.
enum class LexToken {none, number, constant, m_operator, l_paren, r_paren, error};

class Parser{
    public:
        Parser();
        string parse(string equation);
        int precedence_greater_than(string a, string b);

    private:
      // lexer functions and data
      bool is_operator(const char& c);
      bool is_constant_char(const char& c);
      bool is_constant(const string& str);
      bool constant_check(const string& str, LexToken type);
      void lexer(string expr);
      LexToken get_lex_token(const char& c);

      // Other modules
      void to_reverse_polish_notation();
      void evaluator();
      //the purpose of parsed is to contain the different values from the equation in a vector of strings
      //it represents the earliest logic of the parser
      //functionally it could become a queue, becuase values will all be added to the back and removed from the front
      //for the sake of testing, it will remain a vector
      vector<string> parsed;

      string error;
      string result;


      queue<string> parsedQueue;
      stack<string> operatorStack;
      //note that the output stack is made of float values
      // that means we need to change the strings to ints when they are added to this stack
      stack<float> outputStack;



};

#endif