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

		: mAllocator(alloc)
		, mCapacity(count)
		, mSize(count){
			
			mElements = mAllocator.allocate(mSize);
			
			for (int i = 0; i < mSize; i++)
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

			for (InputIt it = first; it != last; it++)
				mCapacity++;

			if (!mCapacity)
				return ;

			mElements = mAllocator.allocate(mCapacity);

			for (int i = 0; first != last; first++, i++)
				mAllocator.construct(mElements + i, *first);

			mSize = mCapacity;

	}

}

#endif
