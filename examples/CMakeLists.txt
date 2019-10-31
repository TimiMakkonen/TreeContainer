cmake_minimum_required (VERSION 3.8)

set(ExampleSources
	BinaryTree_Examples.cpp
)

add_executable(TreeContainerExamples ${ExampleSources})

target_link_libraries(TreeContainerExamples
	TreeContainer
)

