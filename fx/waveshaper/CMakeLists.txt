file(GLOB_RECURSE includes ${CMAKE_CURRENT_LIST_DIR}*.h)
file(GLOB_RECURSE source ${CMAKE_CURRENT_LIST_DIR}*.cpp)

GenerateModFx("waveshaper" "${includes}" "${source}")
