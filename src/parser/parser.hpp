
#include <string>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class Parser{
    public:
        Parser();
        string parse(string equation);
        int precedence(string a, string b);

    private:
        //the purpose of parsed is to contain the different values from the equation in a vector of strings
        //it represents the earliest logic of the parser
        //functionally it could become a queue, becuase values will all be added to the back and removed from the front
        //for the sake of testing, it will remain a vector
        vector<string> parsed;


        queue<string> parsedQueue;
        stack<string> operatorStack;



};