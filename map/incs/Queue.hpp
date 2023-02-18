/* this is an internal file included by AVL.hpp.
	it contains the definition of Queue class template
	which implements a simple queue.
	it is a container adaptor that uses List from List.hpp
		as default underlying container
	
	any container can be supplied to Queue if it
	implements the following member functions:
		+ add_back(const T&)
		+ pop_front()
		+ T& front()
		+ size()
		+ empty()
*/

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <List.hpp>
#include <cstddef>

namespace ft {

	template <
		class T,
		class Container = ft::List<T>
	> class Queue {

		public:
			/******* member types *******/
			typedef Container container_type;
			typedef T value_type;

			/******* queue operations *******/
			// adds data to queue
			void enqueue(const value_type& data);

			// removes first element in queue
			void dequeue();

			/******* accessors *******/
			// accesses first element in queue
			value_type& front();

			// returns size of queue
			std::size_t size();

			// checks whether queue is empty
			bool empty();
		
		protected:
			/******* underlying container *******/
			container_type mContainer;

	};

}

#include <Queue.tpp>

#endif
