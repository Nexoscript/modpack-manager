cmake_minimum_required(VERSION 3.31)
project(modpack-updater)

set(CMAKE_CXX_STANDARD 26)

add_executable(modpack-updater main.cpp download.cpp download.h)
