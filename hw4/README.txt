Task description:

Implement simple thread pool. An example of a required (but not sufficient) interface:

class SimpleThreadPool {
  public:
    explicit SimpleThreadPool(std::size_t threadCount);
    ~SimpleThreadPool();

    SimpleThreadPool(const SimpleThreadPool & ) = delete;
    SimpleThreadPool & operator = (const SimpleThreadPool & ) = delete;

    template < typename Fnc_T >
        auto Post(Fnc_T task) -> std::future < decltype(task()) > ;
    void WorkOn();
    void Destroy();
  private:
    size_t m_threadCount;
    std::vector < std::thread > threads;
    std::queue < std:: function < void() >> tasks;
    std::condition_variable condition;
    std::mutex mut;
    bool stop;
};

Program should have main() function with the example of usage SimpleThreadPool.


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
│   ├── simpleThreadPool.h
├── README.txt
└── src
    ├── main.cpp


Building and usage:
Build by making a build directory (i.e. build/), run cmake in that folder, and then use make.

Example:
> mkdir build && cd build
> cmake ..
> make
> ./hw_4