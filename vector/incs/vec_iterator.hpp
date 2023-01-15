/* this is an internal file included by vector.hpp.
	it contains the class template implementation from
	which vector::iterator and vector::const_iterator are instantiated */

#ifndef VEC_ITERATOR_HPP
#define VEC_ITERATOR_HPP


namespace ft{

	// definiton of ft::vector::iterator class template
	// which ft::vector::iterator and ft::vector::const_iterator use 
	template <
		class T,
		class Allocator
	> template < class U >
	class vector<T, Allocator>::vec_iterator{

			public:

				//member types
				typedef std::random_access_iterator_tag iterator_category;
				typedef T value_type;
				typedef std::ptrdiff_t difference_type;
				typedef U* pointer;
				typedef U& reference;

				// iterator constructors and copy assignment operator
				vec_iterator() : mPtr(NULL) {}

				vec_iterator(U* ptr) : mPtr(ptr) {}

				template < class X >
				vec_iterator(const vec_iterator<X>& iter) : mPtr(iter.base()) {}

				template < class X >
				vec_iterator& operator=(const vec_iterator<X>& iter){
					mPtr = iter.base();
					return (*this);
				}

				// access operators
				U& operator*() const {return (*mPtr);}

				U* operator->() const {return mPtr;}

				U& operator[](difference_type index) const {return (mPtr[index]);}


				// relational operators
				template < class X >
				bool operator==(const vec_iterator<X>& iter) const  {return (mPtr == iter.base());}

				template < class X >
				bool operator!=(const vec_iterator<X>& iter) const  {return (mPtr != iter.base());}

				template < class X >
				bool operator<=(const vec_iterator<X>& iter) const {return (mPtr <= iter.base());}

				template < class X >
				bool operator>=(const vec_iterator<X>& iter) const {return (mPtr >= iter.base());}

				template < class X >
				bool operator>(const vec_iterator<X>& iter) const {return (mPtr > iter.base());}

				template < class X >
				bool operator<(const vec_iterator<X>& iter) const {return (mPtr < iter.base());}

				// increment/decrement operators
				vec_iterator& operator++(){
					++mPtr;
					return (*this);
				}

				vec_iterator operator++(int){
					vec_iterator tmp(*this);
					++mPtr;
					return tmp;
				}

				vec_iterator& operator--(){
					--mPtr;
					return (*this);
				}

				vec_iterator operator--(int){
					vec_iterator tmp(*this);
					--mPtr;
					return tmp;
				}

				// arithmetic assignment operators
				vec_iterator& operator+=(difference_type n){
					mPtr += n;
					return (*this);
				}

				vec_iterator& operator-=(difference_type n){
					mPtr -= n;
					return (*this);
				}


				// arithmetic operators
				vec_iterator operator+(difference_type n) const {return vec_iterator(mPtr + n);}

				friend vec_iterator operator+(difference_type n, const vec_iterator& iter){
					return (iter + n);
				}

				vec_iterator operator-(difference_type n) const{return vec_iterator(mPtr - n);}

				template < class X >
				difference_type operator-(const vec_iterator<X>& iter) const {return (mPtr - iter.base());}

				// retuns underlying pointer
				U* base() const {return mPtr;}

			private:

				// pointer to element in vector
				U* mPtr;

	};

}

#endif
