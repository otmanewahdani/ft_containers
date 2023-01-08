#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iterator>

namespace ft{

	template <
		class T,
		class Allocator = std::allocator<T>
	> class vector{

		public:

		// ft::vector::const_iterator definiton
		class const_iterator{

			public:

			//member types
			typedef std::random_access_iterator_tag iterator_category;
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef const T* pointer;
			typedef const T& reference;

			// const_iterator constructors and copy assignment operator
			const_iterator();
			const_iterator(const T* ptr);
			const_iterator(const const_iterator& iter);
			const_iterator& operator=(const const_iterator& iter);

			// access operators
			const T& operator*() const ;
			const T* operator->() const ;
			const T& operator[](int index) const ;

			// relational operators
			bool operator==(const const_iterator& iter) const ;
			bool operator!=(const const_iterator& iter) const ;
			bool operator<=(const const_iterator& iter) const ;
			bool operator>=(const const_iterator& iter) const ;
			bool operator>(const const_iterator& iter) const ;
			bool operator<(const const_iterator& iter) const ;

			private:

				// pointer to element in vector
				const T* mPtr;

		};

		// ft::vector::iterator definition
		// it uses most of const_iterator functionality
		// with a few override exceptions
		class iterator : public const_iterator{

			public:

			// member types overrides
			typedef T* pointer;
			typedef T& reference;

			//access operators

		};

		// member types

		// constructors, destructors, assignment {operators, member functions}

		// allocator member functions

		// element access

		//iterator getters

		private:

			// underlying array
			T* mElements;

	};
}

#include <vec_iterator.tpp>
#include <vector.tpp>

#endif
