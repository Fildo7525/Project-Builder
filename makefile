SOURCES = ./src/java.cpp ./src/cpp.cpp
HEADER = ./include/Header.h

build: main.cpp ${HEADER} ${SOURCES}
	g++ main.cpp ${SOURCES} -std=c++17 -O3 -o buildProject
