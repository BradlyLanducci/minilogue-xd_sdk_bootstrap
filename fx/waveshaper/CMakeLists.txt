file(GLOB_RECURSE includes ${CMAKE_CURRENT_LIST_DIR}*.h)
file(GLOB_RECURSE source ${CMAKE_CURRENT_LIST_DIR}*.cpp)
set(VERSION 0.1-3)

GenerateModFx("waveshaper" "${VERSION}" "${includes}" "${source}")
