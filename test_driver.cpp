#include "BigInt.h"
#include <iostream>
#include <iterator>
#include <string>

ds::BigInt evaluatePostfix(const std::string &postfix);
std::string infixToPostfix(const std::string &infix);

int main(int argc, char *argv[]) {
  // don't skip the whitespace while reading
  std::cin >> std::noskipws;
  // use stream iterators to copy the stream to a string
  std::istream_iterator<char> it(std::cin);
  std::istream_iterator<char> end;

  std::string infixexp(it, end);
  std::string postfixexp = infixToPostfix(infixexp);

  std::cout << evaluatePostfix(postfixexp);

  return 0;
}
