cmake_minimum_required(VERSION 3.16)

project(buildProject VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
	./src/cpp.cpp
	./src/java.cpp
	./main.cpp
)

set(HEADERS
	./include/Header.h
)

add_executable(${PROJECT_NAME}
	${SOURCES}
	${HEADERS}
)

target_link_directories(${PROJECT_NAME} PUBLIC ./include)

