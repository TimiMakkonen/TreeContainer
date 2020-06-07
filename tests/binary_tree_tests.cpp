

#include <gtest/gtest.h>

#include <tree-container/binary_tree.h>

class BinaryTreeTest : public ::testing::Test {
protected:

	void SetUp() override {

		this->setUpIntBinTree1();		
	}

	void setUpIntBinTree1() {

		intBinTree1.insert(1); // 1
		intBinTree1.insert(2); // 1 -> 2
		intBinTree1.insert(3); // 1 -> 2 -> 3
		intBinTree1.insert_child(2, 4); // 1 -> 2 -> (3, 4)
		intBinTree1.insert_child(3, 6); // 1 -> 2 -> ((3 -> 6), 4)
		intBinTree1.insert_child(4, 7); // 1 -> 2 -> ((3 -> 6), (4 -> 7))
		intBinTree1.insert_child(1, 8); // 1 -> (2 -> ((3 -> 6), (4 -> 7)), 8)
		intBinTree1.insert_child(8, 9); // 1 -> (2 -> ((3 -> 6), (4 -> 7)), (8 -> 9))

		// should be:
		//	1
		//	+-L-2
		//	|    +-L-3
		//	|    |    \-L-6
		//	|    \-R-4
		//	|         \-L-7
		//	\-R-8
		//		 \-L-9
	}




	// declarations:

	tree_container::binary_tree<int> emptyIntBinTree;
	tree_container::binary_tree<std::string> emptyStringBinTree;

	tree_container::binary_tree<int> intBinTree1;
};

using BinaryTreeDeathTest = BinaryTreeTest;

TEST_F(BinaryTreeDeathTest, EmptyTreeTests) { // TODO

	// testing empty int tree
	EXPECT_DEATH(emptyIntBinTree.get_root(), ""); // trying to get_root of empty tree should terminate program
	EXPECT_EQ(emptyIntBinTree.size(), 0) << "Default constructor should make: _size == 0.";

	// testing empty string tree
	EXPECT_DEATH(emptyStringBinTree.get_root(), ""); // trying to get_root of empty tree should terminate program
	EXPECT_EQ(emptyStringBinTree.size(), 0) << "Default constructor should make: _size == 0.";
}

TEST_F(BinaryTreeTest, AssignmentTests) { // TODO
	EXPECT_EQ(1, 1);
}

TEST_F(BinaryTreeTest, IteratorTests) { // TODO

	EXPECT_EQ(emptyIntBinTree.begin(), emptyIntBinTree.end());

	EXPECT_EQ(*intBinTree1.begin(), 1);
	EXPECT_EQ(intBinTree1.end().get_iter(), nullptr);
	EXPECT_EQ(*intBinTree1.rbegin(), 9);
	EXPECT_EQ(*(--intBinTree1.rend()),1);
	EXPECT_EQ(*intBinTree1.cbegin(), 1);
	EXPECT_EQ(intBinTree1.cend().get_iter(), nullptr);
	EXPECT_EQ(*intBinTree1.crbegin(), 9);
	EXPECT_EQ(*(--intBinTree1.crend()), 1);

	// traversing with iterator tests:
	tree_container::binary_tree<int>::iterator it1 = intBinTree1.begin();
	EXPECT_EQ(*it1, 1);
	++it1;
	EXPECT_EQ(*it1, 2);
	it1++;
	EXPECT_EQ(*it1, 3);
	std::advance(it1, 3);
	EXPECT_EQ(*it1, 7);
	++it1;
	EXPECT_EQ(*it1, 8);
	--it1;
	EXPECT_EQ(*it1, 7);
	it1--;
	EXPECT_EQ(*it1, 4);
	std::advance(it1, -3);
	EXPECT_EQ(*it1, 2);

	// for loop iterator tests:
	std::stringstream ss1;
	for (tree_container::binary_tree<int>::iterator it = intBinTree1.begin(); it != intBinTree1.end(); ++it) {
		ss1 << *it << " ";
	}
	EXPECT_EQ(ss1.str(), "1 2 3 6 4 7 8 9 ") 
		<< "Normal iterator for loop should print all nodes in order (depth-left first).";

	std::stringstream ss2;
	for (int myNode : intBinTree1) {
		ss2 << myNode << " ";
	}
	EXPECT_EQ(ss2.str(), "1 2 3 6 4 7 8 9 ") 
		<< "Normal foreach loop should print all nodes in order (depth-left first).";

}

TEST_F(BinaryTreeTest, MeasurementTests) { // TODO

	EXPECT_TRUE(emptyIntBinTree.empty());
	EXPECT_FALSE(intBinTree1.empty());

	EXPECT_EQ(emptyIntBinTree.size(), 0);
	EXPECT_EQ(intBinTree1.size(), 8);

	EXPECT_EQ(emptyIntBinTree.height(), 0);
	EXPECT_EQ(intBinTree1.height(), 3);

	EXPECT_EQ(intBinTree1.subtree_size(++intBinTree1.begin()), 5);

	EXPECT_EQ(intBinTree1.subtree_size(1), 8);
	EXPECT_EQ(intBinTree1.subtree_size(2), 5);
	EXPECT_EQ(intBinTree1.subtree_size(3), 2);
	EXPECT_EQ(intBinTree1.subtree_size(6), 1);
	EXPECT_EQ(intBinTree1.subtree_size(4), 2);
	EXPECT_EQ(intBinTree1.subtree_size(7), 1);
	EXPECT_EQ(intBinTree1.subtree_size(8), 2);
	EXPECT_EQ(intBinTree1.subtree_size(9), 1);
	EXPECT_EQ(intBinTree1.subtree_size(11), 0);
}

TEST_F(BinaryTreeTest, RootAccessTests) { // TODO
	EXPECT_EQ(1, 1);
}

TEST_F(BinaryTreeTest, EmplacementTests) { // TODO
	EXPECT_EQ(1, 1);
}

TEST_F(BinaryTreeTest, InsertionTests) { //TODO

	// insertion should fail, 2 has two children already
	std::pair<tree_container::binary_tree<int>::iterator, bool> failedInsert1 = intBinTree1.insert_child(2, 5);
	EXPECT_FALSE(failedInsert1.second) << "Insert should return false if parent already has two children.";
	EXPECT_EQ(*failedInsert1.first, 2) << "Insert should return parent iterator if parent already has two children.";

}

TEST_F(BinaryTreeTest, ErasureTests) { //TODO
	EXPECT_EQ(1, 1);
}

TEST_F(BinaryTreeTest, FindTests) { //TODO
	EXPECT_EQ(1, 1);
}

TEST_F(BinaryTreeTest, PrintTests) { //TODO

	std::stringstream ss1;
	tree_container::printTree<int>(ss1, emptyIntBinTree);
	EXPECT_EQ(ss1.str(), "") << "printTree with emptyIntBinTree should print nothing.";
	ss1.str("");
	ss1.clear();
	tree_container::printTree<int>(ss1, emptyIntBinTree.begin());
	EXPECT_EQ(ss1.str(), "") << "printTree with emptyIntBinTree.begin() should print nothing.";
	ss1.str("");
	ss1.clear();
	tree_container::printTree<int>(ss1, emptyIntBinTree.end());
	EXPECT_EQ(ss1.str(), "") << "printTree with emptyIntBinTree.end() should print nothing.";
	ss1.str("");
	ss1.clear();



	tree_container::printTree<int>(ss1, intBinTree1);
	EXPECT_EQ(ss1.str(), "1\n+-L-2\n|    +-L-3\n|    |    \\-L-6\n|    \\-R-4\n|         \\-L-7\n\\-R-8\n     \\-L-9\n")
				<< "printTree with intBinTree1.begin() should print correct tree.";
	std::stringstream ss2;
	tree_container::printTree<int>(ss2, intBinTree1.begin());
	EXPECT_EQ(ss1.str(), ss2.str()) << "printTree with intBinTree1.begin() should print correct tree.";
	ss1.str("");
	ss1.clear();
	tree_container::printTree<int>(ss1, intBinTree1.end());
	EXPECT_EQ(ss1.str(), "") << "printTree with intBinTree1.end() should print nothing.";



	EXPECT_EQ(1, 1);
}

TEST_F(BinaryTreeTest, ComparisonTests) { //TODO
	EXPECT_EQ(1, 1);
}

TEST_F(BinaryTreeTest, SwapTests) { //TODO
	EXPECT_EQ(1, 1);
}