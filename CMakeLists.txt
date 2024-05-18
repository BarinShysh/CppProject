cmake_minimum_required(VERSION 3.27)
project(ProjectAAP)

set(CMAKE_CXX_STANDARD 17)

add_executable(ProjectAAP main.cpp
        VigenereCipher.cpp
        SimpleSubCipher.cpp
        AffinCipher.cpp
        AffinCipher.h)
