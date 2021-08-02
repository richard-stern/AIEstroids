#pragma once
template <typename T>
struct DoubleLinkedListNode
{
	DoubleLinkedListNode()
	{
		mNext = nullptr;
		mPrev = nullptr;
	}

	DoubleLinkedListNode(const T& data, DoubleLinkedListNode* next = nullptr, DoubleLinkedListNode* prev = nullptr)
	{
		mData = data;
		mNext = next;
		mPrev = prev;

		if (next)
			next->mPrev = this;
	}

	T mData;
	DoubleLinkedListNode<T>* mNext;
	DoubleLinkedListNode<T>* mPrev;
};