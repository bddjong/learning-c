cmake_minimum_required(VERSION 3.16)
project(HelloTriangle C)

set(CMAKE_C_STANDARD 11)

if(APPLE)
    enable_language(OBJC)
endif()

# PATH TO Sokol
set(SOKOL_DIR ${CMAKE_SOURCE_DIR}/external/sokol)

add_executable(HelloTriangle
        main.m
)

target_include_directories(HelloTriangle PRIVATE ${SOKOL_DIR})

target_compile_definitions(HelloTriangle PRIVATE
        SOKOL_METAL
        SOKOL_IMPL
        SOKOL_APP_IMPL
        SOKOL_GFX_IMPL
        SOKOL_GLUE_IMPL
)

if(APPLE)
    target_link_libraries(HelloTriangle
            "-framework Cocoa"
            "-framework QuartzCore"
            "-framework Metal"
            "-framework MetalKit"
    )
endif()
