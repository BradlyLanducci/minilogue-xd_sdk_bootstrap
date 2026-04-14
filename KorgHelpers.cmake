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

    set(RelativeSource ${Source})
    list(TRANSFORM RelativeSource REPLACE ".*/" "")
    
    string(REPLACE ";" " " IncludesSpaced "${Includes}")
    string(REPLACE ";" " " RelativeSourceSpaced "${RelativeSource}")

    file(WRITE "${UnitDir}/project.mk" "PROJECT=${UnitName}\nUINCDIR=${IncludesSpaced}\nUCXXSRC=${RelativeSourceSpaced}")
    
    # As far as I can tell this makefile is the same for every single unit...
    # So I abritarly picked this one
    file(COPY ${Includes} DESTINATION ${UnitDir})
    file(COPY ${Source} DESTINATION ${UnitDir})
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
    file(COPY ${DelayDemoDir}/Makefile DESTINATION ${UnitDir})
    file(COPY ${DelayDemoDir}/ld DESTINATION ${UnitDir}/ld)
    file(COPY ${DelayDemoDir}/tpl DESTINATION ${UnitDir}/tpl)

    BuildKorgUnit(${UnitName})
endfunction()

function(GenerateModFx UnitName Version Includes Source)
    set(UnitDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/${UnitName})
    GenerateKorgUnit("${UnitDir}" "${UnitName}" "${Includes}" "${Source}")
    GenerateHeader("${UnitName}" "modfx" "${UnitDir}" "${Version}")

    set(ModDemoDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/dummy-modfx)
    file(COPY ${ModDemoDir}/Makefile DESTINATION ${UnitDir})
    file(COPY ${ModDemoDir}/ld DESTINATION ${UnitDir})
    file(COPY ${ModDemoDir}/tpl DESTINATION ${UnitDir})

    BuildKorgUnit(${UnitName})
endfunction()

function(GenerateRevFx UnitName Version Includes Source)
    set(UnitDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/${UnitName})
    GenerateKorgUnit("${UnitDir}" "${UnitName}" "${Includes}" "${Source}")
    GenerateHeader("${UnitDir}" "revfx" "${UnitDir}" "${Version}")

    set(ReverbDemoDir ${CMAKE_BINARY_DIR}/LogueSdk/platform/minilogue-xd/dummy-revfx)
    
    file(COPY ${ReverbDemoDir}/Makefile DESTINATION ${UnitDir})
    file(COPY ${ReverbDemoDir}/ld DESTINATION ${UnitDir}/ld)
    file(COPY ${ReverbDemoDir}/tpl DESTINATION ${UnitDir}/tpl)

    BuildKorgUnit(${UnitName})
endfunction()
