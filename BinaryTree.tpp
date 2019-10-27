#ifndef BINARYTREE_H
#error __FILE__ should only be included from BinaryTree.h
#endif

#include <stack>
#include <tuple>
#include <string>
#include <iostream>

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
std::pair<typename BinaryTree<T>::TreeNode*, size_t> BinaryTree<T>::TreeNode::rightmostChildLeaf() {
	size_t distanceTravelled = 0;
	TreeNode* currentNode = this;
	bool leafNotFound = true;
	while (leafNotFound) {
		if (currentNode->rightChild != nullptr) {
			currentNode = currentNode->rightChild.get();
			++distanceTravelled;
		}
		else if (currentNode->leftChild != nullptr) {
			currentNode = currentNode->leftChild.get();
			++distanceTravelled;
		}
		else {
			leafNotFound = false;
		}
	}
	return std::pair<TreeNode*, size_t>(currentNode, distanceTravelled);
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
std::ostream& operator<<(std::ostream& os, typename BinaryTree<T>::TreeIterator& tree_cit) {
	return os;
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


template<class T>
void printTree(std::ostream& os, typename BinaryTree<T>::const_iterator tree_cit) {

	using node_ptr = typename BinaryTree<T>::TreeNode*;

	// pointer to node, prefix string, isLeft?, hasRightSibling?
	std::stack<std::tuple<node_ptr, std::string, bool, bool> > nodeStack;

	// printing first node
	node_ptr firstNodePtr = tree_cit.get_iter();
	if (firstNodePtr != nullptr) {

		// print the value of the first node
		os << firstNodePtr->access_value() << "\n";

		// enter the next tree level - left and right branch
		node_ptr newRightNodePtr = firstNodePtr->rightChild.get();
		node_ptr newLeftNodePtr = firstNodePtr->leftChild.get();
		if (newRightNodePtr != nullptr) {
			nodeStack.push(std::tuple<node_ptr, std::string, bool, bool>(newRightNodePtr, "", false, false));
			if (newLeftNodePtr != nullptr) {
				nodeStack.push(std::tuple<node_ptr, std::string, bool, bool>(newLeftNodePtr, "", true, true));
			}
		}
		else if (newLeftNodePtr != nullptr) {
			nodeStack.push(std::tuple<node_ptr, std::string, bool, bool>(newLeftNodePtr, "", true, false));
		}


		std::tuple<node_ptr, std::string, bool, bool> nodeTuple;

		// printing rest of nodes
		while (!nodeStack.empty()) {
			nodeTuple = nodeStack.top();
			nodeStack.pop();

				os << std::get<1>(nodeTuple);

				if (std::get<2>(nodeTuple)) {
					os << (std::get<3>(nodeTuple) ? "+-L-" : "\\-L-");
				}
				else {
					os << "\\-R-";
				}

				// print the value of the node
				os << std::get<0>(nodeTuple)->access_value() << "\n";

				// enter the next tree level - left and right branch
				std::string newPrefix = std::get<1>(nodeTuple) + (std::get<2>(nodeTuple) ? "|    " : "     ");
				node_ptr newRightNodePtr = std::get<0>(nodeTuple)->rightChild.get();
				node_ptr newLeftNodePtr = std::get<0>(nodeTuple)->leftChild.get();
				if (newRightNodePtr != nullptr) {
					nodeStack.push(std::tuple<node_ptr, std::string, bool, bool>(newRightNodePtr, newPrefix, false, false));
					if (newLeftNodePtr != nullptr) {
						nodeStack.push(std::tuple<node_ptr, std::string, bool, bool>(newLeftNodePtr, newPrefix, true, true));
					}
				}
				else if (newLeftNodePtr != nullptr) {
					nodeStack.push(std::tuple<node_ptr, std::string, bool, bool>(newLeftNodePtr, newPrefix, true, false));
				}
		}
	}
}





template<class T>
void printTree(std::ostream& os, BinaryTree<T>& tree) { // TODO
	
	/*for (typename BinaryTree<T>::const_iterator it = tree.cbegin(); it != tree.cend(); ++it) {
		os << *it << " ";
	}

	os << "\n";
	std::string preNodeStr = "+---";
	std::string spaceBeforeStr = "|   ";

	typename BinaryTree<T>::const_iterator it = tree.cbegin();
	if (it != tree.cend()) {
		os << *it << '\n';
		++it;
		size_t prevDistBelow = 0;
		size_t currDistBelow = 0;
		for (; it != tree.cend(); ++it) {
			currDistBelow = it.dist_below();
			for (size_t i = 1; i < currDistBelow; ++i) {
				os << spaceBeforeStr;
			}
			os << preNodeStr << *it << '\n';
			prevDistBelow = currDistBelow;
		}
	}*/

	printTree<T>(os, tree.cbegin());
}