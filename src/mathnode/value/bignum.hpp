#ifndef MATHNODE_VALUE_VALUE_H_
#define MATHNODE_VALUE_VALUE_H_

#include <climits>
#include <vector>
#include <string>
#include <cstdint>

class BigNum {
  public:
    BigNum();
    BigNum(uint_fast64_t);
    BigNum(std::string);
    ~BigNum();

    void set_sign(bool is_pos);
    void set_pos();
    void set_neg();
    bool is_pos();
    bool is_neg();
    void set_num(uint_fast64_t);
    void set_num(const std::string&);

    void Shift(int);
    BigNum Shifted(int);

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

    friend BigNum GradeSchoolMult(const BigNum &a, const BigNum &b
                                  BigNum &product);

    friend void QuotientAndRemainder(const BigNum &a, const BigNum &b, 
                                    BigNum* quotient, BigNum* remainder);
    

  private:

    const static uint_fast64_t kBigNumBase = 1000000000000000000;
    const static int kDigitLength = 18;
    const static uint_fast64_t kHalfBase = 1000000000;
    constexpr static uint_fast64_t kBigNumBaseDiv2 = kBigNumBase / 2;
    // organized little endian-ly
    // num_[0] is the least significant digits, then [1], etc
    std::vector<uint_fast64_t> num_;
    bool positive_;

    friend BigNum AddInternal(const BigNum&, const BigNum&, bool);

    void Reset();

    bool is_zero();

    void CorrectForZero();

    void PurgeZeroes();

    bool has_carry(int index = 0);

    std::size_t ulongs_used();

    friend void Concatenate(const BigNum& other);

    friend BigNum SplitRHS();
    friend BigNum SplitLHS();

    void Mult10();

    void AddUlong(uint_fast64_t);

};



#endif