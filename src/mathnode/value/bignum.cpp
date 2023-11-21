#include <climits>
#include <vector>
#include <string>
#include <cstlib>
#include <cstdint>
#include <cctype>

BigNum::BigNum() {}
BigNum::BigNum(uint_fast64_t num) {
  num_.push_back(num);
  set_pos()
}
BigNum::BigNum(const std::string& num) {
  set_num(num);
}
~BigNum() {}

std::size_t BigNum::digit_count() {
  std::size_t len = 0;
  len += ulongs_used() - 1;
  len *= kDigitLength;
  uint_fast64_t back = num_.back();
  while (back != 0) {
    len++;
    back /= 10;
  }
  return len;
}

std::string BigNum::to_string() {
  std::string out;
  if (is_neg()) {
    out += "-";
  }
  out += to_string(num_[num_.size() - 1]);
  for (int i = num_.size() - 2; i >= 0; i--) {
    std::string next_part = to_string(num_[i]);
    next_part.insert(0, (kDigitLength - next_part.length()), '0');
    out += next_part;
  }
  return out;
}

void set_sign(bool is_pos) {positive_ = is_pos;}
void BigNum::set_pos() {positive_ = true;}
void BigNum::set_neg() {positive_ = false;}
bool BigNum::is_pos() {return positive_;}
bool BigNum::is_neg() {return !positive_;}

void BigNum::set_num(uint_fast64_t num) {
  num_.clear();
  num_.push_back(num);
}

void BigNum::set_num(const std::string& num) {
  int start_index = 0;
  int size = num.length();
  if (num[0] == '-') {
    set_neg();
    start_index++;
    size--;
  }
  int divs = (size / kDigitLength) + 1;
  for (int i = 0; i < divs; i++) {
    nums_.push_back(
      std::strtoul(
        num.substr(start_index + i * kDigitLength, kDigitLength).c_str(),
        nullptr, 
        10
        )
      );
  }
}

void BigNum::Shift(int amount) {
  if (!amount) {
    return;
  }
  if (amount > 0) {
    for (int i = 0; i < amount; i++) {
      if (num_.size()) {
        num_.erase(num_.begin());
      }
    }
    if (!num_.size()) {
      num_.push_back(0);
      set_pos();
    }
    return;
  }
  else {
    for (int i = 0; i < amount; i++) {
      num_.insert(num_.begin(), 0);
    }
    return;
  }
}
BigNum BigNum::Shifted(int amount) {
  BigNum result = (*this);
  if (!amount) {
    return result;
  }
  if (amount > 0) {
    for (int i = 0; i < amount; i++) {
      if (result.num_.size()) {
        result.num_.erase(result.num_.begin());
      }
    }
    if (!result.num_.size()) {
      result.num_.push_back(0);
      result.set_pos();
    }
    return result;
  }
  else {
    for (int i = 0; i < amount; i++) {
      result.num_.insert(result.num_.begin(), 0);
    }
    return result;
  }
}

std::size_t BigNum::ulongs_used() {
  return num_.size();
};


void BigNum::Reset() {
  num_ = std::vector<uint_fast64_t>;
  set_pos();
}

bool BigNum::is_zero() {
  return ulongs_used() == 1 && !(num_[0]);
}

void BigNum::CorrectForZero() {
  if (is_zero()) {
    set_pos();
  }
}

void BigNum::PurgeZeroes() {
  for (int i = num_.size() - 1; i > 0; i--) {
    if (num_[i]) {
      return;
    }
    else {
      num_.pop_back();
    }
  }
}

friend BigNum BigNum::operator+(const BigNum &a, const BigNum &b) {
  if (a.is_pos() != b.is_pos()) {
    if (a.is_pos()) {
      return a - b;
    }
    else {
      return b - a;
    }
  }
  return AddInternal(a, b, a.is_pos());
}


