/* this is an internal file included by AVL.hpp. it contains 
	the implementation of AVL binary search tree class template
	and its node class template */

#ifndef AVL_TPP
#define AVL_TPP

/******* AVL_Node implementation *******/
namespace ft {

	/******* constructors *******/
	// A = Allocator
	template< class T, class A >
	AVL_Node<T, A>::AVL_Node(const T& data, int height,
		int balanceFactor, Node* parent,
		const allocator_type& allocatorObj, Node* left, Node* right)
		: data()
		, height(height)
		, balanceFactor(balanceFactor)
		, parent(parent)
		, mAllocator(allocatorObj)
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
		, mAllocator(other.mAllocator)
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

		if (this->data)
			return ;

		this->data = mAllocator.allocate(1);

		mAllocator.construct(this->data, data);

	}

	template< class T, class A >
	void AVL_Node<T, A>::removeDataObject(){

		if (!this->data)
			return ;

		mAllocator.destroy(this->data);

		mAllocator.deallocate(this->data, 1);

		this->data = NULL;

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
	AVL_Tree<T, C, A>::AVL_Tree(const C& comparator,
		const allocator_type& allocatorObj)
		: mRoot()
		, mFirst()
		, mLast()
		, mNodeCount()
		, mComparator(comparator)
		, mAllocator(allocatorObj)
		, mNodeAllocator() {}

	template< class T, class C, class A>
	AVL_Tree<T, C, A>::AVL_Tree(const AVL_Tree& other)
	: mRoot()
	, mFirst()
	, mLast()
	, mNodeCount(other.mNodeCount)
	, mComparator(other.mComparator)
	, mAllocator(other.mAllocator)
	, mNodeAllocator(other.mNodeAllocator) {

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

		Node* nodeToCopyFrom = NULL, *newNodeToInsert = NULL, *newNodeParent = NULL;

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
			else if (mComparator(*newNodeToInsert->data,
				*newNodeParent->data))
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

	/******* copy assignment operator *******/
	template< class T, class C, class A>
	AVL_Tree<T, C, A>&
		AVL_Tree<T, C, A>::operator=(AVL_Tree other){

		this->swap(other);
		return *this;

	}

	/******* destructor *******/
	template< class T, class C, class A>
	AVL_Tree<T, C, A>::~AVL_Tree(){

		clear();

	}

	/******* allocator getters *******/
	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::allocator_type
		AVL_Tree<T, C, A>::get_allocator() const {

			return mAllocator;

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::node_allocator_type
		AVL_Tree<T, C, A>::get_node_allocator() const {

			return mNodeAllocator;

	}

	/******* public member functions *******/
	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::swap(AVL_Tree& other){

		// swap mNodeCount
		{
			std::size_t tmp = mNodeCount;
			mNodeCount = other.mNodeCount;
			other.mNodeCount = tmp;
		}

		{
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

		// swap mComparator
		{
			C tmp = mComparator;
			mComparator = other.mComparator;
			other.mComparator = tmp;
		}

		// swap mAllocator
		{
			allocator_type tmp = mAllocator;
			mAllocator = other.mAllocator;
			other.mAllocator = tmp;
		}

		// swap mNodeAllocator
		{
			node_allocator_type tmp = mNodeAllocator;
			mNodeAllocator = other.mNodeAllocator;
			other.mNodeAllocator = tmp;
		}

	}

	template< class T, class C, class A>
	std::size_t AVL_Tree<T, C, A>::size() const {

		return mNodeCount;

	}

	template< class T, class C, class A>
	bool AVL_Tree<T, C, A>::empty() const {

		return (!mNodeCount);

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::clear(){

		clear(mRoot);

		mRoot = mFirst = mLast = NULL;
		mNodeCount = 0;

	}

	template< class T, class C, class A>
	std::pair<typename AVL_Tree<T, C, A>::Node*, bool> 
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

	template< class T, class C, class A>
	bool AVL_Tree<T, C, A>::remove(const T& data){

		// saves current node count to test it again new
			// node count to check if a node was effectively removed
		const std::size_t oldNodeCount = mNodeCount;

		// calls actual removal method
		mRoot = remove(mRoot, data);

		// returns true if new nodeCount changed
			// otherwise false
		return (oldNodeCount != mNodeCount);

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::nextNode(Node* node){

		if (!node || node == mLast)
			return NULL;

		Node* next = node;

		// as long as a node with a more significant value (data)
			//	hasn't been found yet (since next node must have a more
			// significant value than the current), keep searching

		// loop = while next comes before node or while they are equivalent
		while (mComparator(*next->data, *node->data)
			|| next == node){ 

			// if right subtree has already been visited
				// keeps going back up the tree
			// the above condition is checked by verifying
				// whether the right child of next precedes node
				// of if they're equivalent
				// if right child's value has a more significant
				// value than node, the body of this if statement
				// is skipped and execution goes to next step
				// which is to get the successor node from right subtree
			if (!next->right
				|| mComparator(*next->right->data, *node->data)
				|| next->right == node) { 

				next = next->parent;
				continue;

			}

			// gets successor from right subtree
			next = findLSNode(next->right);

		}
		
		return next;

	}

	template< class T, class C, class A>
	const typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::nextNode(const Node* node) const {

		// calls non-const version of nextNode()
		return ( const_cast<AVL_Tree*>(this)->nextNode
			(const_cast<Node*>(node)) );

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::previousNode(Node* node){

		if (!node || node == mFirst)
			return NULL;

		Node* previous = node;

		// as long as a node with a less significant value (data) hasn't 
			// been found yet (since previous node must have a less
			// significant value than the current), keep searching

		// loop = while previous comes after node (has a more significant
			// value than node) or while they are equivalent
		while (mComparator(*node->data, *previous->data)
			|| node == previous){

			// if left subtree has already been visited
				// keeps going back up the tree
			// the above condition is checked by verifying
				// whether the left child of next succeeds node
				// of if they're equivalent
				// if left child's value has a more significant or equivalent
				// value than node, the body of this if statement
				// is skipped and execution goes to next step
				// which is to get the predecessor node from left subtree
			if (!previous->left ||
				mComparator(*node->data, *previous->left->data)
				|| previous->left == node) {

				previous = previous->parent;
				continue ;

			}

			// gets predecessor from left subtree
			previous = findMSNode(previous->left);

		}

		return previous;
	
	}

	template< class T, class C, class A>
	const typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::previousNode(const Node* node) const {

		// calls non-const version of previousNode()
		return ( const_cast<AVL_Tree*>(this)->previousNode
			(const_cast<Node*>(node)) );

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findNode(const T& data) {

		// calls private version: findNode(Node*, const T&)
			// with mRoot as starting point of search
		return (findNode(mRoot, data));

	}

	template< class T, class C, class A>
	const typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findNode(const T& data) const {

		// calls private version: findNode(const Node*, const T&)
			// with mRoot (implicitly cast to const)
			// as starting point of search
		return (findNode(mRoot, data));

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::getFirstNode() {

		return mFirst;

	}

	template< class T, class C, class A>
	const typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::getFirstNode() const {

		// calls non-const version of this method
		return ( const_cast<AVL_Tree*>(this)->getFirstNode() );

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::getLastNode() {

		return mLast;

	}

	template< class T, class C, class A>
	const typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::getLastNode() const {

		// calls non-const version of this method
		return ( const_cast<AVL_Tree*>(this)->getLastNode() );

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findNodeNotLessThan(const T& data) {

		// stores the found node here
		Node* nodeFound = NULL;

		// pointer used to traverse the tree starting from root node
		Node* node = mRoot;

		while (node) {

			// node is on left since data is less than node
			if ( mComparator(data, *node->data) ) {

				// if node is less than node found previouly (they're
					// both greater than value), saves it. And through
					// this process the next greater node than data is
					// saved in case a node equivalent to data wasn't
					// found
				if (!nodeFound ||
					mComparator(*node->data, *nodeFound->data))
					nodeFound = node;

				node = node->left;

			}

			// goes to right subtree
			else if (mComparator(*node->data, data))
				node = node->right;

			// node equivalent to data was found
			else {

				// saves it and leaves loop
				nodeFound = node;
				break ;

			}

		}

		return nodeFound;

	}

	template< class T, class C, class A>
	const typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findNodeNotLessThan(const T& data) const {

			// calls non-const version of this method
			return ( const_cast<AVL_Tree*>(this)->
				findNodeNotLessThan(data) );

	}

	/******* private member functions *******/
	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node* 
	AVL_Tree<T, C, A>::makeNewNode(
		const T& data, int height, int balanceFactor,
		Node* parent, Node* left, Node* right){

		Node* newNode = mNodeAllocator.allocate(1);

		mNodeAllocator.construct(newNode,
			Node(data, height, balanceFactor
				, parent, mAllocator, left, right));

		return newNode;

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::destroyNode(Node* node){

		mNodeAllocator.destroy(node);
		
		mNodeAllocator.deallocate(node, 1);

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node* AVL_Tree<T, C, A>::insert
		(Node* node, const T& data, Node** const insertPosition){
		
		if (!node){

			Node* newNode = makeNewNode(data);

			// update tree attributes
			++mNodeCount;
			updateFirst(newNode);
			updateLast(newNode);

			// save newly inserted position
			*insertPosition = newNode;

			return newNode;

		}

		if (mComparator(data, *node->data)){
			node->left = insert(node->left, data, insertPosition);
			node->left->parent = node;
		}
		else if (mComparator(*node->data, data)){
			node->right = insert(node->right, data, insertPosition);
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
				return rotateLeft(node);

			// right left case
			else{

				node->right = rotateRight(node->right);
				return rotateLeft(node);

			}

		}
		// left-heavy
		else if (node->balanceFactor == 2){

			// left left case
			if (node->left->balanceFactor >= 0)
				return rotateRight(node);

			// left right case
			else{

				node->left = rotateLeft(node->left);
				return rotateRight(node);

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

		if (!mFirst || mComparator(*node->data, *mFirst->data))
			mFirst = node;

	}

	template< class T, class C, class A>
	void AVL_Tree<T, C, A>::updateLast(Node *node){

		if (!mLast || mComparator(*mLast->data, *node->data))
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

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::remove(Node* node, const T& data){

			if (!node)
				return NULL;

			// if node is on left of current node
			if (mComparator(data, *node->data))
				node->left = remove(node->left, data);

			// if node is on right of current node
			else if (mComparator(*node->data, data))
				node->right = remove(node->right, data);

			// found node and it has no left child
				// or no right child or no neither child
			else if (!node->left || !node->right){

				// select child that's going to replace node
				Node* replacement = node->left
					? node->left
					: node->right;

				// new mFirst node in case node deleted was
					// the one pointed at by mFirst
				// nextNode() gets the next least significant
					// node after mFirst
				Node* newFirst = mFirst != node
					? mFirst
					: nextNode(mFirst);

				// new mLast node in case node deleted was
					// the one pointed at by mLast
				//previousNode() gets the previous most
					// significant node before mLast
				Node* newLast = mLast != node
					? mLast
					: previousNode(mLast);

				// new parent of node's child (replacement)
				Node* newParent = node->parent;

				destroyNode(node);

				// update mFirst and mLast after removal
				mFirst = newFirst;
				mLast = newLast;

				// updates size of tree
				--mNodeCount;
				
				// checks if replacement is an actual node
					// before setting its parent
				if (replacement)
					replacement->parent = newParent;

				return replacement;

			}

			// found node and it has both of its children
			else {

				// gets node that succeeds node in order
				Node* successor = nextNode(node);

				// copies succesor data into the removed node
					// aka replaces node only by copying
					// its succesor's data into it
				node->changeDataObject(*successor->data);

				// removes successor node after copying it
					// into node
				node->right = remove(node->right, *successor->data);

			}

			updateAVLTraits(node);

			return reBalance(node);

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findLSNode(Node* start) {

			if (!start)
				return start;

			// just keeps digging as far left of the tree as possible
			while (start->left)
				start = start->left;
			
			return start;

	}

	template< class T, class C, class A>
	const typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findLSNode(const Node* start) const {

		// calls non-const version of findLSNode
		return ( const_cast<AVL_Tree*>(this)->findLSNode
			(const_cast<Node*>(start)) );

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findMSNode(Node* start) {

		if (!start)
			return start;

		// just keeps digging as far right of the tree as possible
		while (start->right)
			start = start->right;
		
		return start;

	}

	template< class T, class C, class A>
	const typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findMSNode(const Node* start) const {

		// calls non-const version of findLSNode
		return ( const_cast<AVL_Tree*>(this)->findMSnode
			(const_cast<Node*>(start)) );

	}

	template< class T, class C, class A>
	typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findNode(Node* node, const T& data) {

			while (node) {

				// if data is less significant than current node's
					// data, then go to left subtree
				if (mComparator(data, *node->data))
					node = node->left;

				// if data is more significant than current node's
					// data, then go to right subtree
				else if (mComparator(*node->data, data))
					node = node->right;

				// node found
				else
					break;

			}

			return node;

	}

	template< class T, class C, class A>
	const typename AVL_Tree<T, C, A>::Node*
		AVL_Tree<T, C, A>::findNode
		(const Node* node, const T& data) const {

			// calls non_const version of findNode
			return ( const_cast<AVL_Tree*>(this)->findNode(
				const_cast<Node*>(node), data) );

	}

}

#endif
