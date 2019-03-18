cmake_minimum_required(VERSION 3.12)
project(Prism)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(Prism main.cpp src/Encryptor.c)

target_link_libraries(Prism crypto)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)