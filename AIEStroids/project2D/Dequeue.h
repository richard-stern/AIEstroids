#pragma once
#include "DoubleLinkedList.h"

template <typename T>
class Dequeue
{
public:
	Dequeue()
	{
		mData = new DoubleLinkedList<T>();
	}

	~Dequeue()
	{
		delete mData;
		mData = nullptr;
	}

	void PushStart(T data)
	{
		mData->PushStart(data);
	}

	void PushEnd(T data)
	{
		mData->PushEnd(data);
	}

	T& PopStart()
	{
		return mData->PopStart();
	}

	T& PopEnd()
	{
		return mData->PopEnd();
	}

	T& Front()
	{
		return mData->PeekFront();
	}

	T& Back()
	{
		return mData->PeekBack();
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
	DoubleLinkedList<T>* mData;
};