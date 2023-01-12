#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iterator>

namespace ft{

	template <
		class T,
		class Allocator = std::allocator<T>
	> class vector{

		private:

			// underlying array
			T* mElements;

			// forward declaration of iterator class template
			template < class U >
			class vec_iterator;

		public:
			
			// member types
			typedef vec_iterator<T> iterator;
			typedef vec_iterator<const T> const_iterator;

			// constructors, destructors, assignment {operators, member functions}

			// allocator member functions

			// element access

			//iterator getters

			/* do a complete test of vec_iterator, iterator traits, reverse_iterator (with raw pointers as well) and element access. This test will be a part of evaluation

	};
}

#include <vec_iterator.hpp>
#include <vector.tpp>

#endif
