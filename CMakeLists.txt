cmake_minimum_required(VERSION 3.22)

cmake_policy(SET CMP0091 NEW)

project(Nameplate
    VERSION 0.5.1.0
    LANGUAGES CXX
    DESCRIPTION "Corrects defects in nameplate rendering."
    HOMEPAGE_URL "https://github.com/SmithReact/Nameplate"
)

set(ASHITA_SDK_PATH "" CACHE PATH "Path to the current Ashita 4 plugins/sdk directory")
option(NAMEPLATE_ENABLE_PATCHES "Enable validated FFXiMain code patches" OFF)

if(NOT MSVC)
    message(FATAL_ERROR "Nameplate must use the MSVC ABI expected by Ashita.")
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "Nameplate must be configured with a 32-bit generator/toolchain.")
endif()

if(NOT EXISTS "${ASHITA_SDK_PATH}/Ashita.h")
    message(FATAL_ERROR "Set ASHITA_SDK_PATH to the current Ashita 4 plugins/sdk directory.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/versioninfo.rc.in versioninfo.rc COPYONLY)

add_library(Nameplate SHARED
    src/Nameplate.cpp
    src/Nameplate.h
    src/findsignature.h
    src/bytes/bytes.h
    src/Ashita/Ashita.cpp
    src/Ashita/exports.h
    src/exports.def
    "${CMAKE_CURRENT_BINARY_DIR}/versioninfo.rc"
)

target_include_directories(Nameplate PRIVATE
    "${ASHITA_SDK_PATH}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_definitions(Nameplate PRIVATE
    WIN32_LEAN_AND_MEAN
    NAMEPLATE_ENABLE_PATCHES=$<BOOL:${NAMEPLATE_ENABLE_PATCHES}>
)

target_compile_options(Nameplate PRIVATE /EHa /permissive- /W4)
target_link_libraries(Nameplate PRIVATE Psapi)

set_property(TARGET Nameplate PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
