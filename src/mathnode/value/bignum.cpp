#include <climits>
#include <vector>
#include <string>
#include <cstlib>

const static unsigned long kBigNumThreshold = 10000000000000000000;

BigNum::BigNum() {}
BigNum::BigNum(unsigned long num) {
  num_.push_back(num);
}
BigNum::BigNum(const std::string& num) {
  set_num(num);
}
~BigNum() {}

std::size_t BigNum::digit_count() {
  std::size_t len = 0;
  len += ulongs_used() - 1;
  len *= 19;
  unsigned long back = num_.back();
  while (back != 0) {
    len++;
    back /= 10;
  }
  return len;
}

std::string BigNum::to_string() {
  std::string out;
  out += to_string(num_[num_.size() - 1]);
  for (int i = num_.size() - 2; i >= 0; i--) {
    std::string next_part = to_string(num_[i]);
    next_part.insert(0, (19 - next_part.length()), '0');
    out += next_part;
  }
  return out;
}

void set_sign(bool is_pos) {positive_ = is_pos;}
void BigNum::set_pos() {positive_ = true;}
void BigNum::set_neg() {positive_ = false;}
bool BigNum::is_pos() {return positive_;}
bool BigNum::is_neg() {return !positive_;}

void BigNum::set_num(unsigned int num) {
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
  int divs = (size / 19) + 1;
  for (int i = 0; i < divs; i++) {
    nums_.push_back(
      std::strtoul(
        num.substr(start_index + i * 19, 19).c_str(),
        nullptr, 
        10
        )
      );
  }
}

std::size_t BigNum::ulongs_used() {
  return num_.size();
};

std::vector<uint> num_;
bool sign_;

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
  unsigned long difference;
  unsigned long carry = 0;
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
    if (ULONG_MAX - b - carry < difference) {
      carry = 1;
      difference = (ULONG_MAX - difference) + 1;
    } else {
      carry = 0;
    }
    index++;
    result.push_back(difference);
  }
  return result;
}

// TODO(Jake): Implement the hard shit
friend BigNum BigNum::operator*(const BigNum &a, const BigNum &b) {

}
friend BigNum BigNum::operator/(const BigNum &a, const BigNum &b);
friend BigNum BigNum::operator%(const BigNum &a, const BigNum &b);

//  COMPARISON OPERATORS

bool BigNum::operator<(const BigNum &a, const BigNum &b) {
  if (a.ulongs_used() < b.ulongs_used()) {
    return true;
  }
  else if (a.ulong_used() > b.ulongs_used()) {
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

BigNum BigNum::AddInternal(
        const BigNum& a, 
        const BigNum& b, 
        bool result_positive) {
  BigNum result;
  result.set_sign(result_positive);
  unsigned long sum;
  unsigned long carry = 0;
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
    carry = (sum / kBigNumThreshold);
    result.push_back(sum);
    index++;
  }
  return result;
}