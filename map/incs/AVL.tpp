/* this is an internal file included by AVL.hpp. it contains 
	the implementation of AVL binary search tree */

#ifndef AVL_TPP
#define AVL_TPP

namespace ft {

	/******* constructors *******/
	// C = Compare; A = Allocator
	template< class T, class C, class A>
	AVL_Tree<T, C, A>::AVL_Tree(const C& comparator)
		: mRoot()
		, mFirst()
		, mLast()
		, mNodeCount()
		, mComparator(comparator)
		, mAllocator() {}

	template< class T, class C, class A>
	AVL_Tree<T, C, A>::AVL_Tree(const AVL_Tree& other)
	: mRoot()
	, mFirst()
	, mLast()
	, mNodeCount(other.mNodeCount)
	, mComparator(other.mComparator)
	, mAllocator() {
	}

	/******* private member functions *******/
	template< class T, class C, class A>
	Node* AVL_Tree<T, C, A>::insert
		(Node* node, const T& data, const Node** insertPosition){
		
		if (!node){

			Node* newNode = makeNewNode(data);

			// update tree attributes
			nodeCount++;
			updateFirst(newNode);
			updateLast(newNode);

			// save newly inserted position
			*insertPosition = newNode;

			return newNode;

		}

		if (data == node->data){

			// save node that prevented insertion
			*insertPosition = node;

			return node;

		}

		if (data < node->data){
			node->left = add(node->left, data);
			node->left->parent = node;
		}
		else if (data > node->data){
			node->right = add(node->right, data);
			node->right->parent = node;
		}

		updateAVLTraits(node);

		return reBalance(node);

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::updateFirst(Node *node){

		if (!first || first->data > node->data)
			first = node;

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::updateLast(Node *node){

		if (!last || last->data < node->data)
			last = node;

	}

}

#endif
