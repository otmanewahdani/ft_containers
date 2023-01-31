/* this file contains the implementation of the stack container class */

#ifndef STACK_TPP
#define STACK_TPP

namespace ft {

	// constructor, destructor and copy assignment operator
	template < class T, class Container >
	stack<T, Container>::stack( const Container& cont )
		: c(cont) {

		// checks if T and Container::value_type are the same
		typedef typename ft::enable_if< ft::is_same< T,
			value_type >::value >::type IsTypeValid;

		// just to silence warning about unused typedef
		IsTypeValid();

	}

	template < class T, class Container >
	stack<T, Container>::stack( const stack& other )
				: c(other.c) {}

	template < class T, class Container >
	stack<T, Container>::~stack() {}

	template < class T, class Container >
	stack<T, Container>& stack<T, Container>::operator=( const stack& other ){

		c = other.c;
		return (*this);

	}

	//element access
	template < class T, class Container >
	T& stack<T, Container>::top() { return c.back(); }

	template < class T, class Container >
	const T& stack<T, Container>::top() const { return c.back(); }

	// capacity
	template < class T, class Container >
	bool stack<T, Container>::empty() const { return c.empty(); }

	template < class T, class Container >
	typename stack<T, Container>::size_type
		stack<T, Container>::size() const { return c.size(); }
	
	// modifiers
	template < class T, class Container >
	void stack<T, Container>::push( const value_type& value )
				{ c.push_back(value); }

	template < class T, class Container >
	void stack<T, Container>::pop() { c.pop_back(); }

	// non-member relational operators
	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs ){

		return (lhs.c == rhs.c);

	}

	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs ){

		return (lhs.c != rhs.c);

	}

	template< class T, class Container >
	bool operator<( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs ){

		return (lhs.c < rhs.c);

	}

	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs ){

		return (lhs.c <= rhs.c);

	}

	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs ){

		return (lhs.c > rhs.c);

	}

	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs ){

		return (lhs.c >= rhs.c);

	}

}

#endif
