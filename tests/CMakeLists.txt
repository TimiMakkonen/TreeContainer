cmake_minimum_required (VERSION 3.8)

set(TestSources
	BinaryTree_Tests.cpp
)

add_executable(TreeContainerTests ${TestSources})

target_link_libraries(TreeContainerTests 
	gtest_main
	TreeContainer
)

add_test(
	NAME TreeContainerTests
	COMMAND TreeContainerTests
)

