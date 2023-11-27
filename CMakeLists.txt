cmake_minimum_required(VERSION 3.5)
project(CodeForces)

include_directories(${PROJECT_SOURCE_DIR})
include(SSBH/AssembleExecutable.cmake)
include(SSBH/CodeforcesCpp20.cmake)
include(FetchGTest.cmake)

add_subdirectory(r910)