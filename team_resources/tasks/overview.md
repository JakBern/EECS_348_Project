<!-- omit from toc -->
# Task Overview
Note that listed methods and internal structures are not the final implementation must be done or all the methods these classes/modules may have, they simply exist as guidelines. Note however that the **Interface** methods should aim to go through as few revisions as possible to allow others in the codebase to use them freely within their own modules without worrying.
<!-- omit from toc -->
## Table of Contents
- [MathNode](#mathnode)
  - [Description](#description)
  - [Methods](#methods)
  - [Internal Structures](#internal-structures)
- [Parser](#parser)
  - [Description](#description-1)
  - [Methods](#methods-1)
  - [Internal Structures](#internal-structures-1)
- [GUI and I/O](#gui-and-io)
  - [Description](#description-2)
  - [Methods](#methods-2)
  - [Internal Structures](#internal-structures-2)

## MathNode
### Description
The data structure which the invididual elements of the arithmetic expression provided by the user will be parsed into. Math nodes can contain either a numerical value or an operator. Numerical values should be stored in multiple formats (eg, doubles and as BigNums) and can be retrieved as either and will be updated in both formats when an operation is performed upon them. Operators can be binary or unary. Operators should encode priority within the order of operations (parenthetical depth will be handled by the parser).  
Care should be taken so that the class is easily extensible via inheritance so that an arbitrary number of operators can be added.
**Used in:**
- Parser
- GUI and I/O (Constructing input sequence as a Vector of MathNodes)
**Uses:**
- None
### Methods
**Interface**
- Value getValue() // returns the value of a numeral node -- the Value struct should hold all fomats for the value
- bool isOperator() // returns true if the Node represents an operator
- bool isBinary() // returns true if the Node is a binary operator -- may later need to define ternary checks for logs
- MathNode performOperation(MathNode operand) // return a MathNode with a value determined by a unary operation
- MathNode performOperation(MathNode operandA, MathNode operandB) // return a MathNode with a value determined by a binary operation
**Internal**
- TBD
### Internal Structures
Operator overloading might be a good idea for some of these.
- **BigNum** - arbitrary precision integers
- **RationalNum** - class that represents a rational number using 3 BigNums - whole number + remainder (numerator / denominator)
  - How to handle irrational numbers added/multiplied to this?
- **Value** - class that holds 2 different representations of numbers (decimal and rational) - perhaps have some way to communicate     syntax errors or invalid arithmetic expressions so this can be returned by the parser.
  - eg Value might have isError() with the ability to store the position of the error

## Parser
### Description
Module responsible for parsing and evaluating user input. Will probably get input from the I/O as a string then parse it to MathNodes.
**Used in:**
- GUI and I/O
**Uses:**
- MathNode
- GUI and I/O
### Methods
**Interface**
- Value parseInput(std::string input) // takes input, gives output. Possibly returns a Value containing some kind of error type if 
something has gone wrong.
**Internal**
- TBD
### Internal Structures
- Multiple stacks (using std::Vector<MathNode>) used during the parsing process
- way to track parenthetical depth (probably just an int)

## GUI and I/O
### Description
Module for presenting an interface to the user, getting user input, and displaying the output of evaluating user input. Will most likely need to be broken down into smaller tasks, and some kind of framework will need to be chosen. There will also need to be ways to input special characters for constants like pi, etc. (possibly using something like "[pi]" which is rendered differently in the input string.)
**Used in:**
- None
**Uses:**
- MathNode
- Parser
### Methods
**Interface**
- TBD
**Internal**
- TBD
### Internal Structures
- Buttons
- Displays