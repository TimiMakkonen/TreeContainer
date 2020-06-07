#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>


namespace tree_container {

	template <class T>
	class binary_tree {

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
			// node data:
			value_type data;

			TreeNode(const TreeNode& other, TreeNode* const parent);

		public:
			// node variables:
			TreeNode* parent = nullptr;
			std::unique_ptr<TreeNode> leftChild = nullptr;
			std::unique_ptr<TreeNode> rightChild = nullptr;

			// node constructos:
			TreeNode() = default;
			TreeNode(value_type value, TreeNode* const parent);
			TreeNode(const TreeNode& other);
			TreeNode(TreeNode&&) = default;

			value_type& access_value() { return this->data; }

			TreeNode* leftmostChild(); // to find leftmostChild
			TreeNode* rightmostChildLeaf(); // to find rightmostChildLeaf
			size_t subtree_size(); // return number of elements in the subtree (this node included)
		};

		// class variables:
		std::unique_ptr<TreeNode> root = nullptr;
		size_t _size = 0;

		// NOTE: iterator might not behave well after insertion/erasure (especially change of root)
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
			TreeIterator() = default;
			explicit TreeIterator(const std::unique_ptr<TreeNode>& i, const std::unique_ptr<TreeNode>& root_i) 
									: iter(i.get()), root_iter(root_i.get()) { }
			TreeIterator(const TreeIterator& other) 
					: iter(other.iter), root_iter(other.root_iter) { }
			TreeIterator(node_pointer i, node_pointer root_i)
				: iter(i), root_iter(root_i) { }
			TreeIterator(node_pointer i, const std::unique_ptr<TreeNode>& root_i)
				: iter(i), root_iter(root_i.get()) { }

			// conversion to const iterator
			operator TreeIterator<const value_type>() { return TreeIterator<const value_type>(iter, root_iter); }

			// iterator access:
			node_pointer get_iter() const { return this->iter; }

			// iterator operator overloads:
			TreeIterator& operator=(const TreeIterator& other) {
				this->iter = other.iter;
				this->root_iter = other.root_iter;
				return *this;
			}
			reference operator*() const { return iter->access_value(); }
			pointer operator->() const { return &(operator*()); }

			TreeIterator& operator++() {
				if (this->iter == nullptr) { // if for some reason null, increment to root
					this->iter = this->root_iter;
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
				return (lhs.iter == rhs.iter && lhs.root_iter == rhs.root_iter);
			}
			friend bool operator!=(const TreeIterator& lhs, const TreeIterator& rhs) {
				return !operator==(lhs, rhs);
			}
		};


		//---------------------------------------------------------------------------------------------------------

	public:

		// constructors:
		binary_tree() = default; // default constructor
		template <class InputIterator>
		binary_tree(InputIterator first, InputIterator last); // iterator constructor (basic list style)
		binary_tree(const binary_tree& other); // copy constructor
		binary_tree(binary_tree&&) = default; // move constructor
		//binary_tree(initializer_list<value_type>); // initializer_list constructor


		// destructor:
		~binary_tree() = default;


		// assignment operators:
		binary_tree& operator=(const binary_tree& other); // copy assignment
		binary_tree& operator=(binary_tree&& x) = default; // move assignment
		//binary_tree& operator=(initializer_list<value_type>); // initializer_list assignment


		// iterators:
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		const_iterator cbegin() const;
		const_iterator cend() const;
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;


		// capacity/measurements:
		bool empty() const; // to check if tree is empty
		size_t size() const; // return number of elements in the tree
		size_t height() const; // return the height of the tree TODO
		size_t subtree_size(const_iterator position) const; // return size of the subtree (position node included)
		size_t subtree_size(const value_type& value) const;


		// root value access:
		value_type get_root() const; // to access value at the root of the tree



		// emplacement:
		template <class...	 Args>
		iterator emplace(Args&& ... args); // emplace value into tree (to leftmost location)

