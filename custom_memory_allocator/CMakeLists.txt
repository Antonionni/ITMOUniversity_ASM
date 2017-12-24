cmake_minimum_required(VERSION 3.9)
project(custom_memory_allocator C)
set(CMAKE_C_STANDARD 11)

file(GLOB LIBS "include/*.h")
file(GLOB SRC "src/*.c")

include_directories(include/)

add_executable(custom_memory_allocator ${SRC} ${LIBS})
target_link_libraries(custom_memory_allocator m)