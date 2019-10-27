
#include <iostream>

#include "BinaryTree.h"
#include <vector>

// Excuse the crudeness of these preliminary test.
// This is just a playground for me to check if/how everything works.
void preliminaryTests() {

	BinaryTree<int> myBinTree;

	myBinTree.insert(1); // 1

	std::cout << myBinTree.get_root()->access_value() << "\n\n";

	myBinTree.insert(2); // 1 -> 2
	myBinTree.insert(3); // 1 -> 2 -> 3
	myBinTree.insert_at(4, 2); // 1 -> 2 -> (3, 4)

	// insertion should fail, 2 has two children already
	auto myResult = myBinTree.insert_at(5, 2000);
	std::cout << (myResult.second ? "Success!" : "Fail!") << "\n";

	myBinTree.insert_at(6, 3); // 1 -> 2 -> ((3 -> 6), 4)
	myBinTree.insert_at(7, 4); // 1 -> 2 -> ((3 -> 6), (4 -> 7))
	myBinTree.insert_at(8, 1); // 1 -> (2 -> ((3 -> 6), (4 -> 7)), 8)
	myBinTree.insert_at(9, 8); // 1 -> (2 -> ((3 -> 6), (4 -> 7)), (8 -> 9))


	// order should be: 1 2 3 6 4 7 8 9
	std::cout << "Elements of the tree are: ";
	for (BinaryTree<int>::iterator it = myBinTree.begin(); it != myBinTree.end(); ++it) {
		std::cout << *it << " ";
	}

	std::cout << "\n------------------------\n";

	// order should be: 1 2 3 6 4 7 8 9
	std::cout << "Elements of the tree are: ";
	for (auto myNode : myBinTree) {
		std::cout << myNode << " ";
	}

	std::cout << "\n------------------------\n";

	printTree<int>(std::cout, myBinTree);

	std::cout << "\n------------------------\n";

	printTree<int>(std::cout, myBinTree.cbegin());

	std::cout << "\n------------------------\n";

	BinaryTree<int> myEmptyTree;
	printTree<int>(std::cout, myEmptyTree.begin());
	printTree<int>(std::cout, myBinTree.end());

	std::cout << "\n------------------------\n";

	// should be 5
	std::cout << "\nTree has now " << myBinTree.size() << " elements.\n";

	std::cout << "\n------------------------\n";

	std::cout << *myBinTree.begin() << "\n";

	std::cout << "\n------------------------\n";

	// TODO
	//std::cout << *myBinTree.rbegin() << "\n";

	std::cout << "\n------------------------\n";

	BinaryTree<int>::const_iterator cIt = myBinTree.cbegin();
	//*cIt = 9;
	// should be: 1, 2 and 1
	std::cout << "Const iterator, cbegin():  " << *cIt << "\n";
	std::cout << "Const iterator, ++cbegin():  " << *++cIt << "\n";
	std::cout << "Const iterator, --(++cbegin()):  " << *--cIt << "\n";

	std::cout << "\n------------------------\n";

	BinaryTree<int>::iterator myEndIt = myBinTree.end();
	std::cout << "Iterator, --end(): " << *--myEndIt << "\n";

	std::cout << "\n------------------------\n";

	BinaryTree<int>::iterator myIt = myBinTree.begin();
	//*myIt = 9;
	std::cout << "Iterator, begin():  " << *myIt << "\n";

	std::cout << "\n\n\n------------------------\n";
	std::cout << "------------------------\n";
	std::cout << "Some vector tests:\n";
	std::cout << "------------------------\n";
	std::cout << "------------------------\n";

	std::vector<int> myVec = { 1, 2, 3, 4 };
	for (auto x : myVec) {
		std::cout << x << " ";
	}

	std::cout << "\n------------------------\n";

	std::cout << *--myVec.end() << "\n";

	std::cout << "\n------------------------\n";
}




int main() {

	preliminaryTests();

	return 0;
}






