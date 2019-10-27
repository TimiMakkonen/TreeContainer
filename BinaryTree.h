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
		std::pair<TreeNode*, size_t> rightmostChildLeaf();
	};

	std::unique_ptr<TreeNode> root = nullptr;
	size_t _size = 0;

	template <class IterType> // FIXME: dist_below_init_iter still included (to be removed)
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
		size_t dist_below_init_iter;

	public:

		// iterator constructors:
		TreeIterator() : iter(node_pointer()), root_iter(node_pointer()), dist_below_init_iter(size_t()) { }
		explicit TreeIterator(const std::unique_ptr<TreeNode>& i, const std::unique_ptr<TreeNode>& root_i) 
								: iter(i.get()), root_iter(root_i.get()), dist_below_init_iter(size_t()) { }
		TreeIterator(const TreeIterator& other) 
				: iter(other.iter), root_iter(other.root_iter), dist_below_init_iter(other.dist_below_init_iter) { }
		TreeIterator(const node_pointer& i, const node_pointer& root_i, const size_t dist_i)
			: iter(i), root_iter(root_i), dist_below_init_iter(dist_i) { }

		// conversion to const iterator
		operator TreeIterator<const value_type>() { return TreeIterator<const value_type>(iter, root_iter, dist_below_init_iter); }

		// iterator access:
		node_pointer get_iter() const { return this->iter; }
		// how many nodes below initial iterator (positive if below, negative if above)
		size_t dist_below() const { return this->dist_below_init_iter; }

		// iterator operator overloads:
		TreeIterator& operator=(const TreeIterator& other) {
			this->iter = other.iter;
			this->root_iter = other.root_iter;
			this->dist_below_init_iter = other.dist_below_init_iter;
			return *this;
		}
		reference operator*() const { return iter->access_value(); }
		pointer operator->() const { return &(operator*()); }

		TreeIterator& operator++() {
			size_t distTravelled = 0; // distance below(pos) or above(neg) between current and next node
			if (this->iter == nullptr) { // if for some reason null, increment to root
				this->iter = this->root_iter;
			} // depth-and-left first traversal of iterator
			else { // go left if possible
				if (this->iter->leftChild != nullptr) {
					this->iter = this->iter->leftChild.get();
					++distTravelled;

				} // go right if possible
				else if (this->iter->rightChild != nullptr) {
					this->iter = this->iter->rightChild.get();
					++distTravelled;

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
								--distTravelled;
							}
						}
					}
				}
				else { // return nullptr iterator if no options to move
					this->iter = nullptr;
				}
			}
			this->dist_below_init_iter += distTravelled;
			return *this;
		}
		TreeIterator operator++(int) {
			TreeIterator copy(*this);
			operator++();
			return copy;
		}

		TreeIterator& operator--() {
			size_t distTravelled = 0; // distance below(pos) or above(neg) between current and next node
			if (this->iter == nullptr) {
				// if we have nullptr iterator, we go to the rightmost child leaf of the tree
				std::pair<TreeNode*, size_t> prevNodePair = this->root_iter->rightmostChildLeaf();
				this->iter = prevNodePair.first;
				distTravelled += prevNodePair.second;
			} // complement of depth-and-left first traversal of iterator
			else {
				node_pointer parentNode = this->iter->parent;
				// if node does not have a parent, should be root
				if (parentNode == nullptr) {
					this->iter = nullptr;
				} // else proceed with left siblings subtree if possible
				else if (parentNode->leftChild != nullptr && parentNode->leftChild.get() != this->iter) {
					std::pair<TreeNode*, size_t> prevNodePair = parentNode->leftChild->rightmostChildLeaf();
					this->iter = prevNodePair.first;
					distTravelled += prevNodePair.second;
				} // else go to parent node
				else {
					this->iter = parentNode;
					--distTravelled;
				}
			}
			this->dist_below_init_iter += distTravelled;
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
	BinaryTree(InputIterator first, InputIterator last); // iterator constructor TODO
	BinaryTree(const BinaryTree&); // copy constructor TODO
	BinaryTree(BinaryTree&&); // move constructor TODO
	//BinaryTree(initializer_list<value_type>, const Compare & = Compare()); // initializer_list constructor


	// destructor:
	~BinaryTree();


	// assignment operators:
	BinaryTree& operator=(const BinaryTree& other); // copy assignment TODO
	BinaryTree& operator=(BinaryTree&& x); // move assignment TODO
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
	size_t height() const; // return the height of the tree TODO


	// root access:
	TreeNode* get_root() const; // to access root of the tree


	// emplacement:
	template <class...	 Args>
	std::pair<iterator, bool> emplace(Args&& ... args); // construct and insert an element TODO
	template <class... Args>
	iterator emplace_at(const_iterator position, Args&& ... args); // construct and insert an element in a specified location TODO

	// insertion:
	iterator insert(const value_type& value); // insert value into tree (to leftmost location)
	// insert value into tree in a specified location (parent)
	std::pair<iterator, bool> insert_at(const value_type& value, const value_type& parentValue, const bool tryToInsertLeftFirst = true);
	iterator insert_at(const_iterator position, const value_type& x); // insert value into tree in a specified location (iterator) TODO
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last); // iterator insertion TODO
	//void insert(initializer_list<value_type>); // initializer_list insertion

	// erasure:
	iterator erase(const_iterator position); // erase iterator location (and subtree?) TODO
	size_t erase(const value_type& x); // erase value location (and subtree?) TODO
	iterator erase(const_iterator first, const_iterator last); // erase between iterators TODO
	void swap(BinaryTree& second); // swap this tree with second tree TODO
	void clear(); // clear tree TODO


	// operations:
	iterator find(const value_type& value); // to find the first occurrence of value using iterator (return this->end() if no luck)
	const_iterator find(const value_type& value) const; // const version of find
	size_t count(const value_type& value) const; // to check number of specific elements in tree
	bool has(const value_type& value); // check if element in tree (using this->find())


	// friends:
	template <class T>
	friend void printTree(std::ostream& os, typename BinaryTree<T>::const_iterator tree_cit); // TODO

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




template <class T>
void printTree(std::ostream& os, typename BinaryTree<T>::const_iterator tree_cit); // TODO

template <class T>
void printTree(std::ostream& os, BinaryTree<T>& tree); // TODO



#include "BinaryTree.tpp"

#endif