/* this is an internal file that contains the implementation of vector memebers */

#ifndef VECTOR_TPP
#define VECTOR_TPP

namespace ft{

			// constructors, destructors, assignment {operators, member functions}
	template <
		class T,
		class Allocator
	> vector<T, Allocator>::vector()

		: mElements(NULL)
		, mAllocator()
		, mCapacity(0)
		, mSize(0){
	}

	template <
		class T,
		class Allocator
	> vector<T,Allocator>::vector( const Allocator& alloc )

		: mElements(NULL)
		, mAllocator(alloc)
		, mCapacity(0)
		, mSize(0){
	}

	template <
		class T,
		class Allocator
	> vector<T,Allocator>::vector( size_type count,
		 const T& value,
		 const Allocator& alloc)

		: mElements(NULL)
		, mAllocator(alloc)
		, mCapacity(0)
		, mSize(0){
			
			mElements = mAllocator.allocate(mSize);
			
			for (size_type i = 0; i < mSize; i++)
				mAllocator.construct(mElements + i, value);

	}

	template <
		class T,
		class Allocator
	> template< class InputIt >
	vector<T,Allocator>::vector(InputIt first, InputIt last,
		const Allocator& alloc)
		: mElements(NULL)
		, mAllocator(alloc)
		, mCapacity(0)
		, mSize(0) {

		(void) first;
		(void) last;
/* construct object depending on whether InputIt is signle-pass

			for (InputIt it = first; it != last; it++)
				mCapacity++;

			if (!mCapacity)
				return ;

			mElements = mAllocator.allocate(mCapacity);

			for (int i = 0; first != last; first++, i++)
				mAllocator.construct(mElements + i, *first);

			mSize = mCapacity;
			*/

	}
	
	template <
		class T,
		class Allocator
	> vector<T,Allocator>::vector(const vector& other)
	: mElements(NULL)
	, mAllocator(other.mAllocator)
	, mCapacity(0)
	, mSize(0){
	}
	
	template <
		class T,
		class Allocator
	> void vector<T,Allocator>::assign
		( size_type count, const T& value ){

			const bool isAssignable = count > mCapacity ? false : true;

			T* tmp;
			// allocate a new array
			if (!isAssignable){
				tmp = mAllocator.allocate(count);
				mCapacity = count;
			}
			// use old array
			else{
				tmp = mElements;
				mElements = NULL;
			}

			for (size_type i = 0; i <
				(mSize < count ? mSize : count); i++)
				// copy assign value to old elements
				if (isAssignable)
					tmp[i] = value;
				// construct new object in the newly allocated memory
				else
					mAllocator.construct(tmp + i, value);

			// continue constructing if count is more than previous size
			for (size_type i = mSize; i < count; i++)
					mAllocator.construct(tmp + i, value);

			// if assignable, destroy objects in tmp because it will point to old array
			// else destroy objects in mElements since it will be pointing on old array and tmp on newly allocated array
			T* const arrayToDestroy = isAssignable ? tmp : mElements; 
			
			// destroyed unused objects
			for (size_type i = !isAssignable ? 0
				: count ; i < mSize; i++)
				mAllocator.destroy(arrayToDestroy + i);

			// deallocate old array if another array was allocated
			mAllocator.deallocate(mElements, mSize);
			mElements = tmp;

			mSize = count;

	}

	template <
		class T,
		class Allocator
	> template< class InputIt >
	void vector<T,Allocator>::assign( InputIt first, InputIt last,
		typename enable_if<!is_integral<InputIt>() &&
		!is_floating_point<InputIt>(), bool>::type){
		
		// checks if it's not an output iterator
		typedef typename enable_if<!is_output_iterator<InputIt>::value>::type 
			RequiresInputIt;

		// just to silence warning about unused typedef
		RequiresInputIt();

		// check if it's an input iterator

	}

	// capacity
	template <
		class T,
		class Allocator
	> std::size_t vector<T,Allocator>::max_size() const{

		return (mAllocator.max_size());

	}

	template <
		class T,
		class Allocator
	> void vector<T,Allocator>::reserve( size_type new_cap ){
		
		if (new_cap <= mCapacity)
			return ;

		if (new_cap > max_size())
			throw (std::length_error("vector::reserve"));

	}

	// modifiers
	template <
		class T,
		class Allocator
	> void vector<T,Allocator>::push_back( const T& value ){
	}

}

#endif
