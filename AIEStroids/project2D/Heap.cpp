#include "Heap.h"
Heap::Heap()
{
}

Heap::~Heap()
{
}

void Heap::Push(int value)
{
	mData.Add(value);

	int currentIndex = mData.Count() - 1;
	int parentIndex = GetParentIndex(currentIndex);

	while (mData[currentIndex] < mData[parentIndex])
	{
		int temp = mData[currentIndex];
		mData[currentIndex] = mData[parentIndex];
		mData[parentIndex] = temp;

		currentIndex = parentIndex;
		parentIndex = GetParentIndex(currentIndex);
	}
}

int Heap::Pop()
{
	if (Size() == 0)
		return -1;

	int result = mData[0];

	mData[0] = mData[Size() - 1];
	int currentIndex = 0;
	int child1Index = GetChild1Index(currentIndex);
	int child2Index = GetChild2Index(currentIndex);


	//Find smallest child

	int smallestIndex = child1Index;
	if (mData[child2Index] < mData[smallestIndex])
		smallestIndex = child2Index;

	while (mData[smallestIndex] < mData[currentIndex])
	{
		int temp = mData[smallestIndex];
		mData[smallestIndex] = mData[currentIndex];
		mData[currentIndex] = temp;

		currentIndex = smallestIndex;
		child1Index = GetChild1Index(currentIndex);
		child2Index = GetChild2Index(currentIndex);

		smallestIndex = child1Index;
		if (mData[child2Index] < mData[smallestIndex])
			smallestIndex = child2Index;
	}

	mData.RemoveAt(Size() - 1);

	return result;
}

int Heap::Peek()
{
	if (Size() > 0)
		return mData[0];

	return -1;
}

int Heap::Size()
{
	return mData.Count();
}

void Heap::Clear()
{
	mData.Clear();
}

int Heap::GetParentIndex(int index)
{
	return (index - 1) / 2;
}

int Heap::GetChild1Index(int index)
{
	int result = (2 * index) + 1;
	if (result < Size())
		return result;

	//Out of range
	return index;
}

int Heap::GetChild2Index(int index)
{
	int result = (2 * index) + 2;
	if (result < Size())
		return result;

	//Out of range
	return index;
}
