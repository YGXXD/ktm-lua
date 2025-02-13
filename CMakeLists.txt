cmake_minimum_required(VERSION 3.10)

project(ktm-lua)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(LUA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lua)
file(GLOB LUALIB_SOURCES ${LUA_SOURCE_DIR}/*.c)
list(REMOVE_ITEM LUALIB_SOURCES ${LUA_SOURCE_DIR}/lua.c)

add_library(lualib STATIC ${LUALIB_SOURCES})

add_executable(${PROJECT_NAME} source/main.cpp source/lktm_api.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE lualib)