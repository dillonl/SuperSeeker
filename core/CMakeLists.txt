set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build
#set(CMAKE_BUILD_TYPE Release) # uncomment this when you need a debug build

INCLUDE_DIRECTORIES(
	${CXXOPTS_INCLUDE}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

set(POPULATION_SOURCES
  Params.cpp
  SampleFileProcessor.cpp
  Cluster.cpp
  Sample.cpp
  TreeBuilder.cpp
  Tree.cpp
)

add_library(population_core STATIC
  ${POPULATION_SOURCES}
)

SET(CORE_NEW_LIB population_core CACHE STRING "THE CORE NEW LIBRARY")