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
			
			// forward declarations
			class const_iterator;
			class iterator;

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

#include <vec_iterator.hpp>
#include <vector.tpp>

#endif
