/* this file contains the implementation of iterator_traits and reverse_iterator */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

// iterator_traits definition
namespace ft{

	// template used for the typical iterators like the STL containers iterators
	template< class Iter >
	struct iterator_traits{

		// retrieve these types from Iter directly
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;

	};

	// template specialization for raw pointers
	template< class T >
	struct iterator_traits<T*>{

		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;

	};

	// template specialization for const raw pointers
	template< class T >
	struct iterator_traits<const T*> : iterator_traits<T*>{

		typedef const T* pointer;
		typedef const T& reference;

	};

}

// reverse_iterator definition
namespace ft{

	template< class Iter >
	class reverse_iterator{

		public:
			
			// member types
			typedef Iter iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename iterator_traits<Iter>::value_type value_type;
			typedef typename iterator_traits<Iter>::difference_type difference_type;
			typedef typename iterator_traits<Iter>::pointer pointer;
			typedef typename iterator_traits<Iter>::reference reference;

			//constructors and copy assignment operator
			reverse_iterator() : current() {}

			explicit reverse_iterator( iterator_type x ) : current(x) {}

			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()) {}

			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other ){
				current = other.base();
				return (*this);
			}

			// returns current
			iterator_type base() const { return current; }

			// access operators
			reference operator*() const {
				iterator_type tmp = current;
				return (*--tmp);
			}

			pointer operator->() const { return &(this->operator*()); }

			reference operator[]( difference_type n ) const { return current[-n-1]; }

			// increment/decrement operators
			reverse_iterator& operator++(){
				--current;
				return (*this);
			}

			reverse_iterator& operator--(){
				++current;
				return (*this);
			}

			reverse_iterator operator++( int ){
				reverse_iterator tmp(*this);
				--current;
				return (tmp);
			}

			reverse_iterator operator--( int ){
				reverse_iterator tmp(*this);
				++current;
				return (tmp);
			}

			// arithmetic operators
			reverse_iterator operator+( difference_type n ) const {
				return (reverse_iterator(current - n));
			}

			reverse_iterator operator-( difference_type n ) const {
				return (reverse_iterator(current + n));
			}

			friend reverse_iterator operator+(difference_type n, const reverse_iterator& it){
				return (it + n);
			}

			template < class Iter2 >
			friend difference_type operator-(const reverse_iterator& lhs, const reverse_iterator<Iter2>& rhs){
				return (lhs.base() - rhs.base());
			}

			// arithmetic assignment operators
			reverse_iterator& operator+=( difference_type n ){
				current -= n;
				return (*this);
			}

			reverse_iterator& operator-=( difference_type n ){
				current += n;
				return (*this);
			}

			// relational operators
			template < class Iter2 >
			friend bool operator==(const reverse_iterator& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() == rhs.base()); }

			template < class Iter2 >
			friend bool operator!=(const reverse_iterator& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() != rhs.base()); }

			template < class Iter2 >
			friend bool operator<(const reverse_iterator& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() < rhs.base()); }

			template < class Iter2 >
			friend bool operator<=(const reverse_iterator& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() <= rhs.base()); }

			template < class Iter2 >
			friend bool operator>(const reverse_iterator& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() > rhs.base()); }

			template < class Iter2 >
			friend bool operator>=(const reverse_iterator& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() >= rhs.base()); }

		protected:

			// underlying iterator
			iterator_type current;

	};

}

#endif
