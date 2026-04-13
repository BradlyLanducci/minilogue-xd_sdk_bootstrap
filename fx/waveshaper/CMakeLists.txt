
file(GLOB_RECURSE waveshaper_source ${CMAKE_CURRENT_LIST_DIR}*.cpp)

message(${CMAKE_CURRENT_LIST_DIR})

add_executable(waveshaper ${waveshaper_source})

target_include_directories(waveshaper PRIVATE
    ${CMAKE_SOURCE_DIR}/sdk
)
