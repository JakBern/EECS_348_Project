# Style Notes & Exceptions

## Namespaces
The Google C++ Style Guide mandates that all modules must be put into namespaces following the project name and path structure.  
For the purposes of this project, this guideline will not followed. Only code that is outside of a class (except for in the main) requires a namespace.

## Function, Variable, Class, and Namespace Names
**Functions**
Most functions should use upper camel case (eg, FunctionName()).  
Getters, setters, and simple boolean functions should use snake case (eg, set_color(), is_green()).  
  
**Variables**  
Variables should be given names using snake case (eg, var_name).  
Variables that are data members of classes should have an added underscore at the end (eg, var_name_).  
  
**Classes**
Classes should use upper camel case (eg, ClassName).

**Namespaces**
Namespaces should use snake case, although they should preferably only be one word long (eg, namespace_name, preferably just "namespace").