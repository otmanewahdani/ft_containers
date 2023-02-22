/* this is an internal file included by map_iterator.hpp.
	it contains the implementation of map_iterator class template
*/

#ifndef MAP_ITERATOR_TPP
#define MAP_ITERATOR_TPP

namespace ft {

	/******* constructors *******/
	// map template paramters
		// K = Key, T = type, C = Container, A = Allocator
	template<class K, class T, class C, class A>
	// map_iterator template parameters
	template <class U> 
	map<K, T, C, A>::map_iterator<U>::map_iterator()
		: mNodePtr()
		, mArrayPtr() {}

	template<class K, class T, class C, class A>
	template <class U> 
	// template parameter of map_iterator's function template members
	template<class X>
	map<K, T, C, A>::map_iterator<U>::
		map_iterator(const map_iterator<X>& other)
		: mNodePtr(other.mNodePtr)
		, mArrayPtr(other.mArrayPtr) {}

	/******* parameterized constructor *******/
	template<class K, class T, class C, class A>
	template <class U> 
	map<K, T, C, A>::map_iterator<U>::map_iterator
	(const node_type* const nodePtr, const array_type* const arrayPtr)
		: mNodePtr(nodePtr)
		, mArrayPtr(arrayPtr) {}

	/******* copy assignment operator *******/
	template<class K, class T, class C, class A>
	template <class U> 
	template<class X>
	map<K, T, C, A>::map_iterator<U>& // returns reference to itself
		map<K, T, C, A>::map_iterator<U>::operator=
		(const map_iterator<X>& other){

			this->mNodePtr = other.mNodePtr;
			this->mArrayPtr = other.mArrayPtr;

			return (*this);

	}

	/******* access operators *******/
	template<class K, class T, class C, class A>
	template <class U> 
	typename map<K, T, C, A>::map_iterator<U>::reference
		map<K, T, C, A>::map_iterator<U>::operator*() const {

		// gets the pointer to value_type and derefenrences it
		return (*this->operator->());
	}

	template<class K, class T, class C, class A>
	template <class U> 
	typename map<K, T, C, A>::map_iterator<U>::pointer
		map<K, T, C, A>::map_iterator<U>::operator->() const {

		// removes constness of the node pointer in case
			// the underlying data was to be modified
		return (const_cast<node_type*>(mNodePtr)->data);

	}

	/******* relational operators *******/
	template<class K, class T, class C, class A>
	template <class U> 
	template<class X>
	bool map<K, T, C, A>::map_iterator<U>::operator==
		(const map_iterator<X>& other) const {

		return (mNodePtr == other.mNodePtr);

	}

	template<class K, class T, class C, class A>
	template <class U> 
	template <class X>
	bool map<K, T, C, A>::map_iterator<U>::operator!=
		(const map_iterator<X>& other) const {

			return !(*this == other);

	}

	/******* increment/decrement operators *******/
	template<class K, class T, class C, class A>
	template <class U> 
	map<K, T, C, A>::map_iterator<U>&
		map<K, T, C, A>::map_iterator<U>::operator++(){

		// if node pointer wasn't pointing at any element in array,
			// makes it point at first element
		if (!mNodePtr)
			mNodePtr = mArrayPtr->mFirst;
		// makes node pointer points to next node (node that
			// follows currently pointed at node in order)
		else
			mNodePtr = mArrayPtr->nextNode(mNodePtr);

		return (*this);

	}

	template<class K, class T, class C, class A>
	template <class U> 
	map<K, T, C, A>::map_iterator<U>
		map<K, T, C, A>::map_iterator<U>::operator++(int) {

			// makes a copy of current object
			map_iterator tmp(*this);

			this->operator++();

			return tmp;

	}

	template<class K, class T, class C, class A>
	template <class U> 
	map<K, T, C, A>::map_iterator<U>&
		map<K, T, C, A>::map_iterator<U>::operator--() {

		// if node pointer wasn't pointing at any element in array,
			// makes it point at last element
		if (!mNodePtr)
			mNodePtr = mArrayPtr->mLast;

		// gets pointer to node that precedes the node that's
			// currently being pointed at
		else
			mNodePtr = mArrayPtr->previousNode(mNodePtr);

	}

	template<class K, class T, class C, class A>
	template <class U> 
	map<K, T, C, A>::map_iterator<U>
		map<K, T, C, A>::map_iterator<U>::operator--(int) {

			// same comment as the post-increment operator
			map_iterator tmp(*this);

			this->operator--();

			return tmp;

	}

}

#endif
