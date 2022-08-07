Task description:

Write your own implementation of a singly linked list (you can look at std::forward_list
as a reference for what needs to be implemented), which has the following operations
defined:
  a) Basic list operations: constructing, inserting elements at the beginning of the list,
    iterating over the list, size of the list, removing elements.
  b) Move operations (Move constructor, move assignment)
  c) The method for inserting elements at the beginning must have an overload for
    an rvalue reference, and move objects correctly.
  d) Constructing a list using a constructor that takes a std::initializer_list.
  e) The list must be templated, and work not only with primitive values, but also
    with objects (and correctly release them)
  f) Ideally, you should strive for a class interface like std::forward_list, but you do
    not need to implement absolutely all methods - a custom allocator, and
    emplace_* methods are not required (But it will not be a minus). sort, merge,
    unique do not need to be done.
  g) BONUS POINTS: Implement the split_when method, which allows you to split a
    list into two, which determines the position from which element to split, based
    on the bool value returned from the passed predicate function.


Author: Oleksandr Mordyk
Build dependencies:
> C++ compiler (g++ 9.4.0+)
> cmake

Run-time dependencies:
OS: Linux


Structure:
.
├── CMakeLists.txt
├── inc
│   ├── linkedList.h
├── README.txt
└── src
    ├── main.cpp


Building and usage:
Build by making a build directory (i.e. build/), run cmake in that folder, and then use make.

Example:
> mkdir build && cd build
> cmake ..
> make
> ./hw_7

Valgrind report:
==24338== HEAP SUMMARY:
==24338==     in use at exit: 0 bytes in 0 blocks
==24338==   total heap usage: 16 allocs, 16 frees, 74,288 bytes allocated
==24338== 
==24338== All heap blocks were freed -- no leaks are possible
==24338== 
==24338== For lists of detected and suppressed errors, rerun with: -s
==24338== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
user@laptop:~/homework/hw7/build$ 
