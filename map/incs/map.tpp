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
		, mArray(mValueComparator, mAllocator) {}

	/******* modifiers *******/
	template< class K, class T, class C, class A >
	void map<K, T, C, A>::clear() {
		
		mArray.clear();

	}

	template< class K, class T, class C, class A >
	pair< typename map<K, T, C, A>::iterator, bool >
		map<K, T, C, A>::insert( const value_type& value ) {

			// inserting value by calling insert interface
				// of underlying associative arrau
			std::pair<const node_type*, bool>
			// return of array_type::insert(const T&)
				ret = mArray.insert(value);

			// first member of ret is a node pointer that represents
				// either the location of the newly inserted node or of
				//  the node that prevented th insertion because it
				// already has a data field equivalent to value
				// (duplicate values aren't allowed)
			// second member of type bool indicates whether value 
				// got actually inserted
			// takes first member of ret and converts it to an iterator
			// second member is returned as is
			return ( make_pair(iterator(ret.first), ret.second) );

	}

	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::iterator
		map<K, T, C, A>::insert( iterator , const value_type& value ) {

			// first parameter is ignored in this implemetation
				// unlike the STL implementation in which it is actually
				// used to hint to where to insert value directly
			// therefore this member function is equivalent to this
				// insert member function : insert(const value_type&)
				// with a slight difference in the return type

			// calling the other version of insert and extracting
				// only the iterator member of its return value (of
				 // pair type)
			return ( insert(value).first );

	}


	template< class K, class T, class C, class A >
	template< class InputIt >
	void map<K, T, C, A>::insert( InputIt first, InputIt last ) {

		// calling member function overload insert(const value_type&)
			// on each element in range first to last (not including last)
		for (; first != last; ++first)
			insert(*first);

	}

}

#endif
