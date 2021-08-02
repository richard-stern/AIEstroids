#pragma once
#include "LinkedList.h"

template <typename T>
class Queue
{
public:

	Queue()
	{
		mData = new LinkedList<T>();
	}

	~Queue()
	{
		delete mData;
		mData = nullptr;
	}

	void Push(T data)
	{
		mData->PushStart(data);
	}

	T& Pop()
	{
		return mData->PopEnd();
	}

	T& Front()
	{
		return mData->PeekEnd();
	}

	int Size()
	{
		return mData->Count();
	}

	bool Empty()
	{
		return mData->Empty();
	}

private:
	LinkedList<T>* mData;
};