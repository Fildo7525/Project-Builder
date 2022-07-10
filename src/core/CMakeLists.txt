set(HEADERS
	colors.h
	core.h
	flags.h
)

set(SOURCES
	core.cpp
)

add_library(core ${SOURCES} ${HEADERS})

target_include_directories(
	core
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src/filetypes/template
	${CMAKE_SOURCE_DIR}
)
