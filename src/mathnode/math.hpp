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

        void createNumNode(double value){
            NumNode* num = new numNode(value);
            numNode.push_back(num);
        }

        //is_num == bool
        bool is_number() const{
            for (const auto&num : numNode){
                if (num -> is_()){
                    return true;
                }
            }
            return false;
        }

    
    //protected
    protected:
    
    
    //private
    private:
    //array of nums
    
    
    
    //constructor
    //delete allocated memory
    ~MathNode(){
        delete operatorNode;
        for (auto num : numNode)}{
            delete : num;
        }
    }
    
    
    //Needs to handle every integer in user input
    //
    
};

#endif