cmake_minimum_required(VERSION 3.9)

include(cmake/ProjectOptions.cmake)
include(cmake/DownloadCPM.cmake)

project(
    APC
    VERSION 0.1.0
    DESCRIPTION "Audio Player in C"
)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS OFF)

set_project_options("headers" "dependencies")

add_subdirectory(src)
