This project is a C++ home wrok 1 (Factory method) project with cmake.
Author: Oleksandr Mordyk

Task:
Factory method.
Implement an application that:
- Gets a full folder path as its input value
- Collects a list of all files in this folder (you may implement it as recursive or not, it is up
to you), their properties (like size/creation time/modification time/access
type/archive/read-only etc.). Select at least 3 properties.
- Prints a “report” about the folder content in the following formats (select at least 2): txt,
csv, xml, json.
Use factory method.


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
