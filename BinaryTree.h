#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <memory>



template <class T>
class BinaryTree {

	template <class IterType>
	class TreeIterator;

public:
	// type definitions:
	using value_type = T;
	using iterator = TreeIterator<value_type>;
	using const_iterator = TreeIterator<const value_type>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;


private:

	// tree node definition;
	class TreeNode {
	private:
		value_type data;

	public:
		TreeNode* parent;
		std::unique_ptr<TreeNode> leftChild = nullptr;
		std::unique_ptr<TreeNode> rightChild = nullptr;

		TreeNode(const value_type& value, TreeNode* const parent);

		value_type& access_value() { return this->data; }

		TreeNode* leftmostChild();
		TreeNode* rightmostChildLeaf();
	};

	std::unique_ptr<TreeNode> root = nullptr;
	size_t _size = 0;

	template <class IterType>
	class TreeIterator {

	public:
		// iterator traits:
		using difference_type = std::ptrdiff_t;
		using value_type = IterType;
		using pointer = value_type*;
		using reference = value_type&;
		using iterator_category = std::bidirectional_iterator_tag;
		using node_pointer = TreeNode*;


	private:

		node_pointer root_iter;
		node_pointer iter;

	public:

		// iterator constructors:
		TreeIterator() : iter(node_pointer()), root_iter(node_pointer()) { }
		explicit TreeIterator(const std::unique_ptr<TreeNode>& i, const std::unique_ptr<TreeNode>& root_i) 
								: iter(i.get()), root_iter(root_i.get()) { }
		TreeIterator(const TreeIterator& other) : iter(other.iter), root_iter(other.root_iter) { }

		// iterator access:
		node_pointer get_iter() const { return this->iter; }

		// iterator operator overloads:
		TreeIterator& operator=(const TreeIterator& other) {
			this->iter = other.iter;
			return *this;
		}
		reference operator*() const { return iter->access_value(); }
		pointer operator->() const { return &(operator*()); }

		TreeIterator& operator++() {
			if (this->iter == nullptr) {
				// For debuggin purposes. Remove later! TODO
				std::cerr << "Error: Trying to increment iterator holding nullptr\n";
			} // depth-and-left first traversal of iterator
			else { // go left if possible
				if (this->iter->leftChild != nullptr) {
					this->iter = this->iter->leftChild.get();
				} // go right if possible
				else if (this->iter->rightChild != nullptr) {
					this->iter = this->iter->rightChild.get();
				} // go up the tree if possible
				else if (this->iter->parent != nullptr) {
					// loop to find the first right child to proceed with (or alternatively to return nullptr iterator)
					bool prevIsLeftChild = (this->iter == this->iter->parent->leftChild.get());
					for (node_pointer nodePtr = this->iter->parent; nodePtr != nullptr; nodePtr = nodePtr->parent) {
						if (prevIsLeftChild && nodePtr->rightChild.get() != nullptr) {
							this->iter = nodePtr->rightChild.get();
							break;
						}
						else {
							if (nodePtr->parent == nullptr) {
								this->iter = nullptr;
								break;
							}
							else {
								prevIsLeftChild = (nodePtr == nodePtr->parent->leftChild.get());
							}
						}
					}
				}
				else { // return nullptr iterator if no options to move
					this->iter = nullptr;
				}
			}
			return *this;
		}
		TreeIterator operator++(int) {
			TreeIterator copy(*this);
			operator++();
			return copy;
		}

		TreeIterator& operator--() {
			if (this->iter == nullptr) {
				// if we have nullptr iterator, we go to the rightmost child leaf of the tree
				this->iter = this->root_iter->rightmostChildLeaf();
			} // complement of depth-and-left first traversal of iterator
			else {
				node_pointer parentNode = this->iter->parent;
				// if node does not have a parent, should be root
				if (parentNode == nullptr) {
					this->iter = nullptr;
				} // else proceed with left siblings subtree if possible
				else if (parentNode->leftChild != nullptr && parentNode->leftChild.get() != this->iter) {
					this->iter = parentNode->leftChild->rightmostChildLeaf();
				} // else go to parent node
				else {
					this->iter = parentNode;
				}
			}
			return *this;
		}
		TreeIterator operator--(int) {
			TreeIterator copy(*this);
			operator--();
			return copy;
			;
		}

