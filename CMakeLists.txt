cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(KorgFx)

include(FetchContent)

FetchContent_Declare(
  LogueSdk
  GIT_REPOSITORY https://github.com/korginc/logue-sdk.git
  GIT_TAG        main
  SOURCE_DIR ${CMAKE_BINARY_DIR}/LogueSdk
)
FetchContent_MakeAvailable(LogueSdk)

execute_process(
    COMMAND bash ./build_image.sh
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/LogueSdk/docker/
)

add_subdirectory(fx)
