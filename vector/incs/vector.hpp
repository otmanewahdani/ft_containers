/* this file contains the implementation of the vector container*/

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iterator>
#include <cstddef>
#include <iterator.hpp>
#include <type_traits.hpp>
#include <stdexcept>

namespace ft{

	template <
		class T,
		class Allocator = std::allocator<T>
	> class vector{

		private:

			// underlying array
			T* mElements;

			// associated allocator
			Allocator mAllocator;

			// number of elements that can be held
			// with current amount of memory allocated
			std::size_t mCapacity;

			// number of elements currently held by vector
			std::size_t mSize;

			// forward declaration of iterator class template
			template < class U >
			class vec_iterator;

		public:
			
			// member types
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef vec_iterator<T> iterator;
			typedef vec_iterator<const T> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			// constructors, destructors, assignment {operators, member functions}
			vector();

			explicit vector( const Allocator& alloc );

			explicit vector( size_type count,
                 const T& value = T(),
                 const Allocator& alloc = Allocator());

			template< class InputIt >
			vector( InputIt first, InputIt last,
				const Allocator& alloc = Allocator(),
				typename enable_if<!is_integral<InputIt>::value 
					,bool>::type = true);

			vector( const vector& other );

			~vector();

			vector& operator=( const vector& other );

			void assign( size_type count, const T& value );

			template< class InputIt >
			void assign( InputIt first, InputIt last,
				typename enable_if<!is_integral<InputIt>::value
					, bool>::type = true);

			// allocator member functions
			allocator_type get_allocator() const;

			// element access
			reference at( size_type pos );

			const_reference at( size_type pos ) const;

			reference operator[]( size_type pos );

			const_reference operator[]( size_type pos ) const;

			reference front();

			const_reference front() const;

			reference back();

			const_reference back() const;

			T* data();

			const T* data() const;

			//iterator getters
			iterator begin();

			const_iterator begin() const;

			iterator end();

			const_iterator end() const;

			//capacity
			bool empty() const;

			size_type size() const;

			size_type max_size() const;

			void reserve( size_type new_cap );

			size_type capacity() const;

			//modifiers
			void push_back( const T& value );

			void swap( vector& other );

			/* do a complete test of vec_iterator, iterator traits, reverse_iterator (with raw pointers as well) and element access. This test will be a part of evaluation*/

			/* make a script to compare two bins */

			/* test vector on Imac as well */

	};
}

#include <vec_iterator.hpp>
#include <vector.tpp>

#endif
