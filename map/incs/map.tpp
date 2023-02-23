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

	template< class K, class T, class C, class A >
	template< class InputIt >
	map<K, T, C, A>::map( InputIt first, InputIt last,
		const key_compare& comp, const allocator_type& alloc )
		: mAllocator(alloc)
		, mKeyComparator(comp)
		, mValueComparator(mKeyComparator)
		, mArray(mValueComparator, mAllocator) {

			// copies range
			insert(first, last);

	}

	template< class K, class T, class C, class A >
	map<K, T, C, A>::map( const map& other )
		: mAllocator(other.mAllocator)
		, mKeyComparator(other.mKeyComparator)
		, mValueComparator(mKeyComparator)
		// calls copy constructor of mArray
		, mArray(other.mArray) {}
	
	/******* destructor *******/
	// implicitly calls destructor of mArray which handles
		// the process of cleaning
	template< class K, class T, class C, class A >
	map<K, T, C, A>::~map() {}

	/******* copy assignment operator *******/
	template< class K, class T, class C, class A >
	map<K, T, C, A>&
		map<K, T, C, A>::operator=( const map& other ) {

		// copies other temporarily
		map tmp(other);

		// then swaps it with this map
		this->swap(tmp);

		return *this;

	}

	/******* allocator getter *******/
	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::allocator_type
		map<K, T, C, A>::get_allocator() const { return mAllocator; }

	/******* iterators *******/
	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::iterator
		map<K, T, C, A>::begin() {

			// since this method returns an iterator to the first
				// element in the map, it needs to construct
				// an iterator from the first node in the underlying
				// array as a first argument and the second argument
				// is always the underlying array containing the node
			return ( iterator(mArray.getFirstNode(), &mArray) );

	}

	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::const_iterator
		map<K, T, C, A>::begin() const {

			// calls non-const version of this method
			return ( const_cast<map*>(this)->begin() );

	}

	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::iterator
		map<K, T, C, A>::end() {

			// passes NULL to iterator to indicate that it points to
				// past the last node and therefore it
				// doesn't point to any valid node
			// passes the underlying array as a second argument so
				// that the last node is still reachable after a
				// decrement operation on the iterator
			return ( iterator(NULL, &mArray) );

	}

	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::const_iterator
		map<K, T, C, A>::end() const {

			// calls non-const version of this method
			return ( const_cast<map*>(this)->end() );

	}

	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::reverse_iterator
		map<K, T, C, A>::rbegin() {

			// reverses end iterator
			return ( reverse_iterator(end()) );

	}

	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::const_reverse_iterator
		map<K, T, C, A>::rbegin() const {

			// calls non-const version of this method
			return ( const_cast<map*>(this)->rbegin() );

	}

	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::reverse_iterator
		map<K, T, C, A>::rend() {

			// reverses begin iterator
			return ( reverse_iterator(begin()) );

	}

	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::const_reverse_iterator
		map<K, T, C, A>::rend() const {

			// calls non-const version of this method
			return ( const_cast<map*>(this)->rend() );

	}

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
			std::pair<node_type*, bool>
			// return of array_type::insert(const T&)
				ret = mArray.insert(value);

			// first member of ret is a node pointer that represents
				// either the location of the newly inserted node or of
				//  the node that prevented th insertion because it
				// already has a data field equivalent to value
				// (duplicate values aren't allowed)
			// second member of type bool indicates whether value 
				// got actually inserted
			// takes first member of ret and address of underlying
				// array and converts them to an iterator
			// second member is returned as is
			return ( ft::make_pair(iterator(ret.first, &mArray), ret.second) );

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

	template< class K, class T, class C, class A >
	void map<K, T, C, A>::swap( map& other ) {

		// swapping allocators
		std::swap(mAllocator, other.mAllocator);

		// swapping key comparators
		std::swap(mKeyComparator, other.mKeyComparator);

		// swapping value comparators
		std::swap(mValueComparator, other.mValueComparator);

		// swapping underlying arrays
		mArray.swap(other.mArray);

	}

	/******* look-up *******/
	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::iterator
		map<K, T, C, A>::find( const key_type& key ) {

			// creates a tmp pair of key and a default initialized
				// value of type mapped_type
			// this pair will serve as a look-up value in mArray
				// findNode method since the represented type in
				// mArray is value_type and not key_type. It will
				// be compared against stored objects in mArray
				// to determine if their keys are equivalent.
			value_type tmp(key, mapped_type());

			// calls find method in mArray to retrive the node
				// whose data contains same key as tmp
			return ( iterator(mArray.findNode(tmp), &mArray) );

	}

	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::const_iterator
		map<K, T, C, A>::find( const key_type& key ) const {

			// calls non-const version of this method
			return ( const_cast<map*>(this)->find(key) );

	}

	/******* element access *******/
	template< class K, class T, class C, class A >
	typename map<K, T, C, A>::mapped_type&
		map<K, T, C, A>::at( const key_type& key ) {

			// look key up
			iterator tmp = find(key);

			// element doesn't exist
			if (tmp == end())
				throw std::out_of_range("no such element");

			// returns mapped value
			return tmp->second;

	}

	template< class K, class T, class C, class A >
	const typename map<K, T, C, A>::mapped_type&
		map<K, T, C, A>::at( const key_type& key ) const {

			// calls non-const version of this method
			return ( const_cast<map*>(this)->at(key) );

	}

}

#endif
