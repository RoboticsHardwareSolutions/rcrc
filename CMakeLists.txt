cmake_minimum_required(VERSION 3.9)
project(rcrc_test
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION
        "crc16/32/64")

add_library(rcrc crc/crc32.c crc/crc64.c crc/crc8.c crc/crc16.c crc/crc_poly.c
        rcrc.h)

add_executable(rcrc_test
        test/runit/src/runit.c
        crc/crc32.c crc/crc64.c crc/crc8.c crc/crc16.c crc/crc_poly.c
        test/test.c)

target_include_directories(rcrc
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/crc/
        ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(rcrc_test PRIVATE ./ test/runit/src)

if (MSVC OR MSYS OR MINGW)
    target_compile_definitions(rcrc_test PUBLIC -DRCRC_FOR_WINDOWS)
endif ()

if (APPLE)
    target_compile_definitions(rcrc_test PUBLIC -DRCRC_FOR_APPLE)
endif ()

if (UNIX AND NOT APPLE)
    target_compile_definitions(rcrc_test PUBLIC -DRCRC_FOR_UNIX)
endif ()

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
    message(STATUS "Using clang-format: ${clang_format}; files: ${format_files}")
    add_custom_target(format_rcrc COMMAND ${clang_format} -i -fallback-style=none -style=file --verbose ${format_files})
endif ()


enable_testing()
add_test(NAME rcrc_test COMMAND rcrc_test)
