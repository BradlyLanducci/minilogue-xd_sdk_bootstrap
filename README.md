# Korg-Fx-Bootstrap

The purpose of this project is to make developing Korg Minilogue-XD effects simpler. I've mainly just automated what they've already done in CMake. This could be expanded to be used for other Korg hardware.

# Using this project

You can simply copy KorgHelpers.cmake into your project then call 

    include(${CMAKE_SOURCE_DIR}/KorgHelpers.cmake)
    Generate<FxType>Fx(UnitName Includes Source)

This will:
1. Clone the logue-sdk
2. Build the docker image
3. Generate all necessary build files
4. Build the .mnlgxdunit binary and place it in ```BinaryDir/LogueSdk/platform/<UnitName>```

# Examples
I've provided some simple example effects that can be used as reference or to use alongside your Minilogue-XD.