friend BigNum BigNum::operator-(const BigNum &a, const BigNum &b) {
  if (a.is_pos() != b.is_pos()) {
    if (a.is_neg()) {
      return AddInternal(a, b, false);
    }
    if (b.is_neg()) {
      return AddInternal(a, b, true);
    }
  }
  BigNum result;
  uint_fast64_t difference;
  uint_fast64_t carry = 0;
  int index = 0;
  while (true) {
    if (index >= a.size() && index >= b.size()) {
      if (carry) {
        result.set_sign(false);
      }
      else {
        result.set_sign(true);
      }
      break;
    }
    if (index < a.size()) {
      difference = a.num_[index];
    } else {
      difference = 0;
    }
    if (index < b.size()) {
      difference -= b.num_[index];
    }
    difference -= carry;
    if (UINT64_MAX - b - carry < difference) {
      carry = 1;
      difference = (UINT64_MAX - difference) + 1;
    } else {
      carry = 0;
    }
    index++;
    result.push_back(difference);
  }
  result.CorrectForZero();
  return result;
}

friend BigNum BigNum::operator*(const BigNum &a, const BigNum &b) {
  BigNum product;
  product.postive_ = (a.positive_ == b.positive_);

  // early out 1
  if (a.ulongs_used() == 1 && b.ulongs_used() == 1
      && a.num_[0] <= kHalfBaseLo && .num_[0] <= kHalfBaseLo) {
    product.num_.push_back(a.num_[0] * b.num_[0]);
    return product;
  }

  // early out 2
  if (a.is_zero() or b.is_zero()) {
    product.num_.push_back(0);
    product.set_pos();
    return product;
  }
  
  for (std::size_t i = 0; i < a.ulongs_used() + b.ulongs_used() + 1; i++) {
    product.push_back(0);
  }

  GradeSchoolMult(a, b, product);
  return product;
}

friend BigNum BigNum::operator/(const BigNum &a, const BigNum &b);
friend BigNum BigNum::operator%(const BigNum &a, const BigNum &b);

//  COMPARISON OPERATORS

bool BigNum::operator<(const BigNum &a, const BigNum &b) {
  if (a.ulongs_used() < b.ulongs_used()) {
    return true;
  }
  else if (a.ulongs_used() > b.ulongs_used()) {
    return false;
  }
  else {
    for (int i = a.ulongs_used() - 1; i >= 0; i--) {
      if (a[i] < b[i]) {
        return true;
      }
      else if (a[i] > b[i]) {
        return false;
      }
      else {
        continue;
      }
    }
    return false;
  }
}

bool BigNum::operator>(const BigNum &a, const BigNum &b) { return b < a;}
bool BigNum::operator<=(const BigNum &a, const BigNum &b) { return !(a > b);}
bool BigNum::operator>=(const BigNum &a, const BigNum &b) { return !(a < b);}

bool BigNum::operator==(const BigNum &a, const BigNum &b) {
  if (a.ulongs_used() != b.ulongs_used()) {
    return false;
  }
  else {
    for (int i = a.ulongs_used() - 1; i >= 0; i--) {
      if (a[i] != b[i]) {
        return false;
      }
      else {
        continue;
      }
    }
    return true;
  }
}

bool BigNum::operator!=(const BigNum &a, const BigNum &b) {return !(a == b);}

bool BigNum::has_carry(int index = 0) {
  return num_[index] >= kBigNumBase;
}

friend BigNum BigNum::AddInternal(
        const BigNum& a, 
        const BigNum& b, 
        bool result_positive) {
  BigNum result;
  result.set_sign(result_positive);
  uint_fast64_t sum;
  uint_fast64_t carry = 0;
  int index = 0;
  while (true) {
    if (index >= a.size() && index >= b.size() && !carry) {
      break;
    }
    sum = 0;
    sum += carry;
    if (index < a.size()) {
      sum += a.num_[index];
    }
    if (index < b.size()) {
      sum += b.num_[index];
    }
    carry = (sum / kBigNumBase);
    result.push_back(sum);
    index++;
  }
  result.CorrectForZero();
  return result;
}

