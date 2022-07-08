cmake_minimum_required(VERSION 3.16)

project(buildProject VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(src)

add_executable(${PROJECT_NAME}
	main.cpp
	BuildProject.h
)

target_include_directories(${PROJECT_NAME} PUBLIC .)

target_link_libraries(${PROJECT_NAME} PUBLIC core filetypes)
