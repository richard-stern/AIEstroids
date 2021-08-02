#pragma once
#include "DoubleLinkedListNode.h"
template <typename T>
class DoubleLinkedList
{

public:
	DoubleLinkedList() { mHead = mTail = nullptr; }

	~DoubleLinkedList()
	{
		for (DoubleLinkedListNode<T>* p; !Empty();)
		{
			p = mHead->mNext;
			delete mHead;
			mHead = p;
		}
	}

	void PushStart(const T& data)
	{
		mHead = new DoubleLinkedListNode<T>(data, mHead);

		if (mTail == nullptr)
			mTail = mHead;

		mCount++;
	}

	void PushEnd(const T& data)
	{
		if (mTail != nullptr)
		{
			mTail = new DoubleLinkedListNode<T>(data, nullptr, mTail);
			mTail->mPrev->mNext = mTail;
		}
		else mHead = mTail = new DoubleLinkedListNode<T>(data);

		mCount++;
	}

	void InsertAt(int index, const T& data)
	{
		if (index < 0 || index >= mCount)
			return;
		else if (index == 0)
			PushStart(data);
		else if (index == mCount - 1)
			PushEnd(data);
		else
		{
			DoubleLinkedListNode<T>* prev = mHead;

			for (int i = 0; i < index - 1; i++)
			{
				prev = prev->mNext;
			}

			prev->mNext = new DoubleLinkedListNode<T>(data, prev->mNext, prev);
			mCount++;
		}
	}

	T& GetAt(int index)
	{
		if (index == 0)
			return mHead->mData;
		else if (index == mCount - 1)
			return mTail->mData;

		DoubleLinkedListNode<T>* temp = mHead;
		for (int i = 0; i < index; i++)
		{
			temp = temp->mNext;
		}
		return temp->mData;
	}


	DoubleLinkedListNode<T>* GetNodeAt(int index)
	{
		DoubleLinkedListNode<T>* temp = mHead;
		for (int i = 0; i < index; i++)
		{
			temp = temp->mNext;
		}
		return temp;
	}

	DoubleLinkedListNode<T>* GetNode(const T& data)
	{
		DoubleLinkedListNode<T>* temp = mHead;
		for (int i = 0; i < mCount; i++)
		{
			if (temp->mData != data)
				temp = temp->mNext;
			else
				return temp;
		}
		return nullptr;
	}

	T& PopStart()
	{
		T data = mHead->mData;
		if (mHead == mTail)//Only one node in the list
		{
			mHead = mTail = nullptr;
		}
		else //More than one node in the list
		{
			mHead = mHead->mNext;
			mHead->mPrev = nullptr;
		}

		mCount--;
		return data;
	}

	T& PopEnd()
	{
		T data = mTail->mData;
		if (mHead == mTail) //Only one node in the list
		{
			delete mHead;
			mHead = mTail = nullptr;
		}
		else //More than one node in the list
		{
			DoubleLinkedListNode<T>* temp = mTail->mPrev; //Node before the tail

			delete mTail;
			mTail = temp;
			mTail->mNext = nullptr;


		}
		mCount--;
		return data;
	}

	void Remove(const T& data)
	{
		if (mCount > 0) //Check list isn't empty
		{
			if (mHead == mTail && data == mHead->mData) //If only one node in the list
			{
				delete mHead;
				mHead = mTail = nullptr;
				mCount--;
			}
			else if (data == mHead->mData) //If more than one node and node is head
			{
				DoubleLinkedListNode<T>* temp = mHead;
				mHead = mHead->mNext;
				mHead->mPrev = nullptr;
				delete temp;
				mCount--;
			}
			else //If more than one node and it's not the head
			{
				DoubleLinkedListNode<T>* temp = GetNode(data);

				if (temp)
				{
					temp->mPrev->mNext = temp->mNext;
					temp->mNext->mPrev = temp->mPrev;
					if (temp == mTail)
					{
						mTail = temp->mPrev;
					}
					delete temp;
					mCount--;
				}
			}
		}
	}

	void RemoveAt(int index)
	{
		if (index < 0 || index >= mCount)
			return;

		//Check if index is closer to start or end;
		int distEnd = mCount - index;

		DoubleLinkedListNode<T>* temp;

		if (distEnd >= index)
		{
			temp = mHead;
			for (int i = 0; i < index; i++)
			{
				temp = temp->mNext;
			}
		}
		else
		{
			temp = mTail;
			for (int i = mCount; i > index; i--)
			{
				temp = temp->mPrev;
			}
		}

		if (temp)
		{
			Remove(temp->mData);

		}
	}

	T& PeekFront()
	{
		return mHead->mData;
	}

	T& PeekBack()
	{
		return mTail->mData;
	}

	bool Contains(const T& data)
	{
		return GetNode(data) != nullptr;
	}

	bool Empty()
	{
		return mHead == nullptr;
	}

	int Count()
	{
		return mCount;
	}

	void InsertionSort()
	{
		for (int i = 1; i < mCount; i++)
		{
			DoubleLinkedListNode<T>* key = GetNodeAt(i);
			int j = i - 1;
			DoubleLinkedListNode<T>* prev = GetNodeAt(j);

			//Assuming use of ints
			while (j >= 0 && prev->mData > key->mData)
			{
				Swap(GetNodeAt(j + 1), GetNodeAt(j));
				j--;
				prev = GetNodeAt(j);
			}

		}
	}

	void Swap(DoubleLinkedListNode<T>* nodeA, DoubleLinkedListNode<T>* nodeB)
	{
		if (nodeA == nodeB)
			return;

		DoubleLinkedListNode<T>* nodeAPrev = nodeA->mPrev;
		DoubleLinkedListNode<T>* nodeANext = nodeA->mNext;

		DoubleLinkedListNode<T>* nodeBPrev = nodeB->mPrev;
		DoubleLinkedListNode<T>* nodeBNext = nodeB->mNext;

		if (nodeAPrev)
			nodeAPrev->mNext = nodeB;

		if (nodeBPrev)
			nodeBPrev->mNext = nodeA;

		if (nodeANext)
			nodeANext->mPrev = nodeB;

		if (nodeBNext)
			nodeBNext->mPrev = nodeA;

		nodeB->mNext = nodeA->mNext;
		nodeB->mPrev = nodeA->mPrev;

		if (nodeA != nodeBPrev)
			nodeA->mPrev = nodeBPrev;
		else
			nodeA->mPrev = nodeB;

		if (nodeA != nodeBNext)
			nodeA->mNext = nodeBNext;
		else
			nodeA->mNext = nodeB;

		if (nodeA == mHead)
		{
			mHead = nodeB;
		}
		else if (nodeB == mHead)
		{
			mHead = nodeA;
		}

		if (nodeA == mTail)
		{
			mTail = nodeB;
		}
		else if (nodeB == mTail)
		{
			mTail = nodeA;
		}
	}

private:

	int mCount = 0;
	DoubleLinkedListNode<T>* mHead;
	DoubleLinkedListNode<T>* mTail;
};