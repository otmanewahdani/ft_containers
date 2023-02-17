/* this is an internal file included by map.hpp. it contains 
	the definition of AVL binary search tree class template.
	Duplicate values are not allowed in this tree */

#ifndef AVL_HPP
#define AVL_HPP

#include <cstddef>
#include <memory>
#include <utility>
#include <functional>
#include <algorithm>

namespace ft {

	// AVL Node struct template definition
	template< class T >
	struct AVL_Node{

		/******* members types *******/
		typedef AVL_Node Node;

		/******* constructor *******/
		AVL_Node(const T& data,
			int height = 0,
			int balanceFactor = 0,
			Node* parent = NULL,
			Node* left = NULL,
			Node* right = NULL)

			: data(data)
			, height(height)
			, balanceFactor(balanceFactor)
			, parent(parent)
			, left(left)
			, right(right) {}

		/******* member objects *******/
		T data;
		int height, balanceFactor;
		Node* parent;
		Node* left;
		Node* right;

	};

	template<
		class T,
		class Compare = std::less<T> ,
		class Allocator = std::allocator< AVL_Node<T> >
	> class AVL_Tree {

		public:
			/******* member types *******/
			typedef AVL_Node<T> Node;

			/******* constructors *******/
			AVL_Tree(const Compare& comparator = Compare());

			AVL_Tree(const AVL_Tree& other);

			/******* copy assignment operator *******/
			AVL_Tree& operator=(AVL_Tree tree);

			/******* destructor *******/
			~AVL_Tree();

			/******* public member functions *******/
			void swap(AVL_Tree& tree);

			// returns size of tree
			std::size_t size() const;

			// tests if tree is empty
			bool isEmpty() const;

			// make tree empty
			void clear();

			//inserts new element in tree. returns pair that contains either "the new inserted node and true to indicate success" or
			// "an already existing node and false to indicate failure 
			// because an element with the same value already exists" 
			std::pair<const Node*, bool> insert(const T& data);

		private:
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
			Allocator mAllocator;

			/******* private member functions *******/
			// returns a newly allocated node
			Node* makeNewNode(const T& data, int height = 0,
				int balanceFactor = 0, Node* parent = NULL,
				Node* left = NULL, Node* right = NULL);

			// inserts data starting from node and sets insertPosition
			// to the newly inserted node
			// or to an already existing node that has same value as data
			Node* insert(Node* node, const T& data, const Node** insertPosition);

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
			void updateFirst(Node* node);

			// update mLast if node->data > mLast->data
			void updateLast(Node* node);

			// removes all elements from tree
			void clear(Node* node);

	};

}

#include <AVL.tpp>

#endif
