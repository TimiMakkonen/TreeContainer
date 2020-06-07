
set(EXAMPLE_SOURCE_LIST
	binary_tree_examples.cpp
)

set(EXAMPLE_APP_NAME "TreeContainerExamples")
add_executable("${EXAMPLE_APP_NAME}" ${EXAMPLE_SOURCE_LIST})

target_link_libraries("${EXAMPLE_APP_NAME}" PRIVATE "${LIBRARY_NAME}")
