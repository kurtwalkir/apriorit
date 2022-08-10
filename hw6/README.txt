Task description:

1) Implement your own guard that manages the handle obtained as a result of calling the CreateFile Win32 API function.
2) Implement custom deleter(which closes socket) for std::unique_ptr in 3 different ways.
3) Implement own simplified implementations of the std::shared_ptr and std::weak_ptr.

You can get acquainted with the class interface here:
https://en.cppreference.com/w/cpp/memory/shared_ptr
https://en.cppreference.com/w/cpp/memory/weak_ptr


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
│   ├── shared_ptr.h
│   ├── unique_ptr.h
│   ├── weak_ptr.h
├── README.txt
└── src
    ├── main.cpp


Building and usage:
Build by making a build directory (i.e. build/), run cmake in that folder, and then use make.

Example:
> mkdir build && cd build
> cmake ..
> make
> ./hw_6
