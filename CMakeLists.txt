cmake_minimum_required(VERSION 3.28)
project(DataStructures C)

set(CMAKE_C_STANDARD 17)

add_executable(DataStructures lista2.c
        libraries/BinaryTree.c
        libraries/headers/BinaryTree.h
        libraries/headers/Stack.h
        libraries/Stack.c
        libraries/Queue.c
        libraries/headers/Queue.h)
