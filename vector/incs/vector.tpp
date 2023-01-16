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
		, mCapacity(count)
		, mSize(count){
			
			if (!count)
				return ;

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
	: mAllocator(other.mAllocator)
	, mCapacity(other.mCapacity)
	, mSize(other.mSize){
	}
	
	template <
		class T,
		class Allocator
	> void vector<T,Allocator>::assign
		( size_type count, const T& value ){


			// destroyed unused objects
			for (size_type i = mSize <= count ?
				0 : count; i < mSize; i++)
				mAllocator.destroy(mElements[i]);

			mSize = count;

			T* tmp;
			// allocate a new array
			if (count > mCapacity){
				tmp = mAllocator.allocate(count);
				mCapacity = count;
			}
			// use old array
			else{
				tmp = mElements;
				mElements = NULL;
			}

			// assign new elements
			for (size_type i = 0; i < mSize; i++)
				tmp[i] = value;


			mAllocator.deallocate(mElements);
			mElements = tmp;

	}

}

#endif
