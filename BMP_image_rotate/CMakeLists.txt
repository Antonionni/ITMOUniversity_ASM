cmake_minimum_required(VERSION 3.9)
project(BMP_image_rotate C)
set(CMAKE_C_STANDARD 11)

file(GLOB LIBS "include/*.h")
file(GLOB SRC "src/*.c")

include_directories(include/)

add_executable(BMP_image_rotate ${SRC} ${LIBS} include/image.h src/image.c)