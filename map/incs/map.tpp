/* this is an internal file containing the implementation
	of ft::map container class */

#ifndef MAP_TPP
#define MAP_TPP

// map::value_compare class implementation
template< class K, class T, class C, class A >
class ft::map<K, T, C, A>::value_compare
	: public std::binary_function<
		value_type, value_type, bool> {

	// declare map container class as friend so it can construct
	// a value_compare object
	friend class map;

	public:

		// comparator member function
		bool operator()( const value_type& lhs,
			const value_type& rhs ) const{

				return (comp(lhs.first, rhs.first));

		}

	protected:

		// constructor
		value_compare( key_compare c )
			: comp(c) {}

		// object used to compare keys
		key_compare comp;

};

// map container class implementation

#endif
