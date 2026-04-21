cmake_minimum_required(VERSION 3.22)

project(Vlsdk CXX)

include(${CMAKE_SOURCE_DIR}/KorgHelpers.cmake)

add_subdirectory(fx)
add_subdirectory(tests)
