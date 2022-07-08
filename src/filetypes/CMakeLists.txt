set(HEADERS
	cpp/cpp.h
	java/java.h
)

set(SOURCES
	cpp/cpp.cpp
	java/java.cpp
)

add_library(filetypes ${SOURCES} ${HEADERS})

target_link_libraries(filetypes core)

target_include_directories(
	filetypes
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/cpp
	${CMAKE_CURRENT_SOURCE_DIR}/java
)
