/* this is an internal file included by AVL.hpp. it contains 
	the implementation of AVL binary search tree */

#ifndef AVL_TPP
#define AVL_TPP

namespace ft {

	// constructors
	template< class K, class T, class C, class A >
	map<K, T, C, A>::AVL_Tree::AVL_Tree()
		: mRoot()
		, nodeCount() 
		, value_comparator(key_compare()) {}

}

#endif
