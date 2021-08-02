#pragma once
#include "LinkedListNode.h"
template <typename T>
class LinkedList
{

public:
	LinkedList() { mHead = mTail = nullptr; }

	~LinkedList()
	{
		for (LinkedListNode<T>* p; !Empty();)
		{
			p = mHead->mNext;
			delete mHead;
			mHead = p;
		}
	}

	void PushStart(const T& data)
	{
		mHead = new LinkedListNode<T>(data, mHead);

		if (mTail == nullptr)
			mTail = mHead;

		mCount++;
	}

	void PushEnd(const T& data)
	{
		if (mTail != nullptr)
		{
			mTail->mNext = new LinkedListNode<T>(data, nullptr);
			mTail = mTail->mNext;
		}
		else
		{
			mHead = mTail = new LinkedListNode<T>(data, nullptr);
		}

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
			LinkedListNode<T>* prev = mHead;

			for (int i = 0; i < index - 1; i++)
			{
				prev = prev->mNext;
			}

			prev->mNext = new LinkedListNode<T>(data, prev->mNext);
			mCount++;
		}
	}

	T& PopStart()
	{
		T data = mHead->mData;
		if (mHead == mTail) //Only one node in the list
			mHead = mTail = nullptr;
		else
			mHead = mHead->mNext;
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
			LinkedListNode<T>* temp; //Find the node before the tail
			for (temp = mHead; temp->mNext != mTail; temp = temp->mNext);

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
				LinkedListNode<T>* temp = mHead;
				mHead = mHead->mNext;
				delete temp;
				mCount--;
			}
			else //If more than one node and its not the head
			{
				LinkedListNode<T>* prev;
				LinkedListNode<T>* temp;

				for (prev = mHead, temp = mHead->mNext;
					temp != nullptr && !(temp->mData == data);
					prev = prev->mNext, temp = temp->mNext);

				if (temp)
				{
					prev->mNext = temp->mNext;
					if (temp == mTail)
					{
						mTail = prev;
					}
					delete temp;
					mCount--;
				}
			}
		}
	}

	void RemoveAt(int index)
	{
		LinkedListNode<T>* temp = mHead;

		for (int i = 0; i < index; i++)
		{
			temp = temp->mNext;
		}

		Remove(temp->mData);
	}

	T& PeekStart()
	{
		return mHead->mData;
	}

	T& PeekEnd()
	{
		return mTail->mData;
	}

	T& Front()
	{
		return mHead->mData;
	}

	T& Back()
	{
		return mTail->mData;
	}

	T& GetAt(int index)
	{
		if (index == 0)
			return mHead->mData;
		else if (index == mCount - 1)
			return mTail->mData;

		LinkedListNode<T>* temp = mHead;
		for (int i = 0; i < index; i++)
		{
			temp = temp->mNext;
		}
		return temp->mData;
	}

	bool Contains(const T& data) const
	{
		LinkedListNode<T>* temp;

		for (temp = mHead; temp != nullptr && !(temp->mData == data); temp = temp->mNext);
		return temp != nullptr;
	}

	bool Empty()
	{
		return mHead == nullptr;
	}

	int Count()
	{
		return mCount;
	}

private:

	int mCount = 0;
	LinkedListNode<T>* mHead;
	LinkedListNode<T>* mTail;
};
