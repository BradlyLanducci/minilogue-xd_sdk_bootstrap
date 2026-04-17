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

# Build functions

function(GenerateKorgUnit UnitDir UnitName Includes Source)
    file(REMOVE_RECURSE ${UnitDir})
    file(MAKE_DIRECTORY ${UnitDir})

    file(COPY ${Includes} DESTINATION ${UnitDir})
    file(COPY ${Source} DESTINATION ${UnitDir})

    file(COPY ${CMAKE_SOURCE_DIR}/fx/common/ DESTINATION ${UnitDir})

    file(GLOB_RECURSE UnitDirIncludes
        RELATIVE ${UnitDir}
        ${UnitDir}/*.h
    )
    
    file(GLOB_RECURSE UnitDirSources
        RELATIVE ${UnitDir}
        ${UnitDir}/*.cpp
    )

    string(REPLACE ";" " " IncludesSpaced "${UnitDirIncludes}")
    string(REPLACE ";" " " RelativeSourceSpaced "${UnitDirSources}")

    file(WRITE "${UnitDir}/project.mk" "PROJECT=${UnitName}\nUINCDIR=${IncludesSpaced}\nUCXXSRC=${RelativeSourceSpaced}")
    
endfunction()

function(GenerateHeader UnitDir UnitType OutputDir Version)
    set(json "{}")
    string(JSON json SET "${json}" "header" "{}")
    string(JSON json SET "${json}" "header" "platform"  "\"minilogue-xd\"")
    string(JSON json SET "${json}" "header" "module"    "\"${UnitType}\"")
    string(JSON json SET "${json}" "header" "api"       "\"1.1-0\"")
    string(JSON json SET "${json}" "header" "dev_id"    "0")
    string(JSON json SET "${json}" "header" "prg_id"    "0")
    string(JSON json SET "${json}" "header" "version"   "\"${Version}\"")
    string(JSON json SET "${json}" "header" "name"      "\"${UnitName}\"")
    string(JSON json SET "${json}" "header" "num_param" "0")
    file(WRITE "${OutputDir}/manifest.json" "${json}")
endfunction()

function(BuildKorgUnit UnitName)
    execute_process(
        COMMAND ./LogueSdk/docker/run_cmd.sh build minilogue-xd/${UnitName}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE result
        ERROR_VARIABLE err
    )
    if(NOT result EQUAL 0)
        message(FATAL_ERROR "Command failed with: ${result}\nError: ${error_output}")
    endif()
endfunction()

function(GenerateDelayFx UnitName Version Includes Source)
    set(UnitDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/${UnitName})
    GenerateKorgUnit("${UnitDir}" "${UnitName}" "${Includes}" "${Source}")
    GenerateHeader("${UnitDir}" "delfx" "${UnitDir}" "${Version}")

    set(DelayDemoDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/dummy-delfx)

    file(READ "${DelayDemoDir}/Makefile" CONTENTS)
    string(REPLACE "c++11" "c++17" CONTENTS "${CONTENTS}")
    file(WRITE "${UnitDir}/Makefile" "${CONTENTS}")

    file(COPY ${CMAKE_SOURCE_DIR}/fx/common/ld/user.ld DESTINATION ${UnitDir}/ld)
    file(RENAME ${UnitDir}/ld/user.ld ${UnitDir}/ld/userdelfx.ld)

    file(COPY ${DelayDemoDir}/ld/main_api.syms DESTINATION ${UnitDir}/ld)
    file(COPY ${DelayDemoDir}/ld/rules.ld DESTINATION ${UnitDir}/ld)
    file(COPY ${DelayDemoDir}/tpl DESTINATION ${UnitDir})

    BuildKorgUnit(${UnitName})
endfunction()

function(GenerateModFx UnitName Version Includes Source)
    set(UnitDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/${UnitName})
    GenerateKorgUnit("${UnitDir}" "${UnitName}" "${Includes}" "${Source}")
    GenerateHeader("${UnitName}" "modfx" "${UnitDir}" "${Version}")

    set(ModDemoDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/dummy-modfx)

    file(READ "${ModDemoDir}/Makefile" CONTENTS)
    string(REPLACE "c++11" "c++17" CONTENTS "${CONTENTS}")
    file(WRITE "${UnitDir}/Makefile" "${CONTENTS}")

    file(COPY ${CMAKE_SOURCE_DIR}/fx/common/ld/user.ld DESTINATION ${UnitDir}/ld)
    file(RENAME ${UnitDir}/ld/user.ld ${UnitDir}/ld/usermodfx.ld)

    file(COPY ${ModDemoDir}/ld/main_api.syms DESTINATION ${UnitDir}/ld)
    file(COPY ${ModDemoDir}/ld/rules.ld DESTINATION ${UnitDir}/ld)
    file(COPY ${ModDemoDir}/tpl DESTINATION ${UnitDir})

    BuildKorgUnit(${UnitName})
endfunction()

function(GenerateRevFx UnitName Version Includes Source)
    set(UnitDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/${UnitName})
    GenerateKorgUnit("${UnitDir}" "${UnitName}" "${Includes}" "${Source}")
    GenerateHeader("${UnitDir}" "revfx" "${UnitDir}" "${Version}")

    set(ReverbDemoDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/dummy-revfx)

    file(READ "${ReverbDemoDir}/Makefile" CONTENTS)
    string(REPLACE "c++11" "c++17" CONTENTS "${CONTENTS}")
    file(WRITE "${UnitDir}/Makefile" "${CONTENTS}")
    
    file(COPY ${CMAKE_SOURCE_DIR}/fx/common/ld/user.ld DESTINATION ${UnitDir}/ld)
    file(RENAME ${UnitDir}/ld/user.ld ${UnitDir}/ld/userrevfx.ld)

    file(COPY ${ReverbDemoDir}/ld/main_api.syms DESTINATION ${UnitDir}/ld)
    file(COPY ${ReverbDemoDir}/ld/rules.ld DESTINATION ${UnitDir}/ld)
    file(COPY ${ReverbDemoDir}/tpl DESTINATION ${UnitDir})

    BuildKorgUnit(${UnitName})
endfunction()
