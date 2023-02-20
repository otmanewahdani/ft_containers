/* this is an internal file included by map.hpp.
	it contains the definition of a nested class template in map from
	which map::iterator and map::const_iterator are instantiated */

/* map_iterator was implemented as a class template so that it
	can support all types and their const forms as well */

#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

namespace ft {

	template<
		class Key,
		class T,
		class Compare,
		class Allocator
	> template <class U>
	class map<Key, T, Compare, Allocator>::map_iterator {

		friend class map;

		public:
			/******* member types *******/
			typedef std::bidirectional_iterator_tag iterator_category;
			typedef map::value_type value_type;
			typedef map::difference_type difference_type;
			typedef U* pointer;
			typedef U& reference;

			/******* constructors *******/
			map_iterator();

			// the copy constructor was templated so that 
				// in case this object's value_type is const,
				// it can still copy objects with non-const value_type
				// which is essentially a different
				// template parameter
			template<class X>
			map_iterator(const map_iterator<X>& other);

			/******* copy assignment operator *******/
			// same remark as the templated copy constructor
			template<class X>
			map_iterator& operator=(const map_iterator<X>& other);

		private:
			/******* member objects *******/
			// underlying node pointer to element in map
			const node_type* mNodePtr;

			/******* parameterized contructor *******/
			map_iterator(const node_type* nodePtr);

	};

}

#include <map_iterator.tpp>

#endif
