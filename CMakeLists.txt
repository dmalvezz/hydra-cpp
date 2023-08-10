cmake_minimum_required(VERSION 3.16)
project(project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compile options
add_compile_options("-O3")
add_compile_options("-Wall")

# Example
add_executable(${PROJECT_NAME} examples/main.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/examples/config.yaml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Project folders
include_directories(include)
add_subdirectory(examples/app)

# Link yaml-cpp
find_package(yaml-cpp REQUIRED)
if(yaml-cpp_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${YAML_CPP_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${YAML_CPP_LIBRARIES})
else()
    message(FATAL_ERROR "yaml-cpp not found")
endif(yaml-cpp_FOUND)

target_link_libraries(${PROJECT_NAME} PRIVATE app)