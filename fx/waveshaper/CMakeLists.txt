file(GLOB_RECURSE CommonIncludes ${CMAKE_SOURCE_DIR}/fx/common/*.h)
file(GLOB_RECURSE Includes ${CMAKE_CURRENT_LIST_DIR}/*.h)

file(GLOB_RECURSE CommonSource ${CMAKE_SOURCE_DIR}/fx/common/*.cpp)
file(GLOB_RECURSE Source ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

list(APPEND Includes ${CommonIncludes})
list(APPEND Source ${CommonSource})

set(VERSION 0.1-4)

GenerateModFx("waveshaper" "${VERSION}" "${Includes}" "${Source}")
