/* this file contains the implementation of the vector container*/

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iterator>
#include <cstddef>
#include <iterator.hpp>
#include <type_traits.hpp>
#include <stdexcept>
#include <algorithm>
#include <algorithm.hpp>
#include <functional>

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

			//regular iterator getters
			iterator begin();

			const_iterator begin() const;

			iterator end();

			const_iterator end() const;

			// reverse iterator getters
			reverse_iterator rbegin();

			const_reverse_iterator rbegin() const;

			reverse_iterator rend();

			const_reverse_iterator rend() const;

			//capacity
			bool empty() const;

			size_type size() const;

			size_type max_size() const;

			void reserve( size_type new_cap );

			size_type capacity() const;

			//modifiers
			void clear();

			iterator insert( const_iterator pos, const T& value );

			void insert( const_iterator pos, size_type count, const T& value );

			template< class InputIt >
			void insert( const_iterator pos, InputIt first, InputIt last,
				typename enable_if<!is_integral<InputIt>::value
					, bool>::type = true);

			iterator erase( iterator pos );

			iterator erase( iterator first, iterator last );

			void push_back( const T& value );

			void pop_back();

			void resize( size_type count, T value = T() );

			void swap( vector& other );

			/* do a complete test of vec_iterator, iterator traits, reverse_iterator (with raw pointers as well) and element access. This test will be a part of evaluation*/

			/* make a script to compare two bins */

			/* test vector on Imac as well */

		private:
		
			// move to the right all elements starting from start to the end of the array
			// new position = old position + new_pos
			// the moving starts from the back so no subsequent elements are overwritten
			void shiftElemsToRight(const size_type start, const size_type new_pos){

				for (size_type i = mSize; i > start; --i){
					
					// constructs new element
					if (i - 1 + new_pos >= mSize){

						mAllocator.construct(mElements + i - 1 + new_pos,
							mElements[i - 1]);
						continue;

					}

					// copy assigns to old element
					mElements[i - 1 + new_pos] = mElements[i - 1];

				}

			}

	};

	// non-member overloads
	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs,
		const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs,
		const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs,
		const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs,
		const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs,
		const vector<T,Alloc>& rhs );

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs,
		const vector<T,Alloc>& rhs );

}

// std::swap specialization
template< class T, class Alloc >
void std::swap( ft::vector<T,Alloc>& lhs,
	ft::vector<T,Alloc>& rhs );

#include <vec_iterator.hpp>
#include <vector.tpp>

#endif
