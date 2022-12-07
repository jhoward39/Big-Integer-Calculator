# Proj 1: Integers of Unlimited Size 

The project includes two parts. In the first part I implement class `BigInt` to store integers of unlimited size. In the second part, you will use *stack* to simulate a calculator for big integers.


## 1. Implement `BigInt`

There are infinite number of integers. It is impossible to store all of them in computer.

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

