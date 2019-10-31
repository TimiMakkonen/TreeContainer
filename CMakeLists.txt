cmake_minimum_required (VERSION 3.8)

project(TreeContainer VERSION 0.7.0)

enable_testing()

add_subdirectory(googletest)

add_subdirectory(tests)

add_subdirectory(examples)

set(Headers
	TreeBlueprint.h
	BinaryTree.h
)

set(Sources
	TreeBlueprint.cpp
	BinaryTree.cpp
)

set(TemplateSources
	TreeBlueprint.tpp
	BinaryTree.tpp
)


add_library(TreeContainer STATIC ${Headers} ${Sources} ${TemplateSources})