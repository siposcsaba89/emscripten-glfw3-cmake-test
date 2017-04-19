cmake_minimum_required(VERSION 3.0)

project(emscripten-glfw3-test)


if (${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    option(BUILD_HTML "Build html also!" ON)

    set(EMSCRIPTEN TURE)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

message(STATUS "Cmake prefix path: ${CMAKE_PREFIX_PATH}")

#if (EMSCRIPTEN AND BUILD_HTML)
#    SET(CMAKE_EXECUTABLE_SUFFIX ".html")
#endif()


add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_DEBUG_POSTFIX _d)
if (NOT EMSCRIPTEN)
    find_package(glfw3 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
endif()

if (EMSCRIPTEN)
    if (BUILD_HTML)
        set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    endif()
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DEMSCRIPTEN=1)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1")
endif()

if (MSVC)
    find_package(glew REQUIRED CONFIG)
    target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::glew_s)
endif()
