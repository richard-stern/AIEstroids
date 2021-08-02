#pragma once
#include<memory>
template <typename T>
class DynamicArray
{

public:
	DynamicArray(int initializeSize = 1)
	{
		mData = new T[initializeSize];
		mCapacity = initializeSize;
		mUsed = 0;
	}

	~DynamicArray()
	{
		if (mData)
		{
			delete[] mData;
			mData = nullptr;
		}
	}

	void InsertStart(T data)
	{
		InsertAt(0, data);
	}

	void InsertEnd(T data)
	{
		InsertAt(mUsed, data);
	}

	void Add(T data)
	{
		InsertAt(mUsed, data);
	}

	void InsertAt(int index, T data)
	{
		if (index > mUsed || index < 0)
			return;

		CheckForResize();

		//Insert at end
		if (index == mUsed)
		{
			mData[index] = data;
		}
		else
		{
			//Shift all data to right
			for (int i = mUsed - 1; i > index; i--)
			{
				mData[i] = mData[i - 1];
			}

			mData[index] = data;
		}
		mUsed++;
	}

	void RemoveAt(int index)
	{
		if (index > mUsed || index < 0)
			return;

		//Insert at end
		if (index != mUsed)
		{

			//Shift all data to right
			for (int i = index; i < mUsed; i++)
			{
				mData[i] = mData[i + 1];
			}


		}
		mUsed--;
	}

	void Remove(T data)
	{
		RemoveAt(GetIndexOf(data));
	}


	int GetIndexOf(T data)
	{
		for (int i = 0; i < mUsed; i++)
		{
			if (mData[i] == data)
				return i;
		}

		return -1;
	}

	

	T& Front()
	{
		return mData[0];
	}

	T& Back()
	{
		return mData[mUsed - 1];
	}

	T& GetAt(int index)
	{
		return mData[index];
	}

	T& operator[](int index)
	{
		return mData[index];
	}

	int Count()
	{
		return mUsed;
	}

	int Capacity()
	{
		return mCapacity;
	}

	bool Empty()
	{
		return (mUsed == 0);
	}

	void Clear()
	{
		mUsed = 0;
	}

	bool Contains(T data)
	{
		for (int i = 0; i < mUsed; i++)
		{
			if (mData[i] == data)
				return true;
		}

		return false;
	}

	void ShrinkToFit()
	{
		mCapacity = mUsed;
		Resize();
	}

private:

	void CheckForResize()
	{
		if (mUsed >= mCapacity)
		{
			mCapacity *= 2;
			Resize();
		}
	}

	void CheckResizeToFit(int amount)
	{
		if (mCapacity <= mUsed + amount)
		{
			mCapacity += amount;
			Resize();
		}
	}

	void Resize()
	{
		T* newData = new T[mCapacity];
		memcpy(newData, mData, sizeof(T) * mUsed);

		delete[] mData;
		mData = newData;
	}


	T* mData;
	int mCapacity;
	int mUsed;
};