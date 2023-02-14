/* this is an internal file included by map.hpp. it contains 
	the definition of AVL binary search tree */

#ifndef AVL_HPP
#define AVL_HPP

template<
	class Key,
	class T,
	class Compare,
	class Allocator
> struct ft::map<Key, T, Compare, Allocator>::AVL_Tree {

	// Node struct definition
	struct Node{

		/* constructor requires passing a tree class pointer
			to the tree containg this node so that tree size
			can be modified directly after removal or insertion
			of a new node */
		Node(const value_type& data, AVL_Tree* tree)
			: data(data)
			, height()
			, balanceFactor()
			, left()
			, right()
			, parent()
			, tree(tree) { ++tree->nodeCount; }

		~Node() { --tree->nodeCount; }

		value_type data, height, balanceFactor;
		Node* left;
		Node* right;
		Node* parent;

		// pointer to the tree class defining this node
		AVL_Tree* tree;

	};

	// constructors
	AVL_Tree();

	// copy assignment operator

	// destructor

	// member objects

	Node* mRoot;

	// number of nodes in tree
	size_type nodeCount;

	// object used to compare two nodes
	value_compare value_comparator;

	// member functions

};

#include <AVL.tpp>

#endif
