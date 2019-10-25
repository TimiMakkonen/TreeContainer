#ifndef BINARYTREE_H
#error __FILE__ should only be included from BinaryTree.h
#endif

#include <stack>

#include "BinaryTree.h"

template<class T>
BinaryTree<T>::TreeNode::TreeNode(const value_type& value, TreeNode* const parent) : data(value), parent(parent) {}

template<class T>
typename BinaryTree<T>::TreeNode* BinaryTree<T>::TreeNode::leftmostChild() {

	TreeNode* previousNode = nullptr;
	TreeNode* currentNode = this;
	while (currentNode != nullptr) {
		previousNode = currentNode;
		currentNode = currentNode->leftChild.get();
	}
	return previousNode;
}

template<class T>
typename BinaryTree<T>::TreeNode* BinaryTree<T>::TreeNode::rightmostChildLeaf() {

	TreeNode* currentNode = this;
	bool leafNotFound = true;
	while (leafNotFound) {
		if (currentNode->rightChild != nullptr) {
			currentNode = currentNode->rightChild.get();
		}
		else if (currentNode->leftChild != nullptr) {
			currentNode = currentNode->leftChild.get();
		}
		else {
			leafNotFound = false;
		}
	}
	return currentNode;
}


template<class T>
BinaryTree<T>::~BinaryTree() {
}

template<class T>
typename BinaryTree<T>::iterator BinaryTree<T>::begin() {
	return BinaryTree<T>::iterator(this->root, this->root);
}

template<class T>
typename BinaryTree<T>::const_iterator BinaryTree<T>::begin() const {
	return BinaryTree<T>::const_iterator(this->root, this->root);
}

template<class T>
typename BinaryTree<T>::iterator BinaryTree<T>::end() {
	return BinaryTree<T>::iterator(nullptr, this->root);
}

template<class T>
typename BinaryTree<T>::const_iterator BinaryTree<T>::end() const {
	return BinaryTree<T>::const_iterator(nullptr, this->root);
}

template<class T>
typename BinaryTree<T>::reverse_iterator BinaryTree<T>::rbegin() {
	return BinaryTree<T>::reverse_iterator(this->end());
}

template<class T>
typename BinaryTree<T>::const_reverse_iterator BinaryTree<T>::rbegin() const {
	return BinaryTree<T>::const_reverse_iterator(this->end());
}

template<class T>
typename BinaryTree<T>::reverse_iterator BinaryTree<T>::rend() {
	return BinaryTree<T>::reverse_iterator(this->begin());
}

template<class T>
typename BinaryTree<T>::const_reverse_iterator BinaryTree<T>::rend() const {
	return BinaryTree<T>::const_reverse_iterator(this->begin());
}

template<class T>
typename BinaryTree<T>::const_iterator BinaryTree<T>::cbegin() {
	return BinaryTree<T>::const_iterator(this->root, this->root);
}

template<class T>
typename BinaryTree<T>::const_iterator BinaryTree<T>::cend() {
	return BinaryTree<T>::const_iterator(nullptr, this->root);
}

template<class T>
typename BinaryTree<T>::const_reverse_iterator BinaryTree<T>::crbegin() const {
	return BinaryTree<T>::const_reverse_iterator(this->cend());
}

template<class T>
typename BinaryTree<T>::const_reverse_iterator BinaryTree<T>::crend() const {
	return BinaryTree<T>::const_reverse_iterator(this->cbegin());
}

template<class T>
bool BinaryTree<T>::empty() const {
	return (this->size() == 0);
}

template<class T>
size_t BinaryTree<T>::size() const {
	return this->_size;
}

template<class T>
typename BinaryTree<T>::TreeNode* BinaryTree<T>::get_root() const {
	return this->root.get();
}

template<class T> // insert value into tree (to leftmost location)
typename BinaryTree<T>::iterator BinaryTree<T>::insert(const value_type& value) {


	if (this->root == nullptr) {
		this->root = std::make_unique<TreeNode>(value, nullptr);
		++(this->_size);
		return iterator(this->root, this->root);
	}
	else {

		TreeNode* parentNode = this->root.get()->leftmostChild();
		parentNode->leftChild = std::make_unique<TreeNode>(value, parentNode);
		++(this->_size);
		return iterator(parentNode->leftChild, this->root);
	}
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool>
			BinaryTree<T>::insert_at(const value_type& value, 
									const value_type& parentValue, 
									const bool tryToInsertLeftFirst/* = true*/) {

	iterator parentNodeIt = this->find(parentValue);

	if (parentNodeIt == this->end()) {
		return std::pair<iterator, bool>(this->end(), false);
	}
	else {
		TreeNode* parentNode = parentNodeIt.get_iter();
		if (tryToInsertLeftFirst) {
			if (parentNode->leftChild == nullptr) {
				parentNode->leftChild = std::make_unique<TreeNode>(value, parentNode);
				++(this->_size);
				return std::pair<iterator, bool>(iterator(parentNode->leftChild, this->root), true);
			}
			else if (parentNode->rightChild == nullptr) {
				parentNode->rightChild = std::make_unique<TreeNode>(value, parentNode);
				++(this->_size);
				return std::pair<iterator, bool>(iterator(parentNode->rightChild, this->root), true);
			}
			else {
				// if parent already has 2 children
				return std::pair<iterator, bool>(parentNodeIt, false);
			}
		}
		else {
			if (parentNode->rightChild == nullptr) {
				parentNode->rightChild = std::make_unique<TreeNode>(value, parentNode);
				++(this->_size);
				return std::pair<iterator, bool>(iterator(parentNode->rightChild, this->root), true);
			}
			else if (parentNode->leftChild == nullptr) {
				parentNode->leftChild = std::make_unique<TreeNode>(value, parentNode);
				++(this->_size);
				return std::pair<iterator, bool>(iterator(parentNode->leftChild, this->root), true);
			}
			else {
				// if parent already has 2 children
				return std::pair<iterator, bool>(parentNodeIt, false);
			}
		}
	}
}



//-------------ORIGINAL INSERTIONS---------TO BE DELETED-------------
// insert element
//BinaryTreeNode<T>& insert(const T& value);
//BinaryTreeNode<T>* insert(const T& value, const T& parent = this->root->data);
//-------------------------------------------------------------------


//template<class T>
//BinaryTreeNode<T>& BinaryTree<T>::insert(const T& value) {
//
//	if (this->root == nullptr) {
//		this->root = std::make_unique<BinaryTreeNode<T>>(value, nullptr);
//		return *this->root;
//	}
//	else {
//		BinaryTreeNode<T>* previousNode = nullptr;
//		BinaryTreeNode<T>* currentNode = this->root;
//		while (currentNode != nullptr) {
//			previousNode = currentNode;
//			currentNode = currentNode->leftChild;
//		}
//		previousNode->leftChild = std::make_unique<BinaryTreeNode<T>>(value, previousNode);
//		return *previousNode->leftChild;
//	}
//}
//
//template<class T>
//BinaryTreeNode<T>* BinaryTree<T>::insert(const T& value, const T& parentValue) {
//
//	BinaryTreeNode<T>* parentNode = this->find(parentValue);
//
//	if (parentNode != nullptr) {
//		if (parentNode->leftChild == nullptr) {
//			parentNode->leftChild = std::make_unique<BinaryTreeNode<T>>(value, parentNode);
//			return parentNode->leftChild;
//		}
//		else if (parentNode->rightChild == nullptr) {
//			parentNode->rightChild = std::make_unique<BinaryTreeNode<T>>(value, parentNode);
//			return parentNode->rightChild;
//		}
//		else {
//			std::cerr << "Error: Parent already has 2 children\n";
//		}
//	}
//	return nullptr;
//}



template<class T>
typename BinaryTree<T>::iterator BinaryTree<T>::find(const value_type& value) {

	for (iterator it = this->begin(); it != this->end(); ++it) {
		if (*it == value) {
			return it;
		}
	}
	return this->end();
}

template<class T>
typename BinaryTree<T>::const_iterator BinaryTree<T>::find(const value_type& value) const {

	for (const_iterator it = this->begin(); it != this->end(); ++it) {
		if (*it == value) {
			return it;
		}
	}
	return this->end();
}


//----------------ORIGINAL FINDER-----------TO BE DELETED-----------------
//// get pointer to an element on tree
//BinaryTreeNode<T>* find(const T& value);
//iterator find(const value_type& value) const; // to find the first occurrence of value using iterator (return this->end() if no luck)
//------------------------------------------------------------------------
//template<class T>
//BinaryTreeNode<T>* BinaryTree<T>::find(const T& value) {
//
//	if (this->root == nullptr) {
//		std::cerr << "Error: Parent not found\n";
//		return nullptr;
//	}
//	else {
//
//		//non-recursive depth first search
//		BinaryTreeNode<T>* nodePtr = this->root;
//		std::stack<BinaryTreeNode<T>*> nodeStack;
//		nodeStack.push(root);
//
//		while (!nodeStack.empty()) {
//			nodePtr = nodeStack.top();
//			if (nodePtr->data == value) {
//				return nodePtr;
//			}
//			nodeStack.pop();
//			if (nodePtr->rightChild != nullptr) {
//				nodeStack.push(nodePtr->rightChild);
//			}
//			if (nodePtr->leftChild != nullptr) {
//				nodeStack.push(nodePtr->leftChild);
//			}
//		}
//	}
//	std::cerr << "Error: Parent not found\n";
//	return nullptr;
//}


template<class T>
size_t BinaryTree<T>::count(const value_type& value) const {

	size_t counter = 0;
	for (iterator it = this->begin(); it != this->end(); ++it) {
		if (*it == value) {
			++counter;
		}
	}
	return counter;
}

template<class T>
bool BinaryTree<T>::has(const value_type& value) {
	if (this->find(value) == this->end()) {
		return false;
	}
	else {
		return true;
	}
}








template<class T>
bool operator==(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs) {
	return (lhs->get_root() == rhs->get_root());
}

template<class T>
bool operator!=(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs) {
	return !operator==(lhs, rhs);
}

template<class T>
bool operator<(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs) {
	return (lhs->size() < rhs->size());
}

template<class T>
bool operator<=(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs) {
	return !operator>(lhs, rhs);
}

template<class T>
bool operator>(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs) {
	return (lhs->size() > rhs->size());
}

template<class T>
bool operator>=(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs) {
	return !operator<(lhs, rhs);
}

template<class T>
void swap(BinaryTree<T>& lhs, BinaryTree<T>& rhs) {
	lhs.swap(rhs);
}
