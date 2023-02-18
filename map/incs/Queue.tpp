/* this is an internal file included by Queue.hpp.
	it contains the implementation of Queue class template */

#ifndef QUEUE_TPP
#define QUEUE_TPP

namespace ft {

	/******* queue operations *******/
	// C = Container
	template <class T, class C>
	void Queue<T, C>::enqueue(const value_type& data){

		mContainer.add_back(data);

	}

	template <class T, class C>
	void Queue<T, C>::dequeue(){

		mContainer.pop_front();

	}

	/******* accessors *******/
	template <class T, class C>
	T& Queue<T, C>::front(){

		return (mContainer.front());

	}

	template <class T, class C>
	std::size_t Queue<T, C>::size(){

		return (mContainer.size());

	}

	template <class T, class C>
	bool Queue<T, C>::empty(){

		return (mContainer.empty());

	}

}

#endif