		// iterator comparison operators:
		friend bool operator==(const TreeIterator& lhs, const TreeIterator& rhs) {
			return (lhs.iter == rhs.iter);
		}
		friend bool operator!=(const TreeIterator& lhs, const TreeIterator& rhs) {
			return !operator==(lhs, rhs);
		}
	};


	//---------------------------------------------------------------------------------------------------------

public:

	// constructors:
	//explicit BinaryTree(const Compare& comp = Compare()); // default constructor (custom compare)
	explicit BinaryTree() { } // default constructor
	template <class InputIterator>
	BinaryTree(InputIterator first, InputIterator last); // iterator constructor
	BinaryTree(const BinaryTree&); // copy constructor
	BinaryTree(BinaryTree&&); // move constructor
	//BinaryTree(initializer_list<value_type>, const Compare & = Compare()); // initializer_list constructor


	// destructor:
	~BinaryTree();


	// assignment operators:
	BinaryTree& operator=(const BinaryTree& other); // copy assignment
	BinaryTree& operator=(BinaryTree&& x); // move assignment
	//BinaryTree& operator=(initializer_list<value_type>); // initializer_list assignment


	// iterators:
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	const_iterator cbegin();
	const_iterator cend();
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;


	// capacity:
	bool empty() const; // to check if tree is empty
	size_t size() const; // return number of elements in the tree
	size_t height() const; // return the height of the tree


	// root access:
	TreeNode* get_root() const; // to access root of the tree


	// emplacement:
	template <class...	 Args>
	std::pair<iterator, bool> emplace(Args&& ... args); // construct and insert an element
	template <class... Args>
	iterator emplace_at(const_iterator position, Args&& ... args); // construct and insert an element in a specified location

	// insertion:
	iterator insert(const value_type& value); // insert value into tree (to leftmost location)
	// insert value into tree in a specified location (parent)
	std::pair<iterator, bool> insert_at(const value_type& value, const value_type& parentValue, const bool tryToInsertLeftFirst = true);
	iterator insert_at(const_iterator position, const value_type& x); // insert value into tree in a specified location (iterator)
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last); // iterator insertion
	//void insert(initializer_list<value_type>); // initializer_list insertion

	// erasure:
	iterator erase(const_iterator position); // erase iterator location (and subtree?)
	size_t erase(const value_type& x); // erase value location (and subtree?)
	iterator erase(const_iterator first, const_iterator last); // erase between iterators
	void swap(BinaryTree& second); // swap this tree with second tree
	void clear(); // clear tree


	// operations:
	iterator find(const value_type& value); // to find the first occurrence of value using iterator (return this->end() if no luck)
	const_iterator find(const value_type& value) const; // const version of find
	size_t count(const value_type& value) const; // to check number of specific elements in tree
	bool has(const value_type& value); // check if element in tree (using this->find())

};


// comparison operator overloads:
template <class T>
bool operator==(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs);

template <class T>
bool operator!=(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs);

template <class T>
bool operator<(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs);

template <class T>
bool operator<=(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs);

template <class T>
bool operator>(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs);

template <class T>
bool operator>=(const BinaryTree<T>& lhs, const BinaryTree<T>& rhs);


// swap overload:
template <class T>
void swap(BinaryTree<T>& lhs, BinaryTree<T>& rhs);


// outputstream overload:
template <class T>
std::ostream& operator<<(std::ostream& os, const BinaryTree<T>& tree);


#include "BinaryTree.tpp"

#endif