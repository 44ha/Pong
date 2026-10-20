cmake_minimum_required(VERSION 3.16)
project(Pong CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML (Graphics, Window, System)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Game.h
    src/Paddle.cpp
    src/Paddle.h
    src/Ball.cpp
    src/Ball.h
)

add_executable(Pong ${SOURCES})

target_include_directories(Pong PRIVATE src)
target_link_libraries(Pong PRIVATE sfml-graphics sfml-window sfml-system)

# Copy assets folder to build output directory if present
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_custom_command(TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Pong>/assets"
    )
endif()
