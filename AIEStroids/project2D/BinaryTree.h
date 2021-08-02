#pragma once
#include "BinaryTreeNode.h"
#include "DynamicArray.h"
enum  SearchType
{
	DepthFirstPreOrder,
	DepthFirstPostOrder,
	DepthFirstInOrder,
	BreadthFirst
};
template <typename T>
class BinaryTree
{
public:
	BinaryTree()
	{
		mTop = nullptr;
	}

	~BinaryTree()
	{
		if (mTop)
			delete mTop;
	}

	void Insert(T data)
	{
		BinaryTreeNode<T>* node = new BinaryTreeNode<T>();
		node->mData = data;
		mCount++;

		if (!mTop)
			mTop = node;
		else
		{
			bool placed = false;
			BinaryTreeNode<T>* compNode = mTop;
			while (!placed)
			{
				if (compNode)
				{
					if (node->mData > compNode->mData) //Right Side
					{
						if (compNode->mRight)
							compNode = compNode->mRight;
						else
						{
							placed = true;
							compNode->mRight = node;
						}
					}
					else if (node->mData < compNode->mData) //Left Side
					{
						if (compNode->mLeft)
							compNode = compNode->mLeft;
						else
						{
							placed = true;
							compNode->mLeft = node;
						}
					}
				}
			}
		}
	}

	void Remove(T data)
	{
		BinaryTreeNode<T>* node;
		BinaryTreeNode<T>* nodeParent;

		node = FindNode(data);
		if (node)
			nodeParent = FindParentNode(node);
		else
			return;
		mCount--;
		//Delete Leaf
		if (!node->mLeft && !node->mRight)
		{
			if (nodeParent != nullptr)
			{
				if (nodeParent->mLeft == node)
					nodeParent->mLeft = nullptr;
				if (nodeParent->mRight == node)
					nodeParent->mRight = nullptr;
			}
			if (mTop == node)
			{
				mTop = nullptr;
			}
			delete node;

		}
		//Delete node with one child
		else if (GetChildCount(node) == 1)
		{
			BinaryTreeNode<T>* nodeChild = nullptr;

			if (node->mLeft)
				nodeChild = node->mLeft;
			if (node->mRight)
				nodeChild = node->mRight;

			if (nodeParent != nullptr)
			{
				if (nodeParent->mLeft == node)
					nodeParent->mLeft = nodeChild;
				if (nodeParent->mRight == node)
					nodeParent->mRight = nodeChild;
			}

			if (node == mTop)
			{
				mTop = nodeChild;
			}
		}
		//Delete Child with two children
		else
		{
			FindSmallestRightSideChild(node);

		}
	}

	int GetChildCount(BinaryTreeNode<T>* node)
	{
		int count = 0;
		if (node->mLeft)
			count++;
		if (node->mRight)
			count++;
		return count;
	}

	void FindSmallestRightSideChild(BinaryTreeNode<T>* startNode)
	{
		BinaryTreeNode<T>* smallestNode = startNode;
		if (smallestNode->mRight)
		{
			smallestNode = smallestNode->mRight;
			while (smallestNode->mLeft)
			{
				smallestNode = smallestNode->mLeft;
			}
		}

		Remove(smallestNode->mData);
		startNode->mData = smallestNode->mData;

	}

	int Count()
	{
		return mCount;
	}

	BinaryTreeNode<T>* FindNode(T data)
	{
		BinaryTreeNode<T>* compNode = mTop;
		while (true)
		{
			if (compNode)
			{
				if (data == compNode->mData)
					return compNode;

				if (compNode->mLeft && data < compNode->mData)
				{
					compNode = compNode->mLeft;
				}

				else if (compNode->mRight && data > compNode->mData)
				{
					compNode = compNode->mRight;
				}
				else
					return nullptr;
			}
			else
				return nullptr;
		}
	}

	BinaryTreeNode<T>* FindParentNode(BinaryTreeNode<T>* node)
	{
		bool found = false;
		BinaryTreeNode<T>* compNode = mTop;
		if (mTop == node)
			return nullptr;
		while (!found)
		{
			if (compNode)
			{
				if (compNode->mLeft == node || compNode->mRight == node)
					return compNode;

				if (node->mData < compNode->mData)
				{
					compNode = compNode->mLeft;
				}

				else if (node->mData > compNode->mData)
				{
					compNode = compNode->mRight;
				}

			}
			else return nullptr;
		}

	}

	DynamicArray<T>* ToList(SearchType searchType)
	{
		DynamicArray<T>* orderedData = new DynamicArray<T>;
		switch (searchType)
		{
		case SearchType::DepthFirstInOrder:
			mTop->Inorder(*orderedData);

		case SearchType::DepthFirstPostOrder:
			mTop->Postorder(*orderedData);

		case SearchType::DepthFirstPreOrder:
			mTop->Preorder(*orderedData);

		case SearchType::BreadthFirst:
			BreadthFirstToList(*orderedData);

		default:
			break;
		}

		return orderedData;
	}

private:

	void BreadthFirstToList(DynamicArray<T>& orderedData)
	{
		Queue<BinaryTreeNode<T>*> queue;
		queue.Push(mTop);
		while (!queue.Empty())
		{
			BinaryTreeNode<T>* pointer = queue.Pop();
			orderedData.InsertEnd(pointer->mData);
			if (pointer->mLeft)
				queue.Push(pointer->mLeft);
			if (pointer->mRight)
				queue.Push(pointer->mRight);
		}
	}

	BinaryTreeNode<T>* mTop;
	int mCount = 0;
};