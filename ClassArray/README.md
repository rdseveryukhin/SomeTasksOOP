Implement the Array class without relying on the type T to have an assignment operator and default constructor defined. Type T has a copy constructor.

Implement the minimum template function, which finds the minimum element stored in an instance of the Array template class, where the Array template type parameter can be arbitrary. To compare objects of an arbitrary type, a comparator will also be passed to the function input; a function or a class object with an overloaded "()" operator can act as a comparator.

The Array template class can store objects of any type for which a copy constructor is defined, including another Array, such as Array< Array<int> >. The nesting depth can be arbitrary. Write a template function (or several) flatten that takes such a "multidimensional" Array of unknown nesting depth as input and outputs all elements stored at the lowest level to the out stream, separated by a space.