void BigNum::GradeSchoolMult(const BigNum &a, const BigNum &b, BigNum &product) {
  std::size_t carry_pos;
  uint_fast64_t lo_half_a;
  uint_fast64_t hi_half_a;
  uint_fast64_t lo_half_b;
  uint_fast64_t hi_half_b;
  uint_fast64_t carry;

  for (std::size_t i = 0; i < a.ulongs_used(); i++) {
    lo_half_a = a.num_[i] % kHalfBaseLo;
    hi_half_a = a.num_[i] / kHalfBaseLo;
    for (std::size_t j = 0; j < b.ulongs_used(); j++) {
      lo_half_b = b.num_[i] % kHalfBaseLo;
      hi_half_b = b.num_[i] / kHalfBaseLo;
      product.num_[i + j] = lo_half_a * lo_half_b;
      if (hi_half_a && hi_half_b) {
        carry = hi_half_a * hi_half_b;
        if (carry >= kHalfBaseHi) {
          product.num_[i + j] += (carry % kHalfBaseHi) * kHalfBaseLo;
          carry /= kHalfBaseHi;
          product.num_[i + j + 1] += carry;
        }
      }
      carry_pos = 0;
      while (product.has_carry(i + j + carry_pos)) {
        carry = product.num_[i + j + carry_pos] / kBigNumBase;
        product.num_[i + j + carry_pos + 1] += carry;
        carry_pos++;
      }
    }
  }

  // remove extraneous zeroes

  product.PurgeZeroes();

  product.CorrectForZero();
  return;
}

// GradeSchool Div
friend void BigNum::QuotientAndRemainder(const BigNum &a, const BigNum &b, 
                                    BigNum* quotient, BigNum* remainder) {
  // early out 1
  if (a < b) {
    if (quotient) {
      (*quotient) = BigNum(0);
    }
    if (remainder) {
      (*remainder) = b;
    }
    return;
  }

  // early out 2
  if (a == b) {
    if (quotient) {
      (*quotient) = BigNum(1);
      (*quotient).set_sign(!(a.positive_ ^ b.positive_));
    }
    if (remainder) {
      (*remainder) = BigNum(0);
    }
    return;
  }

  if (a.ulongs_used() == b.ulongs_used()) {
    // early out 3
    if (a.ulongs_used() == 1) {
      if (quotient) {
        (*quotient).push_back( a.num_[0] / b.num_[0] );
      }
      if (remainder) {
        (*remainder).push_back( a.num_[0] % b.num_[0] );
      }
      return;
    }
  }
  
  // terrible horrible implementation
  std::string a_digits = a.to_string();
  BigNum working_remainder = 0;
  uint_fast64_t cur_digit;
  std::string q_string;

  for (int str_index = 0; str_index < a_digits.length(); str_index++) {
    uint_fast64_t cur_digit = a_digits[str_index];
    if (!std::isdigit(cur_digit)) {
      continue;
    }
    cur_digit = cur_digit - '0';
    if (!working_remainder.is_zero()) {
      working_remainder.Mult10();
      working_remainder.AddUlong(cur_digit);
    }
    if (working_remainder < b) {
      continue;
    }
    else {
      int q_digit = 0;
      while (working_remainder > b) {
        working_remainder = working_remainder - b;
        q_digit++;
      }
      q_string.append(std::to_string(q_digit));
    }
  }

  if (quotient) {
    (*quotient) = BigNum(q_string);
  }
  if (remainder) {
    (*remainder) = working_remainder;
  }

  return;

}

friend void BigNum::Concatenate(const BigNum& other) {
  num_.insert(num_.end(), other.num_.begin(), other.num_.end());
}

BigNum BigNum::SplitRHS() {
  BigNum output;
  output.num_.insert(output.num_.begin(), 
                    num_.begin() + (num_.size() / 2) + 1, 
                    num_.end());
  return output;
}

BigNum BigNum::SplitLHS() {
  BigNum output;
  output.num_.insert(output.num_.begin(), 
                    num_.begin(), 
                    num_.begin() + (num_.size() / 2));
  return output;
}

void BigNum::Mult10() {
  for ( auto num_part : num_) {
    num_part *= 10;
  }
  for (int num_index = 0; num_index < ulongs_used(); num_index++) {
    if (has_carry(num_index)) {
      uint_fast64_t carry = num_[num_index] / kBigNumBase;
      if (num_index == ulongs_used() - 1) {
        num_.push_back(carry);
      }
      else {
        num_[num_index + 1] += carry;
      }
    }
  }
}

void BigNum::AddUlong(uint_fast64_t addend) {
  num_[0] += addend;
  for (int num_index = 0; num_index < ulongs_used(); num_index++) {
    if (has_carry(num_index)) {
      uint_fast64_t carry = num_[num_index] / kBigNumBase;
      if (num_index == ulongs_used() - 1) {
        num_.push_back(carry);
      }
      else {
        num_[num_index + 1] += carry;
      }
    }
  }
}