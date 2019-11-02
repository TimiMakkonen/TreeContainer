#include <string>

#include <gtest/gtest.h>

#include "../BinaryTree.h"

class BinaryTreeTest : public ::testing::Test {
protected:
	void SetUp() override {
		
	}

	BinaryTree<int> testIntBinTree;
	BinaryTree<std::string> testStringBinTree;
};

TEST_F(BinaryTreeTest, EmptyTreeTests) { // TODO

	// testing empty int tree
	EXPECT_EQ(testIntBinTree.get_root(), NULL) << "Default constructor should suppose: 'value at root' == NULL.";
	EXPECT_EQ(testIntBinTree.size(), 0) << "Default constructor should make: _size == 0.";

	// testing empty string tree
	EXPECT_EQ(testIntBinTree.get_root(), NULL) << "Default constructor should suppose: 'value at root' == NULL.";
	EXPECT_EQ(testIntBinTree.size(), 0) << "Default constructor should make: _size == 0.";
}

TEST(BinaryTreeTest, AssignmentTests) { // TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, IteratorTests) { // TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, MeasurementTests) { // TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, RootAccessTests) { // TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, EmplacementTests) { // TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, InsertionTests) { //TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, ErasureTests) { //TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, FindTests) { //TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, PrintTests) { //TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, ComparisonTests) { //TODO
	EXPECT_EQ(1, 1);
}

TEST(BinaryTreeTest, SwapTests) { //TODO
	EXPECT_EQ(1, 1);
}