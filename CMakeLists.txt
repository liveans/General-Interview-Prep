project(interview_prep)
cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCE_FILE_LIST RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

foreach(FILE_PATH ${SOURCE_FILE_LIST})
 string(REPLACE ".cpp" ".o" NEW_NAME ${FILE_PATH})
 get_filename_component(FILE_NAME ${NEW_NAME} NAME)
 add_executable(${FILE_NAME} ${FILE_PATH})
endforeach()