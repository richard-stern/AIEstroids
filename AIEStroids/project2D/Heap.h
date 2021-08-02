#pragma once
#include "DynamicArray.h"
class Heap
{
public:
	Heap();
	~Heap();

	void Push(int value);
	int Pop();
	int Peek();
	
	int Size();
	void Clear();

private:

	int GetParentIndex(int index);
	int GetChild1Index(int index);
	int GetChild2Index(int index);

	DynamicArray<int> mData;

};

