cmake_minimum_required(VERSION 3.28)
project(DataStructures C)

# Define o diretório de bibliotecas
set(LIBS_DIR ${CMAKE_SOURCE_DIR}/libs)

# Adiciona bibliotecas
add_library(BinarySearchTree ${LIBS_DIR}/BinarySearchTree/BinarySearchTree.c ${LIBS_DIR}/BinarySearchTree/BinarySearchTree.h)
add_library(BinaryTree ${LIBS_DIR}/BinaryTree/BinaryTree.c ${LIBS_DIR}/BinaryTree/BinaryTree.h)
add_library(Graph ${LIBS_DIR}/Graph/Graph.c ${LIBS_DIR}/Graph/Graph.h)
add_library(LinkedList ${LIBS_DIR}/LinkedList/LinkedList.c ${LIBS_DIR}/LinkedList/LinkedList.h)
add_library(Queue ${LIBS_DIR}/Queue/Queue.c ${LIBS_DIR}/Queue/Queue.h)
add_library(Stack ${LIBS_DIR}/Stack/Stack.c ${LIBS_DIR}/Stack/Stack.h)

# Inclui diretórios de cabeçalhos
include_directories(${LIBS_DIR}/BinarySearchTree)
include_directories(${LIBS_DIR}/BinaryTree)
include_directories(${LIBS_DIR}/Graph)
include_directories(${LIBS_DIR}/LinkedList)
include_directories(${LIBS_DIR}/Queue)
include_directories(${LIBS_DIR}/Stack)

# Executáveis para listas
add_executable(lista01 src/lista01.c)
target_link_libraries(lista01 Queue Stack)

add_executable(lista02 src/lista02.c)
target_link_libraries(lista02 BinaryTree Queue Stack)

add_executable(lista03 src/lista03.c)
target_link_libraries(lista03 BinaryTree BinarySearchTree Queue)

add_executable(lista05-1 src/lista05-1.c)
target_link_libraries(lista05-1 Graph)

add_executable(lista05-2 src/lista05-2.c)

add_executable(lista06 src/lista06.c)
