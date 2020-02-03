cmake_minimum_required(VERSION 3.12)

project(shared_ptr)

message(WARNING ${CMAKE_BUILD_TYPE})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") 
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
	endif()
endif()

set (CMAKE_CXX_STANDARD 11)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR  ${CMAKE_SOURCE_DIR}/include)
set(GTEST_DIR ${CMAKE_SOURCE_DIR}/external_lib/googletest)
set(SOURCES
       # ${SOURCE_DIR}/FileReader.cpp
        ${SOURCE_DIR}/FileArrayReader.cpp
        ${SOURCE_DIR}/ExtractTopN.cpp)

add_library(FileRead ${SOURCES})
target_include_directories(FileRead PUBLIC ${INCLUDE_DIR})

add_executable(TOP10 ${SOURCE_DIR}/main.cpp)
target_link_libraries(TOP10 FileRead)

add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

add_compile_definitions(RESOURCES_DIRECTORY="${CMAKE_SOURCE_DIR}/tests/resources")
