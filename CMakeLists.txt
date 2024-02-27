cmake_minimum_required(VERSION 3.9)
project(rcrc
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION
        "crc16/32/64")

#################### MAIN SECTION #######################

add_library(${PROJECT_NAME} crc/crc32.c crc/crc64.c crc/crc8.c crc/crc16.c crc/crc_poly.c)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})


#################### TEST SECTION #######################

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES Generic)
    add_executable(${PROJECT_NAME}_test
            test/runit/src/runit.c
            crc/crc32.c crc/crc64.c crc/crc8.c crc/crc16.c crc/crc_poly.c
            test/test.c)

    if (NOT TARGET runit)
        if (NOT EXISTS ${CMAKE_BINARY_DIR}/runit/src/runit.c)
            include(cmake/GitUtils.cmake)
            git_clone(
                    PROJECT_NAME runit
                    GIT_URL https://gitlab.com/RoboticsHardwareSolutions/rlibs/runit.git
                    GIT_BRANCH main)
        endif ()
        target_include_directories(${PROJECT_NAME}_test PRIVATE ${CMAKE_BINARY_DIR}/runit/src)
    else ()
        target_link_libraries(${PROJECT_NAME}_test PRIVATE runit)
    endif ()

    target_include_directories(${PROJECT_NAME}_test
            PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

    enable_testing()
    add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
endif ()


#################### FORMAT SECTION #######################

set(FILES_FOR_FORMATTING
        crc/crc32.c crc/crc64.c crc/crc8.c crc/crc16.c crc/crc_poly.c
        crc/crc32.h crc/crc64.h crc/crc8.h crc/crc16.h crc/crc_poly.h
        test/test.c
)

# clang-format
find_program(clang_format NAMES clang-format)
if (NOT clang_format)
    message(STATUS "Could not locate clang-format")
else ()
    file(GLOB format_files ${FILES_FOR_FORMATTING})
    add_custom_target(${PROJECT_NAME}_format COMMAND ${clang_format} -i -fallback-style=none -style=file --verbose ${format_files})
endif ()
