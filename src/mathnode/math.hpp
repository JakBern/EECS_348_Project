// Contains the math node used to evaluate the expression for the Arithmetic Expression Evaluator
//
// The node is used to check if numbers are being passed and 
// append the values to a vector 
//
// Author(s): 
// Jake Bernard [from 10/17/2023 - Present],
// Vidur Pandiripally [from 10/17/2023 - Present]
// YourName Here [from Blank - Blank]
//
// Last update:
//  - 10/19/2023 (Jake): 
//  - 11/28/2023 (Vidur)
//

#include <stdio.h>
#include <stdlib.h>
#ifndef MATH_NODE_H_ 
#define MATH_NODE_H_

#include "operatorNode.h"
#include "numNode.h"
#include <vector>

class MathNode{
    
    //public
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