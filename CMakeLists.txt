cmake_minimum_required(VERSION 3.20)

project(vision)

set(CMAKE_CXX_STANDARD 20)

set(VISION "vision")

set(SOURCES "src/Image.cpp")
set(HEADERS "include/Vision/Core.hpp" "include/Vision/Vision.hpp")

add_library(${VISION} ${SOURCES} ${HEADERS})
target_include_directories(${VISION} PUBLIC "include/Vision")

set(TARGET "main")

set(DRIVER "src/Main.cpp")

add_executable(${TARGET} ${DRIVER})

target_link_libraries(${TARGET} PUBLIC ${VISION})
target_include_directories(${TARGET} PUBLIC "include")
