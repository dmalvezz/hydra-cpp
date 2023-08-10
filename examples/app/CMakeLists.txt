add_library(app SHARED
    app.cpp
)

# Compile options
add_compile_options("-fPIC")
add_compile_options("--export-dynamic")

# Link yaml-cpp
find_package(yaml-cpp REQUIRED)
if(yaml-cpp_FOUND)
    target_include_directories(app PRIVATE ${YAML_CPP_INCLUDE_DIR})
    target_link_libraries(app PRIVATE ${YAML_CPP_LIBRARIES})
else()
    message(FATAL_ERROR "yaml-cpp not found")
endif(yaml-cpp_FOUND)

# Link python
find_package(PythonLibs REQUIRED VERSION 3.8)
if(PythonLibs_FOUND)
    target_include_directories(app PRIVATE ${PYTHON_INCLUDE_DIRS})
    target_link_libraries(app PRIVATE ${PYTHON_LIBRARIES})
else()
    message(FATAL_ERROR "PythonLibs not found")
endif(PythonLibs_FOUND)

# Link Boost
find_package(Boost COMPONENTS system thread python REQUIRED)
if(Boost_FOUND)
    target_include_directories(app PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(app PRIVATE ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost not found")
endif(Boost_FOUND)


add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:app> ${PROJECT_SOURCE_DIR}/app.so
)