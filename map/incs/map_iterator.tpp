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
		, mArrayPtr(mArrayPtr) {}

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

			return (*mNodePtr->data);

	}

	template<class K, class T, class C, class A>
	template <class U> 
	typename map<K, T, C, A>::map_iterator<U>::pointer
		map<K, T, C, A>::map_iterator<U>::operator->() const {

			return (mNodePtr->data);

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

}

#endif
