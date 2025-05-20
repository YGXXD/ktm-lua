cmake_minimum_required(VERSION 3.10)

project(ktm-lua)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_compile_options(/source-charset:utf-8)
	add_compile_options(/execution-charset:utf-8)
	add_compile_options(/arch:AVX)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
		"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
		"${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	add_compile_options(-march=native)
endif()

find_package(Lua REQUIRED)
find_package(ktm REQUIRED)
find_package(ntr REQUIRED)

file(GLOB LUAKTM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_library(${PROJECT_NAME} SHARED ${LUAKTM_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES 
	OUTPUT_NAME "ktm"
	PREFIX ""
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LUA_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ntr::ntr)
target_link_libraries(${PROJECT_NAME} PRIVATE ktm::ktm)
target_include_directories(${PROJECT_NAME} PUBLIC ${LUA_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (LUA_TEST_ENABLE)
	enable_testing()
	find_program(LUA lua)
	file(GLOB TEST_LUA_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.lua)
	set(SEARCH_LIB_PATHS "")
	string(APPEND SEARCH_LIB_PATHS "${CMAKE_BINARY_DIR}/?.dylib;")
	string(APPEND SEARCH_LIB_PATHS "${CMAKE_BINARY_DIR}/Debug/?.dylib;")
	string(APPEND SEARCH_LIB_PATHS "${CMAKE_BINARY_DIR}/Release/?.dylib;")
	string(APPEND SEARCH_LIB_PATHS "${CMAKE_BINARY_DIR}/?.so;")
	string(APPEND SEARCH_LIB_PATHS "${CMAKE_BINARY_DIR}/Debug/?.so;")
	string(APPEND SEARCH_LIB_PATHS "${CMAKE_BINARY_DIR}/Release/?.so;")
	string(APPEND SEARCH_LIB_PATHS "${CMAKE_BINARY_DIR}/?.dll;")
	string(APPEND SEARCH_LIB_PATHS "${CMAKE_BINARY_DIR}/Debug/?.dll;")
	string(APPEND SEARCH_LIB_PATHS "${CMAKE_BINARY_DIR}/Release/?.dll;")
	foreach(TEST_LUA_FILE ${TEST_LUA_FILES})
        get_filename_component(TEST_NAME ${TEST_LUA_FILE} NAME_WE)
        add_test(NAME ${TEST_NAME} 
			COMMAND 
			${LUA} 
			-e "package.cpath='${SEARCH_LIB_PATHS}..package.cpath'" 
			${TEST_LUA_FILE}
		)
	endforeach()
endif()