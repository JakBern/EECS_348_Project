#ifndef MATHNODE_VALUE_VALUE_H_
#define MATHNODE_VALUE_VALUE_H_

#include "mathnode/value/bignum.hpp"

#include <string>

// will need sub-values that perform recursive operations for exponents, logs,
// addends, etc.
class Value {
  public:
    Value();
    Value(int);
    Value(float);
    Value(std::string);
    ~Value();

    std::string to_str_sym_notation( 
                  bool truncate = true,
                  std::size_t trunc_width = 6);
    std::string to_str_dec_notation(
                  std::size_t dec_places = 4, 
                  bool truncate = true,
                  std::size_t trunc_width = 12);

  private:



    





};

#endif