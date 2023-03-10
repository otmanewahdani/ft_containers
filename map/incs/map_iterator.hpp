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
	> template <class U, class NODE, class ARRAY>
	class map<Key, T, Compare, Allocator>::map_iterator {

		friend class map;

		// make all instantiations of map_iterator friend so that copy
			// operations and comparisons of a map_iterator object with 
			// const value_type and another one with non-const
			// value_type would work by having access directly
			// to their private member objects.
		template <class U2, class N2, class AR2>
		friend class map_iterator;

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
			template<class U2, class N2, class AR2>
			map_iterator(const map_iterator<U2, N2, AR2>& other);

			/******* copy assignment operator *******/
			// same remark as the templated copy constructor
			template<class U2, class N2, class AR2>
			map_iterator& operator=(const map_iterator<U2, N2, AR2>& other);

			/******* access operators *******/
			// returns a reference to value_type
				// value_type could be const
			reference operator*() const;

			// returns a pointer to value_type
				// same remark about constness as above operator
			pointer operator->() const;

			/******* relational operators *******/
			// this operator was templated so that comparisons
				// can work between iterators who differ only
				// in the constness of their template arguments
			template<class U2, class N2, class AR2>
			bool operator==(const map_iterator<U2, N2, AR2>& other) const;

			// same remark as the above operator
			template <class U2, class N2, class AR2>
			bool operator!=(const map_iterator<U2, N2, AR2>& other) const;

			/******* increment/decrement operators *******/
			map_iterator& operator++();

			map_iterator operator++(int);

			map_iterator& operator--();

			map_iterator operator--(int);

		private:

			typedef NODE node_type;
			typedef ARRAY array_type;

			/******* member objects *******/
			// underlying node pointer to element in map
			node_type* mNodePtr;

			// pointer to whole associative array that underlies map
			array_type* mArrayPtr;

			/******* parameterized constructor *******/
			// a valid iterator will be one that's instantiated 
				// through this constructor
			// it needs be passed to it a pointer to the node
				// represented by this iterator and a pointer to the
				// array object containing this node
			// a past_the_end or before-begin iterator (for reverse
				// iteration) will be represented by passing a NULL
				// pointer to node_type but the pointer to array_type
				// still has to be valid and dereferenceable
			// this constructor can only be instantied by the map
				// container class (hence the friend declaration)
			map_iterator(node_type* const nodePtr,
				array_type* const arrayPtr);

	};

}

#include <map_iterator.tpp>

#endif
