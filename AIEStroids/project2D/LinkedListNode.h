#pragma once
template <typename T>
struct LinkedListNode
{
	LinkedListNode()
	{
		mNext = nullptr;
	}

	LinkedListNode(const T& data, LinkedListNode* next = nullptr)
	{
		mData = data;
		mNext = next;
	}

	T mData;
	LinkedListNode<T>* mNext;
};