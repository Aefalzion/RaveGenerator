cmake_minimum_required(VERSION 3.8)
project(RaveGenerator)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c int_tree.h dictionary.h generator.h files.h logs.h random.h)
add_executable(RaveGenerator ${SOURCE_FILES} int_tree.h generator.h files.h random.h)