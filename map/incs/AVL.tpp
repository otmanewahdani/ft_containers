/* this is an internal file included by AVL.hpp. it contains 
	the implementation of AVL binary search tree and its node class templates */

#ifndef AVL_TPP
#define AVL_TPP

/******* AVL_Node implementation *******/
namespace ft {

	/******* constructors *******/
	// A = Allocator
	template< class T, class A >
	AVL_Node<T, A>::AVL_Node(const T& data, int height,
		int balanceFactor, Node* parent, Node* left, Node* right)
		: data()
		, height(height)
		, balanceFactor(balanceFactor)
		, parent(parent)
		, left(left)
		, right(right) {

			createDataObject(data);

	}

	template< class T, class A >
	AVL_Node<T, A>::AVL_Node(const AVL_Node& other)
		: data()
		, height(other.height)
		, balanceFactor(other.balanceFactor)
		, parent(other.parent)
		, left(other.left)
		, right(other.right) {

			createDataObject(*other.data);

	}

	/******* destructor *******/
	template< class T, class A >
	AVL_Node<T, A>::~AVL_Node(){

		removeDataObject();

	}

	/******* memory management memeber functions *******/
	template< class T, class A >
	void AVL_Node<T, A>::createDataObject(const T& data){

		allocator_type allocatorObj;

		if (data)
			return ;

		this->data = allocatorObj.allocate(1);

		allocatorObj.construct(this->data, data);

	}

	template< class T, class A >
	void AVL_Node<T, A>::removeDataObject(){

		allocator_type allocatorObj;

		if (!data)
			return ;
		
		allocatorObj.destroy(data);

		allocatorObj.deallocate(data, 1);

		data = NULL;

	}

	template< class T, class A >
	void AVL_Node<T, A>::changeDataObject(const T& data){

		removeDataObject();

		createDataObject(data);

	}

}

