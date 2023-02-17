/* this file contains the definition of ft::map container class.
	The underlying associative array is implemented using an AVL
		binary search tree. */

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <utility.hpp>
#include <memory>
#include <cstddef>
#include <iterator.hpp>
#include <AVL.hpp>

namespace ft {

	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator< pair<const Key, T> >
	> class map {

		private:
			// forward declaration of member map::iterator class template
			template < class U >
			class map_iterator;

		public:
			// member types
			typedef Key key_type;
			typedef T mapped_type;
			typedef pair<const Key, T> value_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef map_iterator<value_type> iterator;
			typedef map_iterator<const value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			// member classes
			// forward declaration of value_compare class
			class value_compare;

			// constructors

		private:

			// underlying associative array (AVL tree)
			AVL_Tree<
				value_type,
				value_compare,
				Allocator
			> mArray( value_compare(key_compare()) );

	};

}

#include <map_iterator.hpp>
#include <map.tpp>

#endif