		// emplace value into tree as a child of specified parent
		// (Try specified child position first. Left is default, try the other if not possible.)
		template <class... Args>
		std::pair<iterator, bool> emplace_child(const_iterator parentPosition, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_child(const value_type& parentValue, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_child_left(const_iterator parentPosition, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_child_left(const value_type& parentValue, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_child_right(const_iterator parentPosition, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_child_right(const value_type& parentValue, Args&& ... args);	

		// emplace value into tree at specific location (replace location node and make it its child)
		// (Try to insert original node into specified child position first. Left is default, try the other if not possible.)
		template <class... Args>
		std::pair<iterator, bool> emplace_at(const_iterator position, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_at(const value_type& originalValue, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_at_left(const_iterator position, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_at_left(const value_type& originalValue, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_at_right(const_iterator position, Args&& ... args);
		template <class... Args>
		std::pair<iterator, bool> emplace_at_right(const value_type& originalValue, Args&& ... args);



		// insertion:
		iterator insert(value_type value); // insert value into tree (to leftmost location)

		// insert value into tree as a child of specified parent
		std::pair<iterator, bool> insert_child(const_iterator parentPosition, value_type value);
		std::pair<iterator, bool> insert_child(const value_type& parentValue, value_type value);
		std::pair<iterator, bool> insert_child_left(const_iterator parentPosition, value_type value);
		std::pair<iterator, bool> insert_child_left(const value_type& parentValue, value_type value);
		std::pair<iterator, bool> insert_child_right(const_iterator parentPosition, value_type value);
		std::pair<iterator, bool> insert_child_right(const value_type& parentValue, value_type value);

		// insert value into tree at specific location (replace location node and make it its child)
		std::pair<iterator, bool> insert_at(const_iterator position, value_type value);
		std::pair<iterator, bool> insert_at(const value_type & originalValue, value_type value);
		std::pair<iterator, bool> insert_at_left(const_iterator position, value_type value);
		std::pair<iterator, bool> insert_at_left(const value_type & originalValue, value_type value);
		std::pair<iterator, bool> insert_at_right(const_iterator position, value_type value);
		std::pair<iterator, bool> insert_at_right(const value_type & originalValue, value_type value);

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last); // iterator insertion TODO: change to smarter insert?
		//void insert(initializer_list<value_type>); // initializer_list insertion



		// erasure:
		//Note: Stack overflow is unlikely to be a problem with trees. Problems may arise if tree extremely unbalanced, ie. similar to plain list.
		size_t erase(const_iterator position); // erase iterator location and subtree
		size_t erase(const value_type& value); // erase value location and subtree
		void swap(binary_tree& second); // swap this tree with second tree
		void clear(); // clear tree


		// operations:
		iterator find(const value_type& value); // to find the first occurrence of value using iterator (return this->end() if no luck)
		const_iterator find(const value_type& value) const; // const version of find
		size_t count(const value_type& value) const; // to check number of specific elements in tree
		bool has(const value_type& value); // check if element in tree (using this->find())


		// friends:
		template <class T>
		friend void printTree(std::ostream& os, typename binary_tree<T>::const_iterator tree_cit);

	};


	// comparison operator overloads:
	template <class T>
	bool operator==(const binary_tree<T>& lhs, const binary_tree<T>& rhs);

	template <class T>
	bool operator!=(const binary_tree<T>& lhs, const binary_tree<T>& rhs);

	template <class T>
	bool operator<(const binary_tree<T>& lhs, const binary_tree<T>& rhs);

	template <class T>
	bool operator<=(const binary_tree<T>& lhs, const binary_tree<T>& rhs);

	template <class T>
	bool operator>(const binary_tree<T>& lhs, const binary_tree<T>& rhs);

	template <class T>
	bool operator>=(const binary_tree<T>& lhs, const binary_tree<T>& rhs);


	// swap overload:
	template <class T>
	void swap(binary_tree<T>& lhs, binary_tree<T>& rhs);




	template <class T>
	void printTree(std::ostream& os, typename binary_tree<T>::const_iterator tree_cit);

	template <class T>
	void printTree(std::ostream& os, binary_tree<T>& tree);


} // namespace tree_container

#include "binary_tree.tpp"

#endif // BINARY_TREE_H