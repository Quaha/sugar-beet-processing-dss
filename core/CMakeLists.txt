cmake_minimum_required(VERSION 3.15)

# Project name
set(PROJECT_NAME core)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CXX_BRIDGE_DEFINE CORE_LIBRARY_EXPORT)

# Standart version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS include/*.hpp)

option(BUILD_FOR_DLL "Build only for creating DLL" OFF)

if(BUILD_FOR_DLL)
    add_library(${PROJECT_NAME}_library SHARED
        ${SRC_FILES} 
        ${HEADER_FILES}
    )

    target_compile_definitions(server_library PRIVATE ${CXX_BRIDGE_DEFINE})

    # Header files
    target_include_directories(${PROJECT_NAME}_library
        PUBLIC
            ${CMAKE_SOURCE_DIR}/include
    )
else()
    add_library(${PROJECT_NAME}_library
        ${SRC_FILES} 
        ${HEADER_FILES}
    )

    target_compile_definitions(${PROJECT_NAME}_library PRIVATE ${CXX_BRIDGE_DEFINE})

    # Header files
    target_include_directories(${PROJECT_NAME}_library
        PUBLIC
            ${CMAKE_SOURCE_DIR}/include
    )
	

    # gtest
    enable_testing()
    add_subdirectory(external/gtest EXCLUDE_FROM_ALL)
    add_subdirectory(tests)
endif()
