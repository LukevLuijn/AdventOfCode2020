cmake_minimum_required(VERSION 2.8)

project ( day_1 )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -Wconversion)

include_directories(src)
include_directories(include/format)

set( project_sources
	Main.cpp
)

set( project_headers
)

add_executable(main
	${project_sources}
	${project_headers}
)
