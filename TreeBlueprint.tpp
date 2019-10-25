#ifndef TREEBLUEPRINT_H
#error __FILE__ should only be included from TreeBlueprint.h
#endif

#include "TreeBlueprint.h"



template<class T>
typename TreeBlueprint<T>::iterator TreeBlueprint<T>::begin() {
	return TreeBlueprint<T>::iterator(this->root, this->root);
}

template<class T>
typename TreeBlueprint<T>::const_iterator TreeBlueprint<T>::begin() const {
	return TreeBlueprint<T>::const_iterator(this->root, this->root);
}

template<class T>
typename TreeBlueprint<T>::iterator TreeBlueprint<T>::end() {
	return TreeBlueprint<T>::iterator(nullptr, this->root);
}

template<class T>
typename TreeBlueprint<T>::const_iterator TreeBlueprint<T>::end() const {
	return TreeBlueprint<T>::const_iterator(nullptr, this->root);
}

template<class T>
typename TreeBlueprint<T>::reverse_iterator TreeBlueprint<T>::rbegin() {
	return TreeBlueprint<T>::reverse_iterator(this->end());
}

template<class T>
typename TreeBlueprint<T>::const_reverse_iterator TreeBlueprint<T>::rbegin() const {
	return TreeBlueprint<T>::const_reverse_iterator(this->end());
}

template<class T>
typename TreeBlueprint<T>::reverse_iterator TreeBlueprint<T>::rend() {
	return TreeBlueprint<T>::reverse_iterator(this->begin());
}

template<class T>
typename TreeBlueprint<T>::const_reverse_iterator TreeBlueprint<T>::rend() const {
	return TreeBlueprint<T>::const_reverse_iterator(this->begin());
}

template<class T>
typename TreeBlueprint<T>::const_iterator TreeBlueprint<T>::cbegin() {
	return TreeBlueprint<T>::const_iterator(this->root, this->root);
}

template<class T>
typename TreeBlueprint<T>::const_iterator TreeBlueprint<T>::cend() {
	return TreeBlueprint<T>::const_iterator(nullptr, this->root);
}

template<class T>
typename TreeBlueprint<T>::const_reverse_iterator TreeBlueprint<T>::crbegin() const {
	return TreeBlueprint<T>::const_reverse_iterator(this->cend());
}

template<class T>
typename TreeBlueprint<T>::const_reverse_iterator TreeBlueprint<T>::crend() const {
	return TreeBlueprint<T>::const_reverse_iterator(this->cbegin());
}

template<class T>
bool TreeBlueprint<T>::empty() const {
	return (this->size() == 0);
}

template<class T>
size_t TreeBlueprint<T>::size() const {
	return this->_size;
}

template<class T>
typename TreeBlueprint<T>::TreeNode* TreeBlueprint<T>::get_root() const {
	return this->root.get();
}


template<class T>
typename TreeBlueprint<T>::iterator TreeBlueprint<T>::find(const value_type& value) {

	for (iterator it = this->begin(); it != this->end(); ++it) {
		if (*it == value) {
			return it;
		}
	}
	return this->end();
}

template<class T>
typename TreeBlueprint<T>::const_iterator TreeBlueprint<T>::find(const value_type& value) const {

	for (const_iterator it = this->begin(); it != this->end(); ++it) {
		if (*it == value) {
			return it;
		}
	}
	return this->end();
}

template<class T>
size_t TreeBlueprint<T>::count(const value_type& value) const {

	size_t counter = 0;
	for (iterator it = this->begin(); it != this->end(); ++it) {
		if (it->get_value() == value) {
			++counter;
		}
	}
	return counter;
}

template<class T>
bool TreeBlueprint<T>::has(const value_type& value) {
	if (this->find(value) == this->end()) {
		return false;
	}
	else {
		return true;
	}
}








template<class T>
bool operator==(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs) {
	return (lhs->get_root() == rhs->get_root());
}

template<class T>
bool operator!=(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs) {
	return !operator==(lhs, rhs);
}

template<class T>
bool operator<(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs) {
	return (lhs->size() < rhs->size());
}

template<class T>
bool operator<=(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs) {
	return !operator>(lhs, rhs);
}

template<class T>
bool operator>(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs) {
	return (lhs->size() > rhs->size());
}

template<class T>
bool operator>=(const TreeBlueprint<T>& lhs, const TreeBlueprint<T>& rhs) {
	return !operator<(lhs, rhs);
}

template<class T>
void swap(TreeBlueprint<T>& lhs, TreeBlueprint<T>& rhs) {
	lhs.swap(rhs);
}