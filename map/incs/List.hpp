/* this is an internal file included by Queue.hpp.
	it contains the definition of the List template class.
	This template class is contains a simple implementation of a singly linked list.
	It is an allocator-aware container */

#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <cstddef>

namespace ft {

	template<
		class T,
		class Allocator = std::allocator<T>
	> class List {

		private:
			/******* member struct *******/
			struct Node {

				/******* constructor *******/
				Node(const T& data, Node* next = NULL)
					: data(data)
					, next(next) {}
				
				/******* member objects *******/
				T data;
				// next node in the list
				Node* next;

			};

		public:
			/******* constructor *******/
			List();

			/******* destructor *******/
			~List();

			/******* accessors *******/
			// returns element in the beginning of list
			T& front();

			// number of elements in list
			std::size_t size();

			// checks whether list is empty
			bool empty();

			/******* modifiers *******/
			// appends data to list
			void add_back(const T& data);

			// removes element from beginning of list
			void pop_front();

			// removes all elements fron list
			void clear();

		private:
			/******* member types *******/
			typedef typename Allocator::template
				rebind<Node>::other node_allocator_type;

			/******* member objects *******/
			// first element in list
			Node* mHead;
			
			// last element in list
			Node* mBack;

			// number of nodes in List
			std::size_t mNodeCount;

			// object used to allocate memory for nodes
			node_allocator_type mAllocator;

			/******* memory management *******/
			Node* makeNewNode(const T& data);

			void destroyNode(Node* node);

	};

}

#include <List.tpp>

#endif
