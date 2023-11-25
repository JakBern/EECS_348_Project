#include <stdio.h>
#include <stdlib.h>

class NumNode : public MathNode{
    public:

        NumNode(int value){
            number(value);
        }

    protected:
        int number; 
}