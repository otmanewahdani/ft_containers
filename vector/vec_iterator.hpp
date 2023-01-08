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
				const_iterator();
				const_iterator(const T* ptr);
				const_iterator(const const_iterator& iter);
				const_iterator(const iterator& iter);
				const_iterator& operator=(const const_iterator& iter);
				const_iterator& operator=(const iterator& iter);

				// access operators
				const T& operator*() const ;
				const T* operator->() const ;
				const T& operator[](difference_type index) const ;

				// relational operators
				bool operator==(const const_iterator& iter) const ;
				bool operator==(const iterator& iter) const ;
				bool operator!=(const const_iterator& iter) const ;
				bool operator!=(const iterator& iter) const ;
				bool operator<=(const const_iterator& iter) const ;
				bool operator<=(const iterator& iter) const ;
				bool operator>=(const const_iterator& iter) const ;
				bool operator>=(const iterator& iter) const ;
				bool operator>(const const_iterator& iter) const ;
				bool operator>(const iterator& iter) const ;
				bool operator<(const const_iterator& iter) const ;
				bool operator<(const iterator& iter) const ;

				// increment/decrement operators
				const_iterator& operator++();
				const_iterator operator++(int);
				const_iterator& operator--();
				const_iterator operator--(int);

				// arithmetic assignment operators
				const_iterator& operator+=(difference_type n);
				const_iterator& operator-=(difference_type n);

				// arithmetic operators
				const_iterator operator+(difference_type n) const ;
				friend const_iterator operator+(difference_type n, const const_iterator& iter);
				const_iterator operator-(difference_type n) const;
				difference_type operator-(const const_iterator& iter) const ;
				difference_type operator-(const iterator& iter) const;

				// make iterator a friend
				friend class iterator;

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
				iterator();
				iterator(T* ptr);
				iterator(const iterator& iter);
				iterator& operator=(const iterator& iter);

				// access operators
				T& operator*() const ;
				T* operator->() const ;
				T& operator[](difference_type index) const ;

				// relational operators
				bool operator==(const const_iterator& iter) const ;
				bool operator==(const iterator& iter) const ;
				bool operator!=(const const_iterator& iter) const ;
				bool operator!=(const iterator& iter) const ;
				bool operator<=(const const_iterator& iter) const ;
				bool operator<=(const iterator& iter) const ;
				bool operator>=(const const_iterator& iter) const ;
				bool operator>=(const iterator& iter) const ;
				bool operator>(const const_iterator& iter) const ;
				bool operator>(const iterator& iter) const ;
				bool operator<(const const_iterator& iter) const ;
				bool operator<(const iterator& iter) const ;

				// increment/decrement operators
				iterator& operator++();
				iterator operator++(int);
				iterator& operator--();
				iterator operator--(int);

				// arithmetic assignment operators
				iterator& operator+=(difference_type n);
				iterator& operator-=(difference_type n);

				// arithmetic operators
				iterator operator+(difference_type n) const ;
				friend iterator operator+(difference_type n, const iterator& iter);
				iterator operator-(difference_type n) const;
				difference_type operator-(const const_iterator& iter) const ;
				difference_type operator-(const iterator& iter) const;

				// make const_iterator a friend
				friend class const_iterator;

			private:

				// pointer to element in vector
				T* mPtr;

		};

}

#endif
