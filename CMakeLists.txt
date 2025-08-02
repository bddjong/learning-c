# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)
project(hello_world C)

# Optional: compile with warnings and C11
set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra)

# List your sources
add_executable(main.out
        main.c
        hello.c
)
