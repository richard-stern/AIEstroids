#pragma once
#include "DynamicArray.h"
template <typename T>
class Stack
{
public:

	Stack()
	{
		mData = new DynamicArray<T>();
	}

	~Stack()
	{
		delete mData;
		mData = nullptr;
	}

	void Push(T data)
	{
		mData->InsertEnd(data);
		mTop++;
	}

	T& Pop()
	{
		T data = mData->GetAt(mData->Count() - 1);
		mData->Remove(data);
		mTop--;
		return data;
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
	int mTop = -1;

	DynamicArray<T>* mData;
};