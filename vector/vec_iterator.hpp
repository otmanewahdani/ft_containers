#ifndef VEC_ITERATOR_HPP
#define VEC_ITERATOR_HPP


namespace ft{

	// ft::vector::const_iterator definiton
	template <
		class T,
		class Allocator
	> class vector<T, Allocator>::const_iterator{

			public:

				//member types
				typedef std::random_access_iterator_tag iterator_category;
				typedef T value_type;
				typedef std::ptrdiff_t difference_type;
				typedef const T* pointer;
				typedef const T& reference;

				// const_iterator constructors and copy assignment operator
				const_iterator() : mPtr(NULL) {}

				const_iterator(const T* ptr) : mPtr(ptr) {}

				const_iterator(const const_iterator& iter) : mPtr(iter.mPtr) {}

				const_iterator(const iterator& iter) : mPtr(iter.mPtr) {}

				const_iterator& operator=(const const_iterator& iter){
					mPtr = iter.mPtr;
					return (*this);
				}

				const_iterator& operator=(const iterator& iter){
					mPtr = iter.mPtr;
					return (*this);
				}

				// access operators
				const T& operator*() const {return (*mPtr);}

				const T* operator->() const {return mPtr;}

				const T& operator[](difference_type index) const {return (mPtr[index]);}

				// relational operators
				bool operator==(const const_iterator& iter) const {return (mPtr == iter.mPtr);}
				bool operator==(const iterator& iter) const {return (mPtr == iter.mPtr);}

				bool operator!=(const const_iterator& iter) const {return (mPtr != iter.mPtr);}
				bool operator!=(const iterator& iter) const {return (mPtr != iter.mPtr);}

				bool operator<=(const const_iterator& iter) const {return (mPtr <= iter.mPtr);}
				bool operator<=(const iterator& iter) const {return (mPtr <= iter.mPtr);}
				
				bool operator>=(const const_iterator& iter) const {return (mPtr >= iter.mPtr);}
				bool operator>=(const iterator& iter) const {return (mPtr >= iter.mPtr);}

				bool operator>(const const_iterator& iter) const {return (mPtr > iter.mPtr);}
				bool operator>(const iterator& iter) const {return (mPtr > iter.mPtr);}

				bool operator<(const const_iterator& iter) const {return (mPtr < iter.mPtr);}
				bool operator<(const iterator& iter) const {return (mPtr < iter.mPtr);}

				// increment/decrement operators
				const_iterator& operator++(){
					++mPtr;
					return (*this);
				}

				const_iterator operator++(int){
					const_iterator tmp(*this);
					++mPtr;
					return tmp;
				}

				const_iterator& operator--(){
					--mPtr;
					return (*this);
				}

				const_iterator operator--(int){
					const_iterator tmp(*this);
					--mPtr;
					return tmp;
				}

				// arithmetic assignment operators
				const_iterator& operator+=(difference_type n){
					mPtr += n;
					return (*this);
				}

				const_iterator& operator-=(difference_type n){
					mPtr -= n;
					return (*this);
				}

				// arithmetic operators
				const_iterator operator+(difference_type n) const {return const_iterator(mPtr + n);}

				friend const_iterator operator+(difference_type n, const const_iterator& iter){
					return (iter + n);
				}

				const_iterator operator-(difference_type n) const {return const_iterator(mPtr - n);}

				difference_type operator-(const const_iterator& iter) const {return (mPtr - iter.mPtr);}

				difference_type operator-(const iterator& iter) const {return (mPtr - iter.mPtr);}

				// make iterator a friend
				friend class iterator;

				// retuns underlying pointer
				const T* base() const {return mPtr;}

			private:

				// pointer to element in vector
				const T* mPtr;

		};

	// ft::vector::iterator definition
	template <
		class T,
		class Allocator
	> class vector<T, Allocator>::iterator{

			public:

				//member types
				typedef std::random_access_iterator_tag iterator_category;
				typedef T value_type;
				typedef std::ptrdiff_t difference_type;
				typedef T* pointer;
				typedef T& reference;

				// iterator constructors and copy assignment operator
				iterator() : mPtr(NULL) {}

				iterator(T* ptr) : mPtr(ptr) {}

				iterator(const iterator& iter) : mPtr(iter.mPtr) {}

				iterator& operator=(const iterator& iter){
					mPtr = iter.mPtr;
					return (*this);
				}

				// access operators
				T& operator*() const {return (*mPtr);}

				T* operator->() const {return mPtr;}

				T& operator[](difference_type index) const {return (mPtr[index]);}


				// relational operators
				bool operator==(const const_iterator& iter) const  {return (mPtr == iter.mPtr);}
				bool operator==(const iterator& iter) const  {return (mPtr == iter.mPtr);}

				bool operator!=(const const_iterator& iter) const {return (mPtr != iter.mPtr);}
				bool operator!=(const iterator& iter) const  {return (mPtr != iter.mPtr);}

				bool operator<=(const const_iterator& iter) const {return (mPtr <= iter.mPtr);}
				bool operator<=(const iterator& iter) const {return (mPtr <= iter.mPtr);}

				bool operator>=(const const_iterator& iter) const {return (mPtr >= iter.mPtr);}
				bool operator>=(const iterator& iter) const {return (mPtr >= iter.mPtr);}

				bool operator>(const const_iterator& iter) const {return (mPtr > iter.mPtr);}
				bool operator>(const iterator& iter) const {return (mPtr > iter.mPtr);}

				bool operator<(const const_iterator& iter) const {return (mPtr < iter.mPtr);}
				bool operator<(const iterator& iter) const {return (mPtr < iter.mPtr);}

				// increment/decrement operators
				iterator& operator++(){
					++mPtr;
					return (*this);
				}

				iterator operator++(int){
					iterator tmp(*this);
					++mPtr;
					return tmp;
				}

				iterator& operator--(){
					--mPtr;
					return (*this);
				}

				iterator operator--(int){
					iterator tmp(*this);
					--mPtr;
					return tmp;
				}

				// arithmetic assignment operators
				iterator& operator+=(difference_type n){
					mPtr += n;
					return (*this);
				}

				iterator& operator-=(difference_type n){
					mPtr -= n;
					return (*this);
				}


				// arithmetic operators
				iterator operator+(difference_type n) const {return iterator(mPtr + n);}

				friend iterator operator+(difference_type n, const iterator& iter){
					return (iter + n);
				}

				iterator operator-(difference_type n) const{return iterator(mPtr - n);}

				difference_type operator-(const const_iterator& iter) const {return (mPtr - iter.mPtr);}

				difference_type operator-(const iterator& iter) const {return (mPtr - iter.mPtr);}

				// make const_iterator a friend
				friend class const_iterator;

				// retuns underlying pointer
				T* base() const {return mPtr;}

			private:

				// pointer to element in vector
				T* mPtr;

		};

}

#endif
