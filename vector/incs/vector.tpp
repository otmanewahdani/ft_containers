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
	> vector<T,Allocator>::~vector() {

		for (size_type i = 0; i < mSize; i++)
			mAllocator.destroy(mElements + i);

		mAllocator.deallocate(mElements, mCapacity);

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
			mAllocator.deallocate(mElements, mCapacity);
			mElements = tmp;

			if (!isAssignable)
				mCapacity = count;
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

	// element access
	template <
		class T,
		class Allocator
	> T* vector<T,Allocator>::data() { return mElements; }

	template <
		class T,
		class Allocator
	> const T* vector<T,Allocator>::data() const{
		return (const_cast<const T*>(mElements));
	}

	// capacity
	template <
		class T,
		class Allocator
	> bool vector<T,Allocator>::empty() const{
		return (!mSize);
	}

	template <
		class T,
		class Allocator
	> std::size_t vector<T,Allocator>::size() const{
		return mSize;
	}

	template <
		class T,
		class Allocator
	> std::size_t vector<T,Allocator>::max_size() const{

		const size_type max1 = mAllocator.max_size();
		const size_type max2 = std::numeric_limits<difference_type>::max();
		// max_size of allocator cannot exceed max value of difference_type
		return (max1 < max2 ? max1 : max2);

	}

	template <
		class T,
		class Allocator
	> void vector<T,Allocator>::reserve( size_type new_cap ){
		
		if (new_cap <= mCapacity)
			return ;

		if (new_cap > max_size())
			throw (std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));

		T* const tmp = mAllocator.allocate(new_cap);

		// copy old elements in new array
		for (size_type i = 0; i < mSize; i++)
			mAllocator.construct(tmp + i, mElements[i]);

		// destroy old elements
		for (size_type i = 0; i < mSize; i++)
			mAllocator.destroy(mElements + i);

		// deallocate old array
		mAllocator.deallocate(mElements, mCapacity);

		mElements = tmp;
		mCapacity = new_cap;

	}

	template <
		class T,
		class Allocator
	> std::size_t vector<T,Allocator>::capacity() const{
		return mCapacity;
	}

	// modifiers
	template <
		class T,
		class Allocator
	> void vector<T,Allocator>::push_back( const T& value ){
		

		// if container reached full capacity, increase the capacity
			// to 1 if container was previously empty or else double previous capacity
		// else keep previous capacity
		const size_type newCapacity = mCapacity == mSize ?
			(!mSize ? 1 : (mCapacity * 2)) : mCapacity;

		// create a temporary vector, reserve newCapacity of memory in there
		//copy current elements to it and add additional element of value
		// swap it with current container
		if (newCapacity != mCapacity){

				vector tmp;
				tmp.reserve(newCapacity);

				for (size_type i = 0; i < mSize; i++){
					tmp.mAllocator.construct(tmp.mElements + i, mElements[i]);
					tmp.mSize++;
				}

				tmp.mAllocator.construct(tmp.mElements + mSize, value);
				
				this->swap(tmp);

		}
		else
			mAllocator.construct(mElements + mSize, value);

		mCapacity = newCapacity;
		mSize++;

	}

	template <
		class T,
		class Allocator
	> void vector<T,Allocator>::swap( vector& other ){

		size_type tmp_size = mSize;
		mSize = other.mSize;
		other.mSize = tmp_size;

		tmp_size = mCapacity;
		mCapacity = other.mCapacity;
		other.mCapacity = tmp_size;

		const allocator_type tmp_alloc = mAllocator;
		mAllocator = other.mAllocator;
		other.mAllocator = tmp_alloc;

		T* const tmp_array = mElements;
		mElements = other.mElements;
		other.mElements = tmp_array;

	}

}

#endif
