file(GLOB_RECURSE Includes ${CMAKE_CURRENT_LIST_DIR}/*.h)
file(GLOB_RECURSE Source ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

set(VERSION 0.1-3)

GenerateDelayFx("orbit_delay" "${VERSION}" "${Includes}" "${Source}")
