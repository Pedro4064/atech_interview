##########################################################
# CMake Configuration for Atech Interview Problem        #
##########################################################
cmake_minimum_required(VERSION 3.15)
project(AtechInterviewProblem VERSION 1.0
                              DESCRIPTION "Interview Problem for Jr. Position at Atech"
                              LANGUAGES C)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# File Listings for compilation ##########################
set(SRC_FILES 
    ${CMAKE_SOURCE_DIR}/src/max_area.c
)
set(
    INCLUDE_DIR
    ${CMAKE_SOURCE_DIR}/include
)
set(
    TEST_FILES
    ${CMAKE_SOURCE_DIR}/tests/test_max_area.c
)
set(
    TEST_FRAMEWORK_FILES
    ${CMAKE_SOURCE_DIR}/lib/unity/src/unity.c
)

# Main Execution target ###################################
add_executable(problem ${SRC_FILES} ${CMAKE_SOURCE_DIR}/src/main.c)
target_include_directories(problem PUBLIC ${INCLUDE_DIR})

# Testing target ##########################################
add_executable(test_run ${SRC_FILES} ${TEST_FRAMEWORK_FILES} ${TEST_FILES})
target_include_directories(test_run 
                            PUBLIC 
                            ${INCLUDE_DIR}
                            ${CMAKE_SOURCE_DIR}/lib/unity/src
)