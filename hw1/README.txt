This project is a C++ home wrok 1 (Factory method) project with cmake.

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
│   └── report.h
├── README.txt
└── src
    ├── main.cpp
    └── report.cpp


Building and usage:
Build by making a build directory (i.e. build/), run cmake in that folder, and then use make.

Example:
> mkdir build && cd build
> cmake ..
> make
> ./hw_1 <PATH>