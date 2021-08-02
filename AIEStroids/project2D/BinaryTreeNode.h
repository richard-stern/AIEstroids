#pragma once
#include "DynamicArray.h"
template <typename T>
struct BinaryTreeNode
{

	void Preorder(DynamicArray<T>& orderedData)
	{
		orderedData.InsertEnd(mData);

		if (mLeft)
			mLeft->Preorder(orderedData);
		if (mRight)
			mRight->Preorder(orderedData);
	}

	void Postorder(DynamicArray<T>& orderedData)
	{
		if (mLeft)
			mLeft->Postorder(orderedData);
		if (mRight)
			mRight->Postorder(orderedData);

		orderedData.InsertEnd(mData);
	}

	void Inorder(DynamicArray<T>& orderedData)
	{
		if (mLeft)
			mLeft->Inorder(orderedData);

		orderedData.InsertEnd(mData);

		if (mRight)
			mRight->Inorder(orderedData);

	}

	T mData;

	BinaryTreeNode<T>* mLeft = nullptr;
	BinaryTreeNode<T>* mRight = nullptr;
};