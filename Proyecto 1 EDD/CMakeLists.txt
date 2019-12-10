# cmake_minimum_required(VERSION <specify CMake version here>)
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp Lista.h Pila.h Cola.h)