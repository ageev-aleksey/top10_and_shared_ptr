cmake_minimum_required(VERSION 2.8)

project(test_shared_ptr)

if(${MSVC})
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()


add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)
set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)

add_compile_definitions(RESOURCES_DIRECTORY="${RESOURCES_DIR}")

set(SOURCE_TEST
		${PROJECT_SOURCE_DIR}/test_shared_ptr.cpp
		${PROJECT_SOURCE_DIR}/test_FileArrayReader.cpp
		${PROJECT_SOURCE_DIR}/test_ExtractTopN.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_TEST})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} gtest gtest_main FileRead)