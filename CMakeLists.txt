cmake_minimum_required(VERSION 3.16)
project(y-lib-qrgen)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# y-- source tree to compile against; yenv passes its installed toolchain
set(YLANG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../y---lang" CACHE PATH "y-- source directory")
add_library(y-qrgen SHARED module.cpp qrcodegen.cpp)
# symbols come from the ymm process at load time
if(APPLE)
    target_link_options(y-qrgen PRIVATE -undefined dynamic_lookup)
endif()
target_include_directories(y-qrgen PRIVATE ${YLANG_DIR}/include ${YLANG_DIR}/include/ylang ${YLANG_DIR}/src)
