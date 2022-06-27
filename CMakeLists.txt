cmake_minimum_required(VERSION 3.16)

project(buildProject VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(SOURCES
	./main.cpp
	./src/core.cpp
	./src/cpp.cpp
	./src/java.cpp
)

set(HEADERS
	./include/colors.h
	./include/core.h
	./include/cpp.h
	./include/flags.h
	./include/Header.h
	./include/java.h
)

add_executable(${PROJECT_NAME}
	${SOURCES}
	${HEADERS}
)

target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

