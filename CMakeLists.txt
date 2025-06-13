cmake_minimum_required(VERSION 3.24)
project(rcrc
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION
        "crc16/32/64")

add_library(${PROJECT_NAME} crc/crc32.c crc/crc64.c crc/crc8.c crc/crc16.c crc/crc_poly.c)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

#################### TEST SECTION #######################
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES Generic)
    add_executable(${PROJECT_NAME}_test test/test.c)
    if (NOT TARGET runit)
        include(FetchContent)
        FetchContent_Declare(
                runit
                GIT_REPOSITORY https://github.com/RoboticsHardwareSolutions/runit.git
                GIT_TAG main
        )
        FetchContent_MakeAvailable(runit)
    endif ()

    target_link_libraries(${PROJECT_NAME}_test rcrc runit)
endif ()


#################### FORMAT SECTION #######################
include(FetchContent)
FetchContent_Declare(
        rlibhelper
        GIT_REPOSITORY https://github.com/RoboticsHardwareSolutions/rlibhelper.git
        GIT_TAG main
)
FetchContent_MakeAvailable(rlibhelper)
set(FILES_FOR_FORMATTING
        crc/crc32.c crc/crc64.c crc/crc8.c crc/crc16.c crc/crc_poly.c
        test/test.c
)
include(${CMAKE_BINARY_DIR}/_deps/rlibhelper-src/format.cmake)
format_files(${PROJECT_NAME} SOURCES ${FILES_FOR_FORMATTING})
