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
		// U = type, N = Node, AR = Array
	template <class U, class N, class AR> 
	map<K, T, C, A>::map_iterator<U, N, AR>::map_iterator()
		: mNodePtr()
		, mArrayPtr() {}

	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	// template parameter of map_iterator's function template members
	template<class U2, class N2, class AR2>
	map<K, T, C, A>::map_iterator<U, N, AR>::
		map_iterator(const map_iterator<U2, N2, AR2>& other)
		: mNodePtr(other.mNodePtr)
		, mArrayPtr(other.mArrayPtr) {}

	/******* parameterized constructor *******/
	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	map<K, T, C, A>::map_iterator<U, N, AR>::map_iterator
	(node_type* const nodePtr, array_type* const arrayPtr)
		: mNodePtr(nodePtr)
		, mArrayPtr(arrayPtr) {}

	/******* copy assignment operator *******/
	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	template<class U2, class N2, class AR2>
	typename map<K, T, C, A>::template map_iterator<U, N, AR>& // returns reference to itself
		map<K, T, C, A>::map_iterator<U, N, AR>::operator=
		(const map_iterator<U2, N2, AR2>& other){

			this->mNodePtr = other.mNodePtr;
			this->mArrayPtr = other.mArrayPtr;

			return (*this);

	}

	/******* access operators *******/
	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	typename map<K, T, C, A>::template map_iterator<U, N, AR>::reference
		map<K, T, C, A>::map_iterator<U, N, AR>::operator*() const {

		// gets the pointer to value_type and derefenrences it
		return (*this->operator->());
	}

	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	typename map<K, T, C, A>::template map_iterator<U, N, AR>::pointer
		map<K, T, C, A>::map_iterator<U, N, AR>::operator->() const {

		// removes constness of the node pointer in case
			// the underlying data was to be modified
		return (const_cast<node_type*>(mNodePtr)->data);

	}

	/******* relational operators *******/
	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	template<class U2, class N2, class AR2>
	bool map<K, T, C, A>::map_iterator<U, N, AR>::operator==
		(const map_iterator<U2, N2, AR2>& other) const {

		return (mNodePtr == other.mNodePtr);

	}

	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	template <class U2, class N2, class AR2>
	bool map<K, T, C, A>::map_iterator<U, N, AR>::operator!=
		(const map_iterator<U2, N2, AR2>& other) const {

			return !(*this == other);

	}

	/******* increment/decrement operators *******/
	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	typename map<K, T, C, A>::template map_iterator<U, N, AR>&
		map<K, T, C, A>::map_iterator<U, N, AR>::operator++(){

		// if node pointer wasn't pointing at any element in array,
			// makes it point at first element
		if (!mNodePtr)
			mNodePtr = mArrayPtr->getFirstNode();
		// makes node pointer points to next node (node that
			// follows currently pointed at node in order)
		else
			mNodePtr = mArrayPtr->nextNode(mNodePtr);

		return (*this);

	}

	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	typename map<K, T, C, A>::template map_iterator<U, N, AR>
		map<K, T, C, A>::map_iterator<U, N, AR>::operator++(int) {

			// makes a copy of current object
			map_iterator tmp(*this);

			this->operator++();

			return tmp;

	}

	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	typename map<K, T, C, A>::template map_iterator<U, N, AR>&
		map<K, T, C, A>::map_iterator<U, N, AR>::operator--() {

		// if node pointer wasn't pointing at any element in array,
			// makes it point at last element
		if (!mNodePtr)
			mNodePtr = mArrayPtr->getLastNode();

		// gets pointer to node that precedes the node that's
			// currently being pointed at
		else
			mNodePtr = mArrayPtr->previousNode(mNodePtr);

		return (*this);

	}

	template<class K, class T, class C, class A>
	template <class U, class N, class AR> 
	typename map<K, T, C, A>::template map_iterator<U, N, AR>
		map<K, T, C, A>::map_iterator<U, N, AR>::operator--(int) {

			// same comment as the post-increment operator
			map_iterator tmp(*this);

			this->operator--();

			return tmp;

	}

}

#endif
