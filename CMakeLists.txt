cmake_minimum_required(VERSION 3.31)
project(modpack-updater)

set(CMAKE_CXX_STANDARD 26)

find_package(CURL REQUIRED)

add_executable(modpack-updater src/main.cpp src/download.cpp src/download.h)

target_link_libraries(modpack-updater PRIVATE CURL::libcurl)
