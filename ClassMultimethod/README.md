In this task, it is proposed to implement a template class Multimethod2 that implements a multimethod with two arguments, which allows you to dynamically add new multimethod implementations for different pairs of classes.

You will need to implement three methods of the Multimethod2 class:
addImpl - adds a multi-method implementation for two types that are specified via std::type_info.
hasImpl - takes two pointers and checks if there is a multimethod implementation for the corresponding types.
call - takes two pointers and calls the appropriate implementation for them.
The implementation of these methods must correctly handle the situation when the multimethod is commutative (that is, if the result of calling the multimethod does not depend on the order of the arguments).
