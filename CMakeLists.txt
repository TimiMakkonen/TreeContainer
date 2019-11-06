cmake_minimum_required (VERSION 3.8)

project(TreeContainer VERSION 0.8.1)

enable_testing()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
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