# Task Overview

## Table of Contents

## MathNode
### Description
The data structure which the invididual elements of the arithmetic expression provided by the user will be parsed into. Math nodes can contain either a numerical value or an operator. Numerical values should be stored in multiple formats (eg, doubles and as BigNums) and can be retrieved as either and will be updated in both formats when an operation is performed upon them. Operators can be binary or unary. Operators should encode priority within the order of operations (parenthetical depth will be handled by the parser).  
A possible implementation might use a 16-bit flag to hold the type of math node, with numerals
### Methods
- Value getValue() // returns the value of a numeral node -- the Value struct should hold all fomats for the value
- bool isOperator() // returns true if the Node represents an operator
- bool isBinary() // returns true if the Node is a binary operator
- MathNode performOperation(MathNode operand) // return a MathNode with a value determined by a unary operation
- MathNode performOperation(MathNode operandA, MathNode operandB) // return a MathNode with a value determined by a binary operation


## Parser

## GUI