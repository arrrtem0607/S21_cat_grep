cmake_minimum_required(VERSION 3.27)
project(S21_cat_grep C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(S21_cat_grep s21_cat.c)
