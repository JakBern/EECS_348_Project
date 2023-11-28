#include "bignum.hpp"
#include <iostream>

int main() {
  BigNum a("1000000");
  BigNum b("9");
  std::cout << "a = " << a.to_string() << std::endl;
  std::cout << "b = " << b.to_string() << std::endl;
}