/******* AVL_Tree implementation *******/
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
	, mAllocator(){

		// copies tree nodes in a BFS manner from other
			// by adding a given nodes's children after dequeueing it
		// retrieves all nodes of level N from other
		// and inserts them directly below level N - 1 in this tree
		// thus no traveral of the tree nor rotations are needed
		// time complexity of this method is O(n)

		// enqueue nodes from other here and copies their data
		// into newly allocated nodes in tree
		Queue<Node*> nodesToCopyQueue;
		// new nodes will have their parents set by dequeuing them from here
		// after that the new nodes themselves will be enqueued here as parents
		// so that next nodes set them as their parents and so on...
		Queue<Node*> newNodesParentsQueue;

		if (!mNodeCount)
			return ;

		nodesToCopyQueue.enqueue(other.mRoot);

		Node* nodeToCopyFrom = NULL, newNodeToInsert = NULL, newNodeParent = NULL;

		// while there are nodes to copy in other
		while (!nodesToCopyQueue.empty()) {

			// get next node to copy and remove it from queue
			nodeToCopyFrom = nodesToCopyQueue.front();
			nodesToCopyQueue.dequeue();

			// get parent of the new node
			if (!newNodesParentsQueue.empty()){

				newNodeParent = newNodesParentsQueue.front();
				newNodesParentsQueue.dequeue();

			}

			// copies node
			newNodeToInsert = makeNewNode(*nodeToCopyFrom->data
				, nodeToCopyFrom->height, nodeToCopyFrom->balanceFactor
				, newNodeParent);

			// sets first node as root
			if (!newNodeParent)
				mRoot = newNodeToInsert;

			// if new node comes before parent, sets its parent's
				// left child to new node
			else if (mComparator(newNodeToInsert->data,
				newNodeParent->data))
				newNodeParent->left = newNodeToInsert;

			// if new node comes after parent, sets its parent's
				// right child to new node
			else
				newNodeParent->right = newNodeToInsert;

			// if first node by order reached in other
			// then set mFirst to the newly copied node
			if (nodeToCopyFrom == other.mFirst)
				mFirst = newNodeToInsert;

			// if last node by order reached in other
			// then set mLast to the newly copied node
			if (nodeToCopyFrom == other.mLast)
				mLast = newNodeToInsert;

			// if node that was copied from still has a left child
			// then adds its left child to nodesToCopyQueue to 
			// be copied from later
			// and adds the node that was just inserted (newly copied)
			// to newNodesParentsQueue so that it can be set as the
			// parent of the node that's going to copy the left
			// child of the nodeToCopyFrom when its turn comes
			if (nodeToCopyFrom->left){ 

				newNodesParentsQueue.enqueue(newNodeToInsert);
				nodesToCopyQueue.enqueue(nodeToCopyFrom->left);

			}

			// if node that was copied from still has a right child
			// then adds its right child to nodesToCopyQueue to 
			// be copied from later
			// and adds the node that was just inserted (newly copied)
			// to newNodesParentsQueue so that it can be set as the
			// parent of the node that's going to copy the right
			// child of the nodeToCopyFrom when its turn comes
			if (nodeToCopyFrom->right){

				newNodesParentsQueue.enqueue(newNodeToInsert);
				nodesToCopyQueue.enqueue(nodeToCopyFrom->right);

			}


		}

	}

	/******* destructor *******/
	~AVL_Tree();

	/******* public member functions *******/
	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::swap(AVL_Tree& other){

		// swap mNodeCount
		{
			std::size_t tmp = mNodeCount;
			mNodeCount = other.mNodeCount;
			other.mNodeCount = tmp;
		}

		//swap mRoot
		Node* tmp = mRoot;
		mRoot = other.mRoot;
		other.mRoot = tmp;

		//swap mFirst
		tmp = mFirst;
		mFirst = other.mFirst;
		other.mFirst = tmp;

		//swap mLast
		tmp = mLast;
		mLast = other.mLast;
		other.mLast = tmp;

	}

	template< class T, class C, class A>
	std::size_t AVL_Tree<T, C, A>::size() const {

		return mNodeCount;

	}

	template< class T, class C, class A>
	bool AVL_Tree<T, C, A>::isEmpty() const {

		return (!mNodeCount);

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::clear(){

		clear(mRoot);

		mRoot = mFirst = mLast = NULL;
		mNodeCount = 0;

	}

	template< class T, class C, class A>
	std::pair<const typename AVL_Tree<T, C, A>::Node*, bool> 
		AVL_Tree<T, C, A>::insert(const T& data) {

		// saves current node count to test it again new
			// node count to check if a node was added
		const std::size_t oldNodeCount = mNodeCount;

		// passes it to insert so the newly added node is saved here
			// or saves node that prevented insertion because
			// it already has the value as data
		Node* insertPosition = NULL;

		mRoot = insert(mRoot, data, &insertPosition);

		// if mNodeCount changed then insertPosition is the new node
			// else insertPosition is an already existing node
		return (std::make_pair(insertPosition,
			oldNodeCount != mNodeCount));

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
	void AVL_Tree<T, C, A>::destroyNode(Node* node){

		mAllocator.destroy(node);
		
		mAllocator.deallocate(node, 1);

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

		if (mComparator(data, *node->data)){
			node->left = add(node->left, data);
			node->left->parent = node;
		}
		else if (mComparator(*node->data, data)){
			node->right = add(node->right, data);
			node->right->parent = node;
		}
		else {

			// save node that prevented insertion
			*insertPosition = node;

			return node;

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

		if (!mFirst || mComparator(node->data, *mFirst->data))
			mFirst = node;

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::updateLast(Node *node){

		if (!mLast || mComparator(*mLast->data, node->data))
			mLast = node;

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::clear(Node* node) {

		if (!node)
			return ;

		clear(node->left);
		clear(node->right);

		destroyNode(node);

	}

}

#endif
