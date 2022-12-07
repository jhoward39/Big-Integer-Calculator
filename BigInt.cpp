#include "BigInt.h"
#include <iostream>
#include <string>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h> 
namespace ds {

BigInt::BigInt(const std::string &val) {
  for (size_t j = 0; j < val.size(); j++) {
    digits.push_back(val[j] - '0');
  }
}

std::ostream &operator<<(std::ostream &os, const BigInt &bi) {
  for (unsigned int i = 0; i < bi.digits.size(); i++)
    os << bi.digits[i];
  return os;
}

BigInt BigInt::operator+(const BigInt &other) const {
  int carry=0;
  std::stack<int> stk;
  int runningSum=0; 
  int idxa=(*this).digits.size()-1;
  int idxb=other.digits.size()-1;
  while(idxa>=0 || idxb>=0)
  {
    //Add the digits and carry starting with right-most digit.
    runningSum=(*this).digits[idxa]+other.digits[idxb]+carry; 
    if(carry !=0) carry=0; //Reset carry.
    if(runningSum>=10)
    {
      runningSum=runningSum-10;
      carry++;
    }
      stk.push(runningSum);
      runningSum=0; //reset 
      if(idxa!=-1) --idxa; //Stop number from indexing too low (index of -1 has value of 0).
      if(idxb!=-1) --idxb;
  }
  if(carry>0)
    stk.push(carry);

  BigInt sum("");
  while(!stk.empty())
  {
    sum.digits.push_back(stk.top());
    stk.pop();
  }
  return sum;
}

BigInt BigInt::operator-(const BigInt &other) const {
  //Return the *absolute difference* between this and the `other` BigInt
//Check if number left of operand is less than the number to the right of the operand.
//If so, swap digits around the operand.
  if((*this).digits.size()<other.digits.size())
    return other-(*this);
  else if((*this).digits.size()==other.digits.size())
  {
    for(unsigned int t=0;t<other.digits.size()-1;t++)
    {
      if((*this).digits[t]<other.digits[t])
        return other-(*this);
      else if((*this).digits[t]>other.digits[t])
        break;
    }
  }
  int carry = 0;
  std::stack<int> digitStack;
  int i = (*this).digits.size() - 1;
  int j = other.digits.size() - 1;
  while (i >= 0 || j >= 0) {
    int thisDig = i >= 0 ? (*this).digits.at(i) : 0;
    int otherDig = j >= 0 ? other.digits.at(j) : 0;
    int sub = thisDig - otherDig - carry;
    //If the result is less than zero, add 10 and add 1 to carry.
    if (sub < 0) {
      sub =sub+ 10;
      carry = 1;
    } else {
      carry = 0;
    }

    digitStack.push(sub);
    //Move one digit to the left.
    --i;
    --j;
  }

  // Remove leading zeros.
  while (!digitStack.empty()) {
    if (digitStack.top() != 0)
      break;
    digitStack.pop();
  }
  
  BigInt res("");
  while (!digitStack.empty()) {
    res.digits.push_back(digitStack.top());
    digitStack.pop();
  }
  return res;
}

BigInt BigInt::operator*(const BigInt &other) const {
  //Grid method multiplication. Every computation will be a two digit number whose max value is 81. 
  //Zeros are then added for proper place value. This number is then added to a running sum (RSum).
  int idxa=(*this).digits.size()-1; //indexes for grid 
  int idxb=other.digits.size()-1;
  ds::BigInt newBox("");
  ds::BigInt RSum("0");
  int xeroCountx=0; //Adds zeros for proper place value (horizontal).
  int xeroCounty=0; //Adds zeros for proper place value (vertical).
  while(idxa >= 0)
  {
    while(idxb>=0)
    {
      newBox.digits.push_back(((*this).digits[idxa]*other.digits[idxb])/10); //Push back the tens place
      newBox.digits.push_back(((*this).digits[idxa]*other.digits[idxb]) % 10); //Push back the ones place
      for(int k=0;k<(xeroCountx+xeroCounty);k++)
        newBox.digits.push_back(0); //Add zeros as needed.
      RSum=RSum+newBox;
      newBox.digits.clear();
      idxb--; //Move to next digit in "vertical" number.
      xeroCounty++;
    }
    idxa--; //Move to next digit in "horizontal" number.
    idxb=other.digits.size()-1;;
    xeroCounty=0;
    xeroCountx++;
  }
  if(RSum.digits[0]==0)
    RSum.digits.erase(RSum.digits.begin()); //Erase leading zero if the first digit is zero.
  return RSum;
}

} // namespace ds
