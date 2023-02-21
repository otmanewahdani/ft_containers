/* this is an internal file included by map_iterator.hpp.
	it contains the implementation of map_iterator class template
*/

#ifndef MAP_ITERATOR_TPP
#define MAP_ITERATOR_TPP

namespace ft {

	/******* constructors *******/
	map_iterator();

	template<class X>
	map_iterator(const map_iterator<X>& other);

	/******* parameterized contructor *******/
	map_iterator(const node_type* const nodePtr,
		const array_type* const arrayPtr);

}

#endif
