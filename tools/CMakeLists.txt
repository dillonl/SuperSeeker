set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}
)

set(SUPERSEEKER_SOURCES
	superseeker.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # clang Doesnt use pthread
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

set(CMAKE_BUILD_TYPE Debug) # uncomment this when you need a debug build
#set(CMAKE_BUILD_TYPE Release) # uncomment this when you need a debug build

add_executable(superseeker
  ${SUPERSEEKER_SOURCES}
)

target_link_libraries(superseeker
  ${CORE_NEW_LIB}
)