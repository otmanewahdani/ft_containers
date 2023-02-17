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
	typename AVL_Tree<T, C, A>::Node* 
	AVL_Tree<T, C, A>::makeNewNode(
		const T& data, int height, int balanceFactor,
		Node* parent, Node* left, Node* right){

		Node* newNode = mAllocator.allocate(1);

		mAllocator.construct(newNode,
			Node(data, height, balanceFactor
				, parent, left, right));

		return newNode;

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node* AVL_Tree<T, C, A>::insert
		(Node* node, const T& data, const Node** insertPosition){
		
		if (!node){

			Node* newNode = makeNewNode(data);

			// update tree attributes
			mNodeCount++;
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
	void AVL_Tree<T, C, A>::updateAVLTraits(Node* node){
		
		int leftHeight = -1, rightHeight = -1;

		if (node->left)
			leftHeight = node->left->height;
		if (node->right)
			rightHeight = node->right->height;
		
		node->height = std::max(leftHeight, rightHeight) + 1;

		node->balanceFactor = leftHeight - rightHeight;

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::reBalance(Node* node){

		// right-heavy
		if (node->balanceFactor == -2){

			// right right case
			if (node->right->balanceFactor <= 0)
				return leftRotate(node);

			// right left case
			else{

				node->right = rightRotate(node->right);
				return leftRotate(node);

			}

		}
		// left-heavy
		else if (node->balanceFactor == 2){

			// left left case
			if (node->left->balanceFactor >= 0)
				return rightRotate(node);

			// left right case
			else{

				node->left = leftRotate(node->left);
				return rightRotate(node);

			}

		}

		return node;

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::rotateRight(Node* node){

		// left child becomes new parent of node
		// node becomes right child of old left child
		Node* oldLeftChild = node->left;

		// update parents
		oldLeftChild->parent = node->parent;
		node->parent = oldLeftChild;
		// node becomes parent of right child of oldLeftChild
		if (oldLeftChild->right)
			oldLeftChild->right->parent = node;

		// update children
		node->left = oldLeftChild->right;
		oldLeftChild->right = node;

		updateAVLTraits(node);
		updateAVLTraits(oldLeftChild);

		return oldLeftChild;

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::rotateLeft(Node* node){

		// right child becomes new parent of node
		// node becomes left child of old right child
		Node* oldRightChild = node->right;

		// update parents
		oldRightChild->parent = node->parent;
		node->parent = oldRightChild;
		// node becomes parent of left child of oldRightChild
		if (oldRightChild->left)
			oldRightChild->left->parent = node;

		// update children
		node->right = oldRightChild->left;
		oldRightChild->left = node;

		updateAVLTraits(node);
		updateAVLTraits(oldRightChild);

		return oldRightChild;

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::updateFirst(Node *node){

		if (!mFirst || mFirst->data > node->data)
			mFirst = node;

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::updateLast(Node *node){

		if (!mLast || mLast->data < node->data)
			mLast = node;

	}

}

#endif
