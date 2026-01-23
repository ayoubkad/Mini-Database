cmake_minimum_required(VERSION 3.10)
project(Mini_Database C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Mini_Database
        main.c
        student.c
        student.h
        undo_stack.c
        undo_stack.h
        arbres_binaire.c
        arbres_binaire.h)

# Executable pour les tests
add_executable(Test_Student
        test_student.c
        student.c
        student.h
        undo_stack.c
        undo_stack.h
        arbres_binaire.c
        arbres_binaire.h)

# Activer CTest
enable_testing()
add_test(NAME StudentTests COMMAND Test_Student)

