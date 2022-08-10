set(HEADERS
	cpp/CppProject.h
	java/JavaProject.h
	python/PythonProject.h
	template/Project.h
)

set(SOURCES
	cpp/CppProject.cpp
	java/JavaProject.cpp
	python/PythonProject.cpp
	template/Project.cpp
)

add_library(filetypes ${SOURCES} ${HEADERS})

target_link_libraries(filetypes core)

target_include_directories(
	filetypes
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/cpp
	${CMAKE_CURRENT_SOURCE_DIR}/java
	${CMAKE_CURRENT_SOURCE_DIR}/python
	${CMAKE_CURRENT_SOURCE_DIR}/template
)
