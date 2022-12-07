#include "BigInt.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

ds::BigInt evaluatePostfix(const std::string &postfix);
std::string infixToPostfix(const std::string &infix);

int main(int argc, char *argv[]) {
  ds::BigInt a("456");
  ds::BigInt b("1123");
  ds::BigInt c("3452");
  ds::BigInt d("234");
  ds::BigInt e("1234543");
  ds::BigInt f("3425236");
  ds::BigInt g("234234");
  ds::BigInt h("4536456");
  ds::BigInt z=e-f;
//   //+g-h;
//   cout<<z<<endl;
  //456 - 1123 + 3452 - 234 - 1234543 - 3425236 + 234234 - 4536456
  // cout<<e<<endl<<f<<endl;
  // ds::BigInt s = e- f;
  // cout << s << endl;

// std::cout<<a-b+c-d-e-f+g-h<<std::endl;
  // ds::BigInt d = a - b;
  // cout << d << endl;
  // ds::BigInt p = a * b;
  // cout << p << endl;

  //  std::string postfix = infixToPostfix("   (  0 * 43253265987902374 -
  //   2345907 + 329078 )
  //   *      0 ");
  //  cout << postfix << endl;
  // ds::BigInt r = evaluatePostfix(postfix);
  // cout << r << endl;
}