
#include <iostream>

#include <tree-container/binary_tree.h>

// Excuse the crudeness of these preliminary test.
// This is just a playground to check if/how everything works.
void preliminaryTests() {
	std::cout << "\n";
	std::cout << "|-----------------------------------------------------------------|\n";
	std::cout << "| Crude examples / preliminary tests / showcase of 'binary_tree'. |\n";
	std::cout << "|-----------------------------------------------------------------|\n\n";

	tree_container::binary_tree<int> myBinTree;

	std::cout << "Inserting ints to myBinTree...\n\n";

	myBinTree.insert(1); // 1

	std::cout << "Root of myBinTree: " << myBinTree.get_root() << "\n\n";

	myBinTree.insert(2); // 1 -> 2
	myBinTree.insert(3); // 1 -> 2 -> 3
	myBinTree.insert_child(2, 4); // 1 -> 2 -> (3, 4)

	// insertion should fail, 2 has two children already
	auto myResult = myBinTree.insert_child(2, 5);
	std::cout << "Did insertion (5 to 2) fail?: " << (myResult.second ? "No!" : "Yes!") << "\n\n";

	myBinTree.insert_child(3, 6); // 1 -> 2 -> ((3 -> 6), 4)
	myBinTree.insert_child(4, 7); // 1 -> 2 -> ((3 -> 6), (4 -> 7))
	myBinTree.insert_child(1, 8); // 1 -> (2 -> ((3 -> 6), (4 -> 7)), 8)
	myBinTree.insert_child(8, 9); // 1 -> (2 -> ((3 -> 6), (4 -> 7)), (8 -> 9))

	std::cout << "Done with inserting ints to myBinTree...";

	std::cout << "\n------------------------\n";

	// order should be: 1 2 3 6 4 7 8 9
	std::cout << "Iterator for loop:\n" << "Elements of the tree are: ";
	for (tree_container::binary_tree<int>::iterator it = myBinTree.begin(); it != myBinTree.end(); ++it) {
		std::cout << *it << " ";
	}

	std::cout << "\n------------------------\n";

	// order should be: 1 2 3 6 4 7 8 9
	std::cout << "Foreach loop:\n" << "Elements of the tree are: ";
	for (auto myNode : myBinTree) {
		std::cout << myNode << " ";
	}

	std::cout << "\n------------------------\n";

	std::cout << "Height of myBinTree: " << myBinTree.height() << "\n";
	std::cout << "Size of myBinTree: " << myBinTree.size();

	std::cout << "\n------------------------\n";

	std::cout << "Print of myBinTree:\n";
	tree_container::printTree<int>(std::cout, myBinTree);

	std::cout << "\n------------------------\n";

	std::cout << "Print of myBintree starting from myBinTree.cbegin():\n";
	tree_container::printTree<int>(std::cout, myBinTree.cbegin());

	std::cout << "\n------------------------";

	// couple empty tree print checks
	tree_container::binary_tree<int> myEmptyTree;
	tree_container::printTree<int>(std::cout, myEmptyTree.begin());
	tree_container::printTree<int>(std::cout, myBinTree.end());

	std::cout << "\n------------------------\n";

	std::cout << "*myBinTree.rbegin(): " << *myBinTree.rbegin();

	std::cout << "\n------------------------\n";

	tree_container::binary_tree<int>::const_iterator cIt = myBinTree.cbegin();
	//*cIt = 9;
	// should be: 1, 2 and 1
	std::cout << "Const iterator, cbegin():  " << *cIt << "\n";
	std::cout << "Const iterator, ++cbegin():  " << *++cIt << "\n";
	std::cout << "Const iterator, --(++cbegin()):  " << *--cIt;

	std::cout << "\n------------------------\n";

	tree_container::binary_tree<int>::iterator myEndIt = myBinTree.end();
	std::cout << "Iterator: --end(): " << *--myEndIt;

	std::cout << "\n------------------------\n";

	tree_container::binary_tree<int>::iterator myIt = myBinTree.begin();
	//*myIt = 9;
	std::cout << "Iterator: begin():  " << *myIt;

	std::cout << "\n------------------------\n";

	std::cout << "Looping through elements of myBinTree printing their subtree sizes: \n";
	for (auto it = myBinTree.begin(); it != myBinTree.end(); ++it) {
		std::cout << *it << "(" << myBinTree.subtree_size(it) << "), ";
	}

	std::cout << "\n------------------------\n";

	std::cout << "myBinTree.subtree_size(8): " << myBinTree.subtree_size(8);

	std::cout << "\n------------------------\n";
}

int main() {

	preliminaryTests();
	
	return 0;
}


