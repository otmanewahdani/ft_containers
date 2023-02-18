/* this is an internal file included by List.hpp.
	it contains the implementation of the List template class.*/

#ifndef LIST_TPP
#define LIST_TPP

namespace ft{

	/******* constructor *******/
	// A = Allocator
	template <class T, class A>
	List<T, A>::List()
		: mHead()
		, mBack()
		, mNodeCount()
		, mAllocator() {}

	/******* destructor *******/
	template <class T, class A>
	List<T, A>::~List() { clear(); }

	/******* accessors *******/
	template <class T, class A>
	T& List<T, A>::front() { return mHead->data; }

	template <class T, class A>
	std::size_t List<T, A>::size() { return mNodeCount; }

	template <class T, class A>
	bool List<T, A>::empty() { return (!mNodeCount); }

	/******* modifiers *******/
	template <class T, class A>
	void List<T, A>::add_back(const T& data) {

		Node* newNode = makeNewNode(data);

		if (!mHead)
			mHead = newNode;

		if (mBack)
			mBack->next = newNode;

		mBack = newNode;

		mNodeCount++;

	}

	template <class T, class A>
	void List<T, A>::pop_front() {

		Node* tmp = mHead;

		mHead = mHead->next;

		--mNodeCount;

		if (!mNodeCount)
			mBack = mHead;

		destroyNode(tmp);

	}

	template <class T, class A>
	void List<T, A>::clear() {

		Node* tmp;

		while (mHead){

			tmp = mHead;
			mHead = mHead->next;
			destroyNode(tmp);

		}

		mBack = NULL;
		mNodeCount = 0;
	
	}

	/******* memory management *******/
	template <class T, class A>
	typename List<T, A>::Node*
		List<T, A>::makeNewNode(const T& data){

			Node* newNode = mAllocator.allocate(1);

			mAllocator.construct(newNode, Node(data));

			return newNode;

	}

	template <class T, class A>
	void List<T, A>::destroyNode(Node* node){

		mAllocator.destroy(node);

		mAllocator.deallocate(node, 1);

	}

}

#endif
