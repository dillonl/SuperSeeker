#Set up min CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#Set project name
PROJECT(tree_finder)

INCLUDE_DIRECTORIES(.)

SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build

IF("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  MESSAGE(SEND_ERROR "In-source builds are not allowed, please build this in the bin directory!")
ENDIF("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

ADD_SUBDIRECTORY(externals)
ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(tools)