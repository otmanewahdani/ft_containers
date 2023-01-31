/* this file contains the definition of the stack container class */

#ifndef STACK_HPP
#define STACK_HPP

#include <vector.hpp>
#include <type_traits.hpp>

namespace ft {

	// forward declaration of stack container class
	template< class T, class Container >
	class stack;

	// forward declaration of non-member relational operators
	template< class T, class Container >
	bool operator==( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs );

	template< class T, class Container >
	bool operator!=( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs );

	template< class T, class Container >
	bool operator<( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs );

	template< class T, class Container >
	bool operator<=( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs );

	template< class T, class Container >
	bool operator>( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs );

	template< class T, class Container >
	bool operator>=( const stack<T,Container>& lhs,
		const stack<T,Container>& rhs );

	// definition of stack container class
	template<
		class T,
		class Container = ft::vector<T>
	> class stack {

		public:

			// member types
			typedef Container container_type;
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef typename Container::reference reference;
			typedef typename Container::const_reference const_reference;

			// constructor, destructor and copy assignment operator
			explicit stack( const Container& cont = Container() );

			~stack();

			stack& operator=( const stack& other );

			// element access
			T& top();

			const T& top() const;

			// capacity
			bool empty() const;

			size_type size() const;

			// modifiers
			void push( const value_type& value );

			void pop();

			// non-member relational operators
			friend bool operator== <>( const stack<T,Container>& lhs,
				const stack<T,Container>& rhs );

			friend bool operator!= <>( const stack<T,Container>& lhs,
				const stack<T,Container>& rhs );

			friend bool operator< <>( const stack<T,Container>& lhs,
				const stack<T,Container>& rhs );

			friend bool operator<= <>( const stack<T,Container>& lhs,
				const stack<T,Container>& rhs );

			friend bool operator> <>( const stack<T,Container>& lhs,
				const stack<T,Container>& rhs );

			friend bool operator>= <>( const stack<T,Container>& lhs,
				const stack<T,Container>& rhs );

		protected:
			
			// underlying container
			container_type c;

	};

}

#include <stack.tpp>

#endif
