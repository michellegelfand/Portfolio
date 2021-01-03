
#pragma once


#include <string>
#include <iostream>

/*
BSnode class based on templates

*/

template <typename T>
class TBSNode
{
public:
	//inits a junction
	TBSNode(T data);

	//deep copy of another tree
	TBSNode(const TBSNode& other);
	~TBSNode();

	TBSNode* getLeft() const;
	TBSNode* getRight() const;
	bool isLeaf() const;
	void insert(T value);
	bool search(T value) const;
	T getData() const;
	TBSNode& operator=(const TBSNode& other);

	void printNodesConsole() const;

	//assumes input node is a direct ancestor of curr node
	//returns -1 if not
	int getCurrNodeDistFromInputNode(const TBSNode* ancestor) const;
	int getDepth(const TBSNode& root) const;
	int getHeight() const;
private:
	T _data;
	TBSNode* _left;
	TBSNode* _right;
	int _count;
};

template <typename T>
TBSNode<typename T>::TBSNode(T data)
	:_data(data), _left(nullptr), _right(nullptr), _count(1)
{
}

template <typename T>
TBSNode<typename T>::TBSNode(const TBSNode& other)
{
	//DEEP COPY
	_data = other.getData();

	if (other.getRight() != nullptr)
	{
		_right = new TBSNode(*other.getRight());
	}
	else
	{
		_right = nullptr;
	}

	if (other.getLeft() != nullptr)
	{
		_left = new TBSNode(*other.getLeft());
	}
	else
	{
		_left = nullptr;
	}


}
template <typename T>
TBSNode<typename T>* TBSNode<typename T>::getLeft() const
{
	return _left;
}
template <typename T>
TBSNode<typename T>* TBSNode<typename T>::getRight() const
{
	return _right;
}

template <typename T>
bool TBSNode<typename T>::isLeaf() const
{
	return (_left == nullptr && _right == nullptr);
}
template <typename T>
TBSNode<typename T>::~TBSNode()
{
	if (_right != nullptr)
	{
		delete _right;
	}
	if (_left != nullptr)
	{
		delete _left;
	}
}
template <typename T>
void TBSNode<typename T>::insert(T value)
{
	if(_data == value)
	{
		_count++;
	}
	else if (_data < value)
	{
		if (_right == nullptr)
		{
			_right = new TBSNode(value);
		}
		else
		{
			_right->insert(value);
		}
	}
	else if (_data > value)
	{
		if (_left == nullptr)
		{
			_left = new TBSNode(value);
		}
		else
		{
			_left->insert(value);
		}
	}
	
}
template <typename T>
bool TBSNode<typename T>::search(T value) const
{
	bool found = false;

	if (_data == value)
	{
		found = true;
	}
	else if (_data >= value)
	{
		if (_left)
		{
			found = _left->search(value);
		}
	}
	else if (_right)
	{
		found = _right->search(value);
	}

	return found;
}
template <typename T>
T TBSNode<typename T>::getData() const
{
	return _data;
}
template <typename T>
TBSNode<typename T>& TBSNode<typename T>::operator=(const TBSNode<typename T>& other)
{
	//DEEP COPY

	if (_right)
	{
		delete _right;
	}
	if (_left)
	{
		delete _left;
	}

	_data = other._data;
	_right = nullptr;
	_left = nullptr;

	if (other._right)
	{
		_right = new TBSNode(*other._right);
	}
	if (other._left)
	{
		_left = new TBSNode(*other._left);
	}


	_count = other._count;
	return *this;
}
template <typename T>
void TBSNode<typename T>::printNodesConsole() const
{
	if (_left != nullptr)
	{
		_left->printNodesConsole();
	}
	else
	{
		std::cout << "# ";
	}
	std::cout << _data << " ";
	
	if (_right != nullptr)
	{
		_right->printNodesConsole();
	}
	else
	{
		std::cout << "# ";
	}

	

}


template <typename T>
int TBSNode<typename T>::getCurrNodeDistFromInputNode(const TBSNode<typename T>* ancestor) const
{
	if (this == ancestor)
	{
		return 0;
	}
	else if (ancestor->_data >= this->_data)
	{
		if (ancestor->_left)
		{
			return getCurrNodeDistFromInputNode(ancestor->_left) + 1;
		}

	}
	else if (ancestor->_right)
	{
		return getCurrNodeDistFromInputNode(ancestor->_right) + 1;
	}

	return -1;

}
template <typename T>
int TBSNode<typename T>::getDepth(const TBSNode<typename T>& root) const
{
	return getCurrNodeDistFromInputNode(&root);
}
template <typename T>
int TBSNode<typename T>::getHeight() const
{
	int height;

	// leaf height defined as 1
	if (isLeaf())
	{
		height = 1;
	}
	else
	{
		int rightHeight = 0;
		int leftHeight = 0;

		//gets called recursively adding +1 for each node passed

		// calculate the height of right sub tree 
		if (_right)
		{
			rightHeight = _right->getHeight() + 1;
		}
		// calculate the height of left sub tree 
		if (_left)
		{
			leftHeight = _left->getHeight() + 1;
		}

		// check which sub tree is higher
		height = (leftHeight > rightHeight ? leftHeight : rightHeight);

	}

	return height;

}
