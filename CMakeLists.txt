cmake_minimum_required(VERSION 3.16)

project(nurbs)

message(STATUS "NURBS CMake file. 2021.")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include(FindGLUT)
include(FindOpenGL)
include_directories(${CMAKE_SOURCE_DIR}/src)
file(GLOB SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_executable(nurbs "src/main.cpp" ${SRC})
target_link_libraries(nurbs PUBLIC ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
set_target_properties(nurbs PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)
FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE TESTS_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM SRC "src/main.cpp")
add_executable(nurbs-test "test/Test.cpp" ${SRC} ${TESTS_SRC})

target_link_libraries(nurbs-test PRIVATE Catch2::Catch2 ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
set_target_properties(nurbs-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
