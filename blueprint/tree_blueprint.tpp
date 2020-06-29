#ifndef TREE_CONTAINER_TREE_BLUEPRINT_H
#error __FILE__ should only be included from tree_blueprint.h
#endif

#include <tree-container/tree_blueprint.h>


namespace tree_container {

	template<class T>
	typename tree_blueprint<T>::iterator tree_blueprint<T>::begin() {
		return tree_blueprint<T>::iterator(this->root, this->root);
	}

	template<class T>
	typename tree_blueprint<T>::const_iterator tree_blueprint<T>::begin() const {
		return tree_blueprint<T>::const_iterator(this->root, this->root);
	}

	template<class T>
	typename tree_blueprint<T>::iterator tree_blueprint<T>::end() {
		return tree_blueprint<T>::iterator(nullptr, this->root);
	}

	template<class T>
	typename tree_blueprint<T>::const_iterator tree_blueprint<T>::end() const {
		return tree_blueprint<T>::const_iterator(nullptr, this->root);
	}

	template<class T>
	typename tree_blueprint<T>::reverse_iterator tree_blueprint<T>::rbegin() {
		return tree_blueprint<T>::reverse_iterator(this->end());
	}

	template<class T>
	typename tree_blueprint<T>::const_reverse_iterator tree_blueprint<T>::rbegin() const {
		return tree_blueprint<T>::const_reverse_iterator(this->end());
	}

	template<class T>
	typename tree_blueprint<T>::reverse_iterator tree_blueprint<T>::rend() {
		return tree_blueprint<T>::reverse_iterator(this->begin());
	}

	template<class T>
	typename tree_blueprint<T>::const_reverse_iterator tree_blueprint<T>::rend() const {
		return tree_blueprint<T>::const_reverse_iterator(this->begin());
	}

	template<class T>
	typename tree_blueprint<T>::const_iterator tree_blueprint<T>::cbegin() {
		return tree_blueprint<T>::const_iterator(this->root, this->root);
	}

	template<class T>
	typename tree_blueprint<T>::const_iterator tree_blueprint<T>::cend() {
		return tree_blueprint<T>::const_iterator(nullptr, this->root);
	}

	template<class T>
	typename tree_blueprint<T>::const_reverse_iterator tree_blueprint<T>::crbegin() const {
		return tree_blueprint<T>::const_reverse_iterator(this->cend());
	}

	template<class T>
	typename tree_blueprint<T>::const_reverse_iterator tree_blueprint<T>::crend() const {
		return tree_blueprint<T>::const_reverse_iterator(this->cbegin());
	}

	template<class T>
	bool tree_blueprint<T>::empty() const {
		return (this->size() == 0);
	}

	template<class T>
	size_t tree_blueprint<T>::size() const {
		return this->_size;
	}

	template<class T>
	typename tree_blueprint<T>::TreeNode* tree_blueprint<T>::get_root() const {
		return this->root.get();
	}

	template<class T>
	void tree_blueprint<T>::swap(tree_blueprint<T>& second) {
		using std::swap;

		swap(this->root, second.root);
		swap(this->_size, second._size);
	}

	template<class T>
	typename tree_blueprint<T>::iterator tree_blueprint<T>::find(const value_type& value) {

		for (iterator it = this->begin(); it != this->end(); ++it) {
			if (*it == value) {
				return it;
			}
		}
		return this->end();
	}

	template<class T>
	typename tree_blueprint<T>::const_iterator tree_blueprint<T>::find(const value_type& value) const {

		for (const_iterator it = this->begin(); it != this->end(); ++it) {
			if (*it == value) {
				return it;
			}
		}
		return this->end();
	}

	template<class T>
	size_t tree_blueprint<T>::count(const value_type& value) const {

		size_t counter = 0;
		for (iterator it = this->begin(); it != this->end(); ++it) {
			if (it->get_value() == value) {
				++counter;
			}
		}
		return counter;
	}

	template<class T>
	bool tree_blueprint<T>::has(const value_type& value) {
		if (this->find(value) == this->end()) {
			return false;
		}
		else {
			return true;
		}
	}








	template<class T>
	bool operator==(const tree_blueprint<T>& lhs, const tree_blueprint<T>& rhs) {
		return (lhs->get_root() == rhs->get_root());
	}

	template<class T>
	bool operator!=(const tree_blueprint<T>& lhs, const tree_blueprint<T>& rhs) {
		return !operator==(lhs, rhs);
	}

	template<class T>
	bool operator<(const tree_blueprint<T>& lhs, const tree_blueprint<T>& rhs) {
		return (lhs->size() < rhs->size());
	}

	template<class T>
	bool operator<=(const tree_blueprint<T>& lhs, const tree_blueprint<T>& rhs) {
		return !operator>(lhs, rhs);
	}

	template<class T>
	bool operator>(const tree_blueprint<T>& lhs, const tree_blueprint<T>& rhs) {
		return (lhs->size() > rhs->size());
	}

	template<class T>
	bool operator>=(const tree_blueprint<T>& lhs, const tree_blueprint<T>& rhs) {
		return !operator<(lhs, rhs);
	}

	template<class T>
	void swap(tree_blueprint<T>& lhs, tree_blueprint<T>& rhs) {
		lhs.swap(rhs);
	}

} // namespace tree_container