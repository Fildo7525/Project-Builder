set(HEADERS
	cpp/CppProject.h
	java/JavaProject.h
	template/Project.h
)

set(SOURCES
	cpp/CppProject.cpp
	java/JavaProject.cpp
	template/Project.cpp
)

add_library(filetypes ${SOURCES} ${HEADERS})

target_link_libraries(filetypes core)

target_include_directories(
	filetypes
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/cpp
	${CMAKE_CURRENT_SOURCE_DIR}/java
	${CMAKE_CURRENT_SOURCE_DIR}/template
)
