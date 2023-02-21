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
namespace ft {

	// map template parameters meaning:
		// K = Key, T = type, C = Compare, A = Allocator

	/******* constructors *******/
	template< class K, class T, class C, class A >
	map<K, T, C, A>::map()
		: mAllocator()
		, mKeyComparator()
		, mValueComparator(mKeyComparator)
		, mArray(mValueComparator) {}

	template< class K, class T, class C, class A >
	map<K, T, C, A>::map(const key_compare& comp,
		const allocator_type& alloc)
		: mAllocator(alloc)
		, mKeyComparator(comp)
		, mValueComparator(mKeyComparator)
		, mArray(mValueComparator) {}

}

#endif
