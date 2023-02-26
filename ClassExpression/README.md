In this assignment, you are asked to develop an Expression class hierarchy to represent arithmetic expressions. More specifically, you need to define three classes: Expression is the base class of the hierarchy, Number is for representing numbers, and BinaryOperation is a class that describes a binary operation (+, -, * or /).

The Number class must store a value of type double.

The BinaryOperation class must store a pointer to the left and right operands, which are themselves arithmetic expressions, and the type of operation (+, -, *, or /) to perform on them.

All classes should have an evaluate method that returns a value of type double - the value of the corresponding arithmetic expression, for example, the value of an instance of type Number is the number that it stores, and if you have a BinaryOperation object with the + operation, then you need to calculate the values of the left and right operand and return their sum.

When doing this task, keep in mind that when the BinaryOperation object is destroyed, it is responsible for destroying the left and right operands (it is guaranteed that they are allocated in heap memory).

The Visitor class must print (using std::cout) the textual representation of an arithmetic expression. Those. for a Number class object, it must print the number it holds, and for a BinaryOperation class object, it must print the left operand, then the operation, and then the right operand.

Note that the + and - operators have lower precedence than the * and / operators, so you may need to print additional parentheses to keep the order of the operations correct.
