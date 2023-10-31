#ifndef MATHNODE_VALUE_VALUE_H_
#define MATHNODE_VALUE_VALUE_H_

#include <climits>
#include <vector>
#include <string>

class BigNum {
  public:
    BigNum();
    BigNum(unsigned long);
    BigNum(std::string);
    ~BigNum();

    void set_sign(bool is_pos);
    void set_pos();
    void set_neg();
    bool is_pos();
    bool is_neg();
    void set_num(unsigned long);
    void set_num(const std::string&);

    std::size_t digit_count();
    std::string to_string();

    friend BigNum operator+(const BigNum &a, const BigNum &b);
    friend BigNum operator-(const BigNum &a, const BigNum &b);
    friend BigNum operator*(const BigNum &a, const BigNum &b);
    friend BigNum operator/(const BigNum &a, const BigNum &b);
    friend BigNum operator%(const BigNum &a, const BigNum &b);

    BigNum operator<(const BigNum &a, const BigNum &b);
    BigNum operator>(const BigNum &a, const BigNum &b);
    BigNum operator<=(const BigNum &a, const BigNum &b);
    BigNum operator>=(const BigNum &a, const BigNum &b);
    BigNum operator==(const BigNum &a, const BigNum &b);
    BigNum operator!=(const BigNum &a, const BigNum &b);
    

  private:
    // organized little endian-ly
    // num_[0] is the least significant digits, then [1], etc
    std::vector<unsigned long> num_;
    bool positive_;

    BigNum AddInternal(const BigNum&, const BigNum&, bool);

    std::size_t ulongs_used();




};



#endif