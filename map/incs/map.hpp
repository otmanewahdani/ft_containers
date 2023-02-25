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
#include <utility>
#include <stdexcept>
#include <limits>

namespace ft {

	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator< pair<const Key, T> >
	> class map {

		public:
			/******* member classes *******/
			// forward declaration of value_compare class
			class value_compare;

			/******* member types *******/
			typedef pair<const Key, T> value_type;

		private:
			/******* member types *******/
			// underlying associative array type used to represent elements of map
			typedef AVL_Tree<value_type, value_compare, Allocator>
				array_type ;

			// node type used in array_type
			typedef typename array_type::Node node_type ;

			/******* member class templates *******/
			// forward declaration of member map::iterator
				// class template
			// U = type
			// NODE = type of node being used
			// ARRAY = type of underlying associative array
				// where type NODE belongs
			template < class U, class NODE, class ARRAY >
			class map_iterator;

		public:
			/******* member types *******/
			typedef Key key_type;
			typedef T mapped_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef map_iterator<value_type, node_type,
				array_type> iterator;
			typedef map_iterator<const value_type,
				const node_type, const array_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			/******* constructors *******/
			map();

			explicit map( const key_compare& comp,
				const allocator_type& alloc = Allocator() );

			template< class InputIt >
			map( InputIt first, InputIt last,
				const key_compare& comp = Compare(),
				const allocator_type& alloc = Allocator() );

			map( const map& other );

			/******* destructor *******/
			~map();

			/******* copy assignment operator *******/
			map& operator=( const map& other );

			/******* allocator getter *******/
			allocator_type get_allocator() const;

			/******* element access *******/
			mapped_type& at( const key_type& key );

			const mapped_type& at( const key_type& key ) const;

			mapped_type& operator[]( const key_type& key );

			/******* iterators *******/
			iterator begin();

			const_iterator begin() const;

			iterator end();

			const_iterator end() const;

			reverse_iterator rbegin();

			const_reverse_iterator rbegin() const;

			reverse_iterator rend();

			const_reverse_iterator rend() const;

			/******* capacity *******/
			bool empty() const;

			size_type size() const;

			size_type max_size() const;

			/******* modifiers *******/
			void clear();

			pair<iterator, bool> insert( const value_type& value );

			iterator insert( iterator , const value_type& value );

			template< class InputIt >
			void insert( InputIt first, InputIt last );

			void erase( iterator pos );

			void erase( iterator first, iterator last );

			size_type erase( const key_type& key );

			void swap( map& other );

			/******* look-up *******/
			size_type count( const key_type& key ) const;

			iterator find( const key_type& key );

			const_iterator find( const key_type& key ) const;

			iterator lower_bound( const key_type& key );

			const_iterator lower_bound( const key_type& key ) const;

			iterator upper_bound( const key_type& key );

			const_iterator upper_bound( const key_type& key ) const;

			pair<iterator,iterator> equal_range( const key_type& key );

			pair<const_iterator,const_iterator>
				equal_range( const key_type& key ) const;

			/******* observers *******/
			key_compare key_comp() const;

			value_compare value_comp() const;

		private:
			/******* member objects *******/
			// underlying allocator
			allocator_type mAllocator;

			// underlying object that compares keys
			key_compare mKeyComparator;

			// underlying object that compares elements of map
			value_compare mValueComparator;

			// underlying associative array object
			array_type mArray;

	};

}

#include <map_iterator.hpp>
#include <map.tpp>

#endif
