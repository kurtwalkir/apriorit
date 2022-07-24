cmake_minimum_required(VERSION 3.5)

project(hw_1)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/report.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/inc
)
