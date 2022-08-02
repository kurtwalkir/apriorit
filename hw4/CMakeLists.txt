cmake_minimum_required(VERSION 3.5)

project(hw_4)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/inc
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Threads::Threads)
