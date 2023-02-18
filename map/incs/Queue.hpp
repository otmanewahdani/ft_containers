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

#include <Queue.tpp>

#endif
