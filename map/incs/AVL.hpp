/* this is an internal file included by map.hpp. it contains 
	the definition of AVL binary search tree and its node class templates
	Duplicate values are not allowed in this tree */

#ifndef AVL_HPP
#define AVL_HPP

#include <cstddef>
#include <memory>
#include <utility>
#include <functional>
#include <algorithm>
#include <Queue.hpp>

namespace ft {

	/******* AVL Node struct template definition *******/
	template<
		class T,
		class Allocator = std::allocator<T>
	> struct AVL_Node{

		/******* members types *******/
		typedef AVL_Node Node;
		typedef Allocator allocator_type;

		/******* constructors *******/
		AVL_Node(const T& data,
			int height = 0,
			int balanceFactor = 0,
			Node* parent = NULL,
			Node* left = NULL,
			Node* right = NULL);

		AVL_Node(const AVL_Node& other);

		/******* destructor *******/
		~AVL_Node();

		/******* memory management memeber functions *******/
		// allocates and constructs data object
		// does nothing if object already exists
		void createDataObject(const T& data);

		// deallocates and destructs data object
		// does nothing if object doesn't exist
		void removeDataObject();

		// removes existing object
		// creates a new one and initialize it to data
		void changeDataObject(const T& data);

		/******* member objects *******/
		T* data;
		int height, balanceFactor;
		Node* parent;
		Node* left;
		Node* right;

	};

	/******* AVL_Tree class template definition *******/
	template<
		class T,
		class Compare = std::less<T> ,
		class Allocator = std::allocator<T>
	> class AVL_Tree {

		public:
			/******* public member types *******/
			typedef AVL_Node<T, Allocator> Node;

			/******* constructors *******/
			AVL_Tree(const Compare& comparator = Compare());

			AVL_Tree(const AVL_Tree& other);

			/******* copy assignment operator *******/
			AVL_Tree& operator=(AVL_Tree other);

			/******* destructor *******/
			~AVL_Tree();

			/******* public member functions *******/
			void swap(AVL_Tree& other);

			// returns size of tree
			std::size_t size() const;

			// tests if tree is empty
			bool empty() const;

			// make tree empty
			void clear();

			//inserts new element in tree. returns pair that contains either "the new inserted node and true to indicate success" or
			// "an already existing node and false to indicate failure 
			// because an element with the same value already exists" 
			std::pair<const Node*, bool> insert(const T& data);

			// removes node whose data equals data parameter
			bool remove(const T& data);

			// finds next node that follows node in order
				// if node was last node, then NULL is returned
				// to indicate end of traversal
			Node* nextNode(Node* node);

			const Node* nextNode(const Node* node) const ;

			// finds previous node that precedes node in order
				// if node was first node, then NULL is returned
				// to indicate end of traversal
			Node* previousNode(Node* node);

			const Node* previousNode(const Node* node) const ;

			// performs binary search
			// searches for node in whole tree
				// if not found returns NULL
			Node* findNode(const T& data);

			const Node* findNode(const T& data) const ;

			// gets least significant node in whole tree
			// returns NULL if empty() == true
			const Node* getFirstNode() const;

			// gets most significant node in whole tree
			// returns same value as getFirstNode if empty() == true
			const Node* getLastNode() const;

		private:

			/******* private member types *******/
			// get allocator type for allocating nodes in AVL_Tree
			typedef typename
				Allocator::template rebind< AVL_Node<T> >::other
				node_allocator_type;

			/******* member objects *******/
			Node* mRoot;
			
			// first node in tree by order (aka node with smallest value)
			Node* mFirst;

			// last node in tree by order (aka node with largest value)
			Node* mLast;

			// number of nodes in tree
			std::size_t mNodeCount;

			// object used to compare two nodes' values
			Compare mComparator;

			// object used to allocate memory for nodes
			node_allocator_type mAllocator;

			/******* private member functions *******/
			// returns a newly allocated node
			Node* makeNewNode(const T& data, int height = 0,
				int balanceFactor = 0, Node* parent = NULL,
				Node* left = NULL, Node* right = NULL);

			// deallocates and destructs node
			void destroyNode(Node* node);

			// inserts data starting from node and sets insertPosition
			// to the newly inserted node
			// or to an already existing node that has same value as data
			Node* insert(Node* node, const T& data, Node** const insertPosition);

			// updates height and balance factor of node
			void updateAVLTraits(Node* node);

			// if needed, rebalances node by performing the neccessary rotations
			// returns the node that replaces node
				// in the tree after rebalancing
			Node* reBalance(Node* node);

			// returns the node that replaces node after right rotation
			Node* rotateRight(Node* node);

			// returns the node that replaces node after left rotation
			Node* rotateLeft(Node* node);

			// update mFirst if node->data < mFirst->data
				// only works with insert(Node*, const T&, ...)
			void updateFirst(Node* node);

			// update mLast if node->data > mLast->data
				// only works with insert(Node*, const T&, ...)
			void updateLast(Node* node);

			// removes all elements from tree
			void clear(Node* node);

			// actual removal function that's called by
				// remove(const T& data) public interface
			Node* remove(Node* node, const T& data);

			// LS = least significant
			// finds node with least significant value ( that comes first in order )
				// starting from start
			Node* findLSNode(Node* start);

			const Node* findLSNode(const Node* start) const ;

			// MS = most significant
			// finds node with most significant value ( that comes last in order )
				// starting from start
			Node* findMSNode(Node* start);

			const Node* findMSNode(const Node* start) const ;

			// finds node that has same value as data
				// search starts from node parameter
			Node* findNode(Node* node, const T& data);

			const Node* findNode(const Node* node, const T& data) const ;

	};

}

#include <AVL.tpp>

#endif