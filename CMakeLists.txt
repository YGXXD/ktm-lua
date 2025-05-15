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

set(LUA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/lua)
file(GLOB LUALIB_SOURCES ${LUA_SOURCE_DIR}/*.c)
list(REMOVE_ITEM LUALIB_SOURCES ${LUA_SOURCE_DIR}/lua.c)
list(REMOVE_ITEM LUALIB_SOURCES ${LUA_SOURCE_DIR}/onelua.c)
add_library(lualib STATIC ${LUALIB_SOURCES})

set(NTR_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ntr)
file(GLOB_RECURSE NTRLIB_SOURCES ${NTR_SOURCE_DIR}/src/*.cpp)
add_library(ntrlib STATIC ${NTRLIB_SOURCES})
target_include_directories(ntrlib PUBLIC ${NTR_SOURCE_DIR}/inc)

file(GLOB LUAKTM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${LUAKTM_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE lualib)
target_link_libraries(${PROJECT_NAME} PRIVATE ntrlib)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)