#include <stdio.h>
#include <stdlib.h>
#ifndef MATH_NODE_H_ 
#define MATH_NODE_H_

#include <vector>

#include <stdio.h>
#include <stdlib.h>

#include "operatorNode.h"
#include "numNode.h"

class MathNode{
    
    // public
    // Needs to be abstract
    // Works with operator and num node
    // Will assign to respective nodes
    public:
        
        //Im unsure what this is
        virtual bool is_num() const = 0; 

        //delete allocated memory
        virtual ~MathNode(){
            delete operatorNode;
            for (auto num : numNode)}{
                delete : num;
            }
        }
    
    //protected
    protected:
        //array of nums
        std::vector<MathNode*> nodes;
        OperatorNode* operatorNode;
    
    
    //private
    private:   
    
    
    //Needs to handle every integer in user input
    //
    
};

#endif