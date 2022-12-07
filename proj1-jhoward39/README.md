# Proj 1: Integers of Unlimited Size (10 pts)

The project includes two parts. In the first part, you will implement class `BigInt` to store integers of unlimited size. In the second part, you will use *stack* to simulate a calculator for big integers.

Your code should have sufficient comments and properly indented. The score will depend on the autograding results and your code quality.

## 0. Clone repository

To clone the remote repository to local machine, run the following commands:

```bash
cd SOME_DIRECTORY
git clone https://github.com/cisc2200/proj1-YOUR_GITHUB_ID.git
cd proj1-YOUR_GITHUB_ID
```

## 1. Implement `BigInt`

There are infinite number of integers. It is impossible to store all of them in computer.
In the first part of the project, you will implement class `BigInt` to store integers of unlimited size, as long as they fit in the physical memory.

### 1.1. Background

In C++, primitive type `int` is used to store *signed* integers.
If no length modifiers are present (e.g., `short`, `long`), it's guaranteed to have a width of at least 16 bits.
In 32-bit or 64-bit systems, it is almost exclusively guaranteed to have width of at least 32 bits.
Suppose on our machine an `int` is 32 bits wide.
This means in memory the Operating System (OS) will use a memory cell of *32 bits* (= 4 bytes) to store an integer of type `int`.
The maximum and minimum value of such an integer are `2^31-1` and `-2^31`. The `31` here is due to the dedicated sign bit.
You can read these values using functions defined in [`std::numeric_limits`](http://www.cplusplus.com/reference/limits/numeric_limits/).
Any integer that is greater than the `2^31-1` or less than `-2^31` cannot be correctly stored and represented by `int`.

### 1.2. The `BigInt` class

To store integers of any size, we can design our own variable-length representations of integers as types (or classes).
In this project, we define class `BigInt` and we will only consider ***unsigned integers***.

#### 1.2.1. Data members

In the `BigInt` class, an integer is stored in a *list*. ***Each slot in the list stores one digit of the integer***.
You can use linked list or [C++ STL containers](http://www.cplusplus.com/reference/stl/) to store the digits in class `BigInt`.
An example is given in [BigInt.h](BigInt.h#L11):

```cpp
LList<int> digits;
```

If you decide to use STL containers, for example, `std::vector`, the code should be:

```cpp
std::vector<int> digits;
```

#### 1.2.2. Methods

You should implement 3 arithmetic operations for `BigInt`: **addition** ([definition](https://en.wikipedia.org/wiki/Addition)), **subtraction for absolute difference** ([definition](https://en.wikipedia.org/wiki/Absolute_difference)), and **multiplication** ([definition](https://en.wikipedia.org/wiki/Multiplication)).
In [BigInt.cpp](BigInt.cpp), you should finish [`operator+`](BigInt.cpp#L21), [`operator-`](BigInt.cpp#L29), and [`operator*`](BigInt.cpp#L37). 
These 3 methods utilize the [operator overloading](https://en.cppreference.com/w/cpp/language/operators) feature of C++.
The return value of the 3 methods should be **a new `BigInt` object**. You should **NOT** change the content of the two operands.
There should be no leading `0`s for the results except for `0` itself.

For example, if we have two `BigInt` objects that store integer `456` and `1123`, the results of the 3 operations are as follows:

```cpp
ds::BigInt a("456");
ds::BigInt b("1123");

ds::BigInt s = a + b; // s = 1579
ds::BigInt d = a - b; // d = 667
ds::BigInt p = a * b; // p = 512088
```

**NOTE: A new method `getValueAt(pos)` in [LList.h](LList.h#L128) is added for conveniently accessing list elements by position. You can use it in your code.**

**NOTE: If you are using STL containers, you are also required to modify [the constructor](BigInt.cpp#L7) of which the input is a [`std::string`](http://www.cplusplus.com/reference/string/string/) and overload [the `<<` operator](BigInt.cpp#L14) which puts the `BigInt` object to stream `os`, starting (and ending) with the most (and least) significant digit of the integer.**

## 2. Basic calculator for `BigInt`

In the second part of the project, you will implement function `infixToPostfix` and `evaluatePostfix` in [calculator.cpp](calculator.cpp). You can refer to [this link](http://www.cplusplus.com/reference/string/string/) for the `std::string` class, for example, to find out how to access each `char` in the string object.

### 2.1. Infix to postfix

The input of function `infixToPostfix` is an expression using [infix notation](https://en.wikipedia.org/wiki/Infix_notation) that may contain `'('`, `')'`, `'+'`, `'-'`, `'*'`, digits, and white spaces (`' '`, `'\t'`, `'\n'`, etc.).
For example, `23543 + 345435  * ( 345 - 123)`.
Your implementation should transform the infix expression to its corresponding ***postfix expression*** using the [reverse Polish notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation).
The syntax of postfix expression requires that the two operands are specified first, followed by the operator: `operand1 operand2 operator`. For example, `23456234467 324568763 2223413 - *` means `23456234467 * (324568763 - 2223413)`.

Below is the pesudocode:

```
// Convert an expression from infix format to postfix format
// Param infix: the expression's infix format, e.g., 1 + 2 * 3
// Return: the "infix" expression's postfix format, e.g., 1 2 3 * +
string infixToPostfix (string infix) {
    // Empty character stack and blank postfix string.
    stack<char> opStack;
    string postFixString = "";

    // Loop through the array (one character at a time) until we reach the end of the string.
    for (int i = 0; i < infix.length(); i++) {
        if the i-th char of infix string is a digit or a space of any kind {
            // simply append it to our postfix string.
            postFixString += *cPtr;
        } else if the i-th char of infix is an operator (i.e., '+', '-', '*') {
            curOp = infix[i]; //this is current operator
            // pop operators of our stack and append them to postFixString
            // until 1) it is empty, or 2) an open parenthesis, or
            // 3) an operator with lower or same precedence is reached
            while (!opStack.empty() and opStack.top() != '(' and
                    the operator on the top of opStack is of lower or
                    same precedence than current op) {
                postFixString += opStack.top();
                // append the top operator from stack to postFixString
                opStack.pop();
            }
            Push current operator to the opStack
        } else if i-th char of infix is '(' {
            Push open parenthesis onto our stack
        } else if i-th char of infix is ')' {
            // When we reach a closing one, start popping off operators
            // until we run into an opening parenthesis.
            while (!opStack.empty()) {
                if (opStack.top() == '(') {
                    opStack.pop();
                    break;
                } else {
                    Append the top operator in opStack to postFixString
                    Pop top element from opStack
                }
            }
        }
    }
    if there is any remaining operators left on the stack
        Pop them off and append them onto the postFixString one by one.

    return postFixString;
}
```

**NOTE: You should use [`std::stack` class](http://www.cplusplus.com/reference/stack/stack/) for `opStack` in the implementation.**


### 2.2. Evaluate postfix expressions


The input of function `evaluatePostfix` is a ***postfix expression***. Your implementation of should **evaluate** it and **return** the final result as a `BigInt`.
You should create one `BigInt` object for each operand and use the methods from the first part of the project for the evaluation.
Below is the algorithm:

1. Declare a stack of `BigInt` to store the operands, and the value of the subexpression
2. Scan the expression from left to right
    1) If the `char` is a white space of any kind (`' '`, `'\t'`, `'\n'`), skip to the next `char`.
    2) If the `char` is a digit, continue reading until a non-digit `char` is observed, create a `BigInt` object for the substring, and push the `BigInt` into the stack.
    3) if the `char` is an operation symbol (`'+'`, `'-'`, `'*'`), pop two elements from the stack and apply the operation on the two elements, push the result onto the stack.
    4) When reaching the end of the expression, there should be only one value in the stack that is the result of the whole expression. Return this value.

## 3. Test your implementation

An example test is given in [main.cpp](main.cpp). You could modify its content to create your own tests.
To run the test, run the following commands:

```bash
docker build -t cisc2200 .
docker run --rm -v /FULL/PATH/TO/proj1-YOUR_GITHUB_ID:/lab cisc2200 "make clean; make" # clean and compile
docker run --rm -v /FULL/PATH/TO/proj1-YOUR_GITHUB_ID:/lab cisc2200 "./main.out" # execute the program
```

## 4. Commit and submit

```bash
git add BigInt.cpp calculator.cpp # also add `BigInt.h` if you use STL
git commit -m "part 1 & 2" # this is a message for your record, you could put anything here
git push
```
