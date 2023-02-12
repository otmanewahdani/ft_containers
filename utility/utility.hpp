/* this file contains the definition and implementation
	of ft::pair class template and ft::make_pair function template */

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft{

	// ft::pair
	template<
		class T1,
		class T2
	> struct pair {

		// member types
		typedef T1 first_type;
		
		typedef T2 second_type;

		// member objects
		first_type first;

		second_type second;

		// constructors
		pair() : first(), second() {}

		pair( const T1& x, const T2& y )
			: first(x), second(y) {}

		template< class U1, class U2 >
		pair( const pair<U1, U2>& p )
			: first(p.first)
			, second(p.second) {}

	};

	// non-member relational operators of ft::pair
	template< class T1, class T2 >
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs){

		return (lhs.first == rhs.first &&
			lhs.second == rhs.second);

	}

	template< class T1, class T2 >
	bool operator!=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ){

		return (!(lhs == rhs));

	}

	template< class T1, class T2 >
	bool operator<( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ){

		return ( lhs.first < rhs.first
			|| (!(rhs.first < lhs.first)
				&& (lhs.second < rhs.second))
		);

	}

	template< class T1, class T2 >
	bool operator<=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ){

		return (!(rhs < lhs));

	}

	template< class T1, class T2 >
	bool operator>( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ){

		return (rhs < lhs);

	}

	template< class T1, class T2 >
	bool operator>=( const pair<T1, T2>& lhs, const pair<T1, T2>& rhs ){
	
		return (!(lhs < rhs));

	}

	//ft::make_pair
	template< class T1, class T2 >
	pair<T1, T2> make_pair( T1 t, T2 u ){

		return pair<T1, T2>(t, u);

	}

}

#endif
