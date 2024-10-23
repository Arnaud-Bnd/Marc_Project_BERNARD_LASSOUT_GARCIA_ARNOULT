cmake_minimum_required(VERSION 3.27)
project(Marc_Project_BERNARD_LASSOUT_GARCIA_ARNOULT C)

set(CMAKE_C_STANDARD 11)

add_executable(Marc_Project_BERNARD_LASSOUT_GARCIA_ARNOULT main.c
        loc.c
        loc.h
        moves.c
        moves.h
        map.c
        map.h
        queue.c
        queue.h
        stack.c
        stack.h
        tree_functions.h
)
