#ifndef __BIGINT_H__
#define __BIGINT_H__

#include "LList.h"
#include <iostream>
#include <string>
#include <vector>
//Class which stores a vector of digits which we manipulate in order to allow us 
//to evaluate numbers outside of the 32-bit or 64-bit range.
namespace ds {
class BigInt {

public:
  std::vector<int> digits;
  
  BigInt(const std::string &val);
  BigInt(const BigInt &other) : digits(other.digits) {}

  friend std::ostream &operator<<(std::ostream &os, const BigInt &bi);

  BigInt operator+(const BigInt &other) const;
  BigInt operator-(const BigInt &other) const;
  BigInt operator*(const BigInt &other) const;
};

} // namespace ds

#endif // __BIGINT_H__