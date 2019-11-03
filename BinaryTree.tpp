#include "BinaryTree.h"
#include "BinaryTree.h"
#include "BinaryTree.h"
#include "BinaryTree.h"
#include "BinaryTree.h"
#include "BinaryTree.h"
#include "BinaryTree.h"
#ifndef BINARYTREE_H
#error __FILE__ should only be included from BinaryTree.h
#endif

#include <stack>
#include <tuple>
#include <string>
#include <iostream>

#include "BinaryTree.h"

template<class T>
BinaryTree<T>::TreeNode::TreeNode(const TreeNode& other, TreeNode* const parent)
	: parent(parent),
	leftChild(other.leftChild ? std::make_unique<TreeNode>(*(other.leftChild), this) : nullptr),
	rightChild(other.rightChild ? std::make_unique<TreeNode>(*(other.rightChild), this) : nullptr)
	{ }

template<class T>
BinaryTree<T>::TreeNode::TreeNode(value_type value, TreeNode* const parent) : data(std::move(value)), parent(parent) {}

template<class T>
BinaryTree<T>::TreeNode::TreeNode(const TreeNode& other)
	: parent(nullptr),
	leftChild(other.leftChild ? std::make_unique<TreeNode>(*(other.leftChild), this) : nullptr),
	rightChild(other.rightChild ? std::make_unique<TreeNode>(*(other.rightChild), this) : nullptr)
	{ }

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
size_t BinaryTree<T>::TreeNode::subtree_size() {
	size_t subSize = 1;

	// non-recursive depth-first traversal
	TreeNode* currentNode = this;
	std::stack<TreeNode*> nodeStack;
	nodeStack.push(currentNode);

	while (!nodeStack.empty()) {
		currentNode = nodeStack.top();
		nodeStack.pop();

		if (currentNode->rightChild != nullptr) {
			++subSize;
			nodeStack.push(currentNode->rightChild.get());
		}
		if (currentNode->leftChild != nullptr) {
			++subSize;
			nodeStack.push(currentNode->leftChild.get());
		}
	}
	return subSize;
}

template<class T>
template<class InputIterator>
BinaryTree<T>::BinaryTree(InputIterator first, InputIterator last) {

	for (InputIterator it = first; it != last; ++it) {
		this->insert(*it);
	}
}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) 
	: _size(other._size), 
	root(other.root ? std::make_unique<TreeNode>(*(other.root)) : nullptr)
	{ }

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other) { // TODO
	
	if (this != &other) {
		root.reset(other.root ? std::make_unique<TreeNode>(*(other.root)) : nullptr);
		this->_size = other._size;
	}
	return *this;
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
size_t BinaryTree<T>::height() const {
	size_t treeHeight = 0;

	if (this->root != nullptr) {

		// non-recursive depth first traversal
		std::pair<TreeNode*, size_t> nodePair(this->root.get(), 0);
		std::stack<std::pair<TreeNode*, size_t> > nodeStack;
		nodeStack.push(nodePair);

		while (!nodeStack.empty()) {
			nodePair = nodeStack.top();
			nodeStack.pop();

			if (nodePair.first->rightChild != nullptr) {
				nodeStack.push(std::pair<TreeNode*, size_t>(nodePair.first->rightChild.get(), nodePair.second + 1));
			}
			if (nodePair.first->leftChild != nullptr) {
				nodeStack.push(std::pair<TreeNode*, size_t>(nodePair.first->leftChild.get(), nodePair.second + 1));
			}
			if (nodePair.second > treeHeight) {
				treeHeight = nodePair.second;
			}
		}
	}
	return treeHeight;
}

template<class T>
size_t BinaryTree<T>::subtree_size(const_iterator position) const {

	TreeNode* positionPtr = position.get_iter();
	if (positionPtr == nullptr) {
		return 0;
	}
	else {
		return position.get_iter()->subtree_size();
	}
}

template<class T>
size_t BinaryTree<T>::subtree_size(const value_type& value) const {
	
	const_iterator it = this->find(value);
	if (it == this->end()) {
		return 0;
	}
	else {
		return this->subtree_size(it);
	}
}

template<class T>
T BinaryTree<T>::get_root() const {
	if (this->root != nullptr) {
		return *(this->begin());
	}
	else {
		return NULL;
	}
	
}

template<class T>
template <class... Args> // emplace (create and insert) value into tree (to leftmost location)
typename BinaryTree<T>::iterator BinaryTree<T>::emplace(Args&& ...args) {
	
	if (this->root == nullptr) {
		this->root = std::make_unique<TreeNode>(value_type(std::forward<Args>(args)...), nullptr);
		++(this->_size);
		return iterator(this->root, this->root);
	}
	else {

		TreeNode* parentNode = this->root.get()->leftmostChild();
		parentNode->leftChild = std::make_unique<TreeNode>(value_type(std::forward<Args>(args)...), parentNode);
		++(this->_size);
		return iterator(parentNode->leftChild, this->root);
	}
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool> 
			BinaryTree<T>::emplace_child(const_iterator parentPosition, Args&& ...args) {

	return this->emplace_child_left(parentPosition, std::forward<Args>(args)...);
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool> 
			BinaryTree<T>::emplace_child(const value_type& parentValue, Args&& ...args) {

	return this->emplace_child_left(parentValue, std::forward<Args>(args)...);
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool>
			BinaryTree<T>::emplace_child_left(const_iterator parentPosition, Args&& ...args) {
	
	if (parentPosition == this->end()) {
		// if end == begin, root must be nullptr, so we insert new root
		if (parentPosition == this->begin()) {
			iterator newRootNodeIt = this->emplace(std::forward<Args>(args)...);
			return std::pair<iterator, bool>(newRootNodeIt, true);
		}
		else {
			return std::pair<iterator, bool>(this->end(), false);
		}
	}
	else {
		TreeNode* parentNode = parentPosition.get_iter();
		bool insertionWorked;
		iterator returnedIt; // if insertion worked, parent, else added child iterator
		
		if (parentNode->leftChild == nullptr) {
			parentNode->leftChild = std::make_unique<TreeNode>(value_type(std::forward<Args>(args)...), parentNode);
			++(this->_size);
			insertionWorked = true;
			returnedIt = iterator(parentNode->leftChild, this->root);
		}
		else if (parentNode->rightChild == nullptr) {
			parentNode->rightChild = std::make_unique<TreeNode>(value_type(std::forward<Args>(args)...), parentNode);
			++(this->_size);
			insertionWorked = true;
			returnedIt = iterator(parentNode->rightChild, this->root);
		}
		else {
			// if parent already has 2 children
			insertionWorked = false;
			returnedIt = iterator(parentNode, this->root);
		}
		
		return std::pair<iterator, bool>(returnedIt, insertionWorked);
	}
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool> 
			BinaryTree<T>::emplace_child_left(const value_type& parentValue, Args&& ...args) {
	
	iterator parentNodeIt = this->find(parentValue);
	if (parentNodeIt == this->end()) {
		return std::pair<iterator, bool>(this->end(), false);
	}
	else {
		return this->emplace_child_left(parentNodeIt, std::forward<Args>(args)...);
	}
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool>
			BinaryTree<T>::emplace_child_right(const_iterator parentPosition, Args&& ...args) {

	if (parentPosition == this->end()) {
		// if end == begin, root must be nullptr, so we insert new root
		if (parentPosition == this->begin()) {
			iterator newRootNodeIt = this->emplace(std::forward<Args>(args)...);
			return std::pair<iterator, bool>(newRootNodeIt, true);
		}
		else {
			return std::pair<iterator, bool>(this->end(), false);
		}
	}
	else {
		TreeNode* parentNode = parentPosition.get_iter();
		bool insertionWorked;
		iterator returnedIt; // if insertion worked, parent, else added child iterator
		
		if (parentNode->rightChild == nullptr) {
			parentNode->rightChild = std::make_unique<TreeNode>(value_type(std::forward<Args>(args)...), parentNode);
			++(this->_size);
			insertionWorked = true;
			returnedIt = iterator(parentNode->rightChild, this->root);
		}
		else if (parentNode->leftChild == nullptr) {
			parentNode->leftChild = std::make_unique<TreeNode>(value_type(std::forward<Args>(args)...), parentNode);
			++(this->_size);
			insertionWorked = true;
			returnedIt = iterator(parentNode->leftChild, this->root);
		}
		else {
			// if parent already has 2 children
			insertionWorked = false;
			returnedIt = iterator(parentNode, this->root);
		}
		
		return std::pair<iterator, bool>(returnedIt, insertionWorked);
	}
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool> 
			BinaryTree<T>::emplace_child_right(const value_type& parentValue, Args&& ...args) {

	iterator parentNodeIt = this->find(parentValue);
	if (parentNodeIt == this->end()) {
		return std::pair<iterator, bool>(this->end(), false);
	}
	else {
		return this->emplace_child_right(parentNodeIt, std::forward<Args>(args)...);
	}
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool> 
			BinaryTree<T>::emplace_at(const_iterator position, Args&& ...args) {

	return this->emplace_at_left(position, std::forward<Args>(args)...);
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool> 
			BinaryTree<T>::emplace_at(const value_type& originalValue, Args&& ...args) {

	return this->emplace_at_left(originalValue, std::forward<Args>(args)...);
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool> 
			BinaryTree<T>::emplace_at_left(const_iterator position, Args&& ...args) {

	if (position == this->end()) {
		// if end == begin, root must be nullptr, so we insert new root
		if (position == this->begin()) {
			iterator newRootNodeIt = this->emplace(std::forward<Args>(args)...);
			return std::pair<iterator, bool>(newRootNodeIt, true)
		}
		else {
			return std::pair<iterator, bool>(this->end(), false);
		}
	}
	else { // main idea: make new unique_ptr<TreeNode>, change parents, and swap children around
		TreeNode* originalNode = position.get_iter();
		TreeNode* parentNode = originalNode->parent;

		// make newNode, set its parent to parentnode
		auto newNodePointer = std::make_unique<TreeNode>(value_type(std::forward<Args>(args)...), parentNode);

		// set originalNode's parent into newNode
		originalNode->parent = newNodePointer.get();

		// if parentNode == nullptr, we should be inserting to root position
		if (parentNode == nullptr) {
			// child relationships: tree->root=o, n->child=null, (local=n)
			using std::swap;
			swap(newNodePointer->leftChild, this->root);
			// child relationships: tree->root=null, n->child=o, (local=n)
			swap(newNodePointer, this->root);
			// child relationships: tree->root=n, n->child=o, (local=null) GOOD

			++(this->_size);
			return std::pair<iterator, bool>(this->begin(), true);
		}
		else {
			bool isLeftChild = (parentNode->leftChild.get() == originalNode);

			// child relationships: p->child=o, n->child=null, (local=n)
			using std::swap;
			swap(newNodePointer->leftChild, (isLeftChild ? parentNode->leftChild : parentNode->rightChild));
			// child relationships: p->child=null, n->child=o, (local=n)
			swap(newNodePointer, (isLeftChild ? parentNode->leftChild : parentNode->rightChild));
			// child relationships: p->child=n, n->child=o, (local=null) GOOD

			++(this->_size);
			return std::pair<iterator, bool>(iterator((isLeftChild ? parentNode->leftChild : parentNode->rightChild), this->root), true);
		}
	}
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool>
			BinaryTree<T>::emplace_at_left(const value_type& originalValue, Args&& ...args) {

	iterator originalNodeIt = this->find(originalValue);
	if (originalNodeIt == this->end()) {
		return std::pair<iterator, bool>(this->end(), false);
	}
	else {
		return this->emplace_at_left(originalNodeIt, std::forward<Args>(args)...);
	}
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool>
			BinaryTree<T>::emplace_at_right(const_iterator position, Args&& ...args) {

	if (position == this->end()) {
		// if end == begin, root must be nullptr, so we insert new root
		if (position == this->begin()) {
			iterator newRootNodeIt = this->emplace(std::forward<Args>(args)...);
			return std::pair<iterator, bool>(newRootNodeIt, true)
		}
		else {
			return std::pair<iterator, bool>(this->end(), false);
		}
	}
	else { // main idea: make new unique_ptr<TreeNode>, change parents, and swap children around
		TreeNode* originalNode = position.get_iter();
		TreeNode* parentNode = originalNode->parent;

		// make newNode, set its parent to parentnode
		auto newNodePointer = std::make_unique<TreeNode>(value_type(std::forward<Args>(args)...), parentNode);

		// set originalNode's parent into newNode
		originalNode->parent = newNodePointer.get();

		// if parentNode == nullptr, we should be inserting to root position
		if (parentNode == nullptr) {
			// child relationships: tree->root=o, n->child=null, (local=n)
			using std::swap;
			swap(newNodePointer->rightChild, this->root);
			// child relationships: tree->root=null, n->child=o, (local=n)
			swap(newNodePointer, this->root);
			// child relationships: tree->root=n, n->child=o, (local=null) GOOD

			++(this->_size);
			return std::pair<iterator, bool>(this->begin(), true);
		}
		else {
			bool isLeftChild = (parentNode->leftChild.get() == originalNode);

			// child relationships: p->child=o, n->child=null, (local=n)
			using std::swap;
			swap(newNodePointer->rightChild, (isLeftChild ? parentNode->leftChild : parentNode->rightChild));
			// child relationships: p->child=null, n->child=o, (local=n)
			swap(newNodePointer, (isLeftChild ? parentNode->leftChild : parentNode->rightChild));
			// child relationships: p->child=n, n->child=o, (local=null) GOOD

			++(this->_size);
			return std::pair<iterator, bool>(iterator((isLeftChild ? parentNode->leftChild : parentNode->rightChild), this->root), true);
		}
	}
}

template<class T>
template<class ...Args>
std::pair<typename BinaryTree<T>::iterator, bool>
			BinaryTree<T>::emplace_at_right(const value_type& originalValue, Args&& ...args) {

	iterator originalNodeIt = this->find(originalValue);
	if (originalNodeIt == this->end()) {
		return std::pair<iterator, bool>(this->end(), false);
	}
	else {
		return this->emplace_at_right(originalNodeIt, std::forward<Args>(args)...);
	}
}

template<class T>
template<class InputIterator>
void BinaryTree<T>::insert(InputIterator first, InputIterator last) {

	for (InputIterator it = first; it != last; ++it) {
		this->insert(*it);
	}
}

template<class T>
typename BinaryTree<T>::iterator BinaryTree<T>::insert(value_type value) {
	return this->emplace(std::move(value));
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool>
			BinaryTree<T>::insert_child(const_iterator parentPosition, value_type value) {
	
	return this->emplace_child(parentPosition, std::move(value))
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool>
			BinaryTree<T>::insert_child(const value_type& parentValue, value_type value) {

	return this->emplace_child(parentValue, std::move(value));
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool> BinaryTree<T>::insert_child_left(const_iterator parentPosition, value_type value) {

	return this->emplace_child_left(parentPosition, std::move(value))
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool> BinaryTree<T>::insert_child_left(const value_type& parentValue, value_type value) {

	return this->emplace_child_left(parentValue, std::move(value));
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool> BinaryTree<T>::insert_child_right(const_iterator parentPosition, value_type value) {

	return this->emplace_child_right(parentPosition, std::move(value))
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool> BinaryTree<T>::insert_child_right(const value_type& parentValue, value_type value) {

	return this->emplace_child_right(parentValue, std::move(value));
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool> 
			BinaryTree<T>::insert_at(const_iterator position, value_type value) {
	
	return this->emplace_at(position, std::move(value));
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool> 
			BinaryTree<T>::insert_at(const value_type& originalValue, value_type value) {

	return this->emplace_at(originalValue, std::move(value));
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool>
BinaryTree<T>::insert_at_left(const_iterator position, value_type value) {

	return this->emplace_at_left(position, std::move(value));
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool>
BinaryTree<T>::insert_at_left(const value_type& originalValue, value_type value) {

	return this->emplace_at_left(originalValue, std::move(value));
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool>
BinaryTree<T>::insert_at_right(const_iterator position, value_type value) {

	return this->emplace_at_right(position, std::move(value));
}

template<class T>
std::pair<typename BinaryTree<T>::iterator, bool>
BinaryTree<T>::insert_at_right(const value_type& originalValue, value_type value) {

	return this->emplace_at_right(originalValue, std::move(value));
}

template<class T>
size_t BinaryTree<T>::erase(const_iterator position) {
	size_t numOfnodes = subtree_size(position);
	if (numOfnodes != 0) {
		TreeNode* nodeToErase = position.get_iter();
		TreeNode* parentNode = nodeToErase->parent;
		if (parentNode == nullptr) {
			// should be root node
			this->clear();
		}
		else {
			if (parentNode->leftChild.get() == nodeToErase) {
				parentNode->leftChild.reset();
			}
			else {
				parentNode->rightChild.reset();
			}
			this->_size -= numOfnodes;
		}
	}
	return numOfnodes;
}

template<class T>
size_t BinaryTree<T>::erase(const value_type& value) {
	
	iterator nodeToEraseIt = this->find(value);
	if (nodeToEraseIt == this->end()) {
		return 0;
	}
	else {
		return this->erase(nodeToEraseIt);
	}
}

template<class T>
void BinaryTree<T>::swap(BinaryTree<T>& second) {

	using std::swap;

	swap(this->root, second.root);
	swap(this->_size, second._size);
}

template<class T>
void BinaryTree<T>::clear() {
	
	this->root.reset();
	this->_size = 0;
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
	using std::equal;
	return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
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
void printTree(std::ostream& os, BinaryTree<T>& tree) {

	printTree<T>(os, tree.cbegin());
}