set(PROJECT_TEST_NAME VlsdkTests)

enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "main"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/gtest"
    BINARY_DIR "${CMAKE_BINARY_DIR}/gtest_build"
)
FetchContent_MakeAvailable(gtest)

file(GLOB_RECURSE TestSourceFiles 
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
    ${CMAKE_SOURCE_DIR}/vlsdk/*.cpp
)

add_executable(${PROJECT_TEST_NAME} ${TestSourceFiles})

target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_20)

target_compile_definitions(${PROJECT_TEST_NAME} PRIVATE
    ARM_MATH_CM4
    CORTEX_USE_FPU
)

target_compile_options(${PROJECT_TEST_NAME} PRIVATE
    -fpermissive
)

if(COVERAGE_ENABLED)
    target_compile_options(${PROJECT_TEST_NAME} PUBLIC
        -fprofile-instr-generate -fcoverage-mapping
    )
    target_link_options(${PROJECT_TEST_NAME} PUBLIC
        -fprofile-instr-generate -fcoverage-mapping
    )
endif()

target_compile_features(${PROJECT_TEST_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_TEST_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}/vlsdk
    ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/inc/dsp
    ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/inc/utils
    ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/inc
    ${CMAKE_BINARY_DIR}/LogueSdk/platform/ext/CMSIS/CMSIS/Include
)

target_link_libraries(${PROJECT_TEST_NAME}
    PRIVATE

    gtest_main
    gmock
)
