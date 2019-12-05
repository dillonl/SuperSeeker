#set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build
set(CMAKE_BUILD_TYPE Release) # uncomment this when you need a debug build

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

set(TREEBUILDER_SOURCES
  Tree.cpp
  TreeBuilder.cpp
  )

add_library(treebuilder_core STATIC
  ${TREEBUILDER_SOURCES}
)

SET(CORE_LIB treebuilder_core CACHE STRING "THE CORE LIBRARY")