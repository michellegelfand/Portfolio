#include "BSNode.h"

BSNode::BSNode(std::string data)
	:_data(data), _left(nullptr), _right(nullptr), _count(1)
{
}

BSNode::BSNode(const BSNode& other)
{
	//DEEP COPY
	_data = other.getData();

	if (other.getRight() != nullptr)
	{
		_right = new BSNode(*other.getRight());
	}
	else
	{
		_right = nullptr;
	}

	if (other.getLeft() != nullptr)
	{
		_left = new BSNode(*other.getLeft());
	}
	else
	{
		_left = nullptr;
	}

	
}

BSNode* BSNode::getLeft() const
{
	return _left;
}

BSNode* BSNode::getRight() const
{
	return _right;
}

bool BSNode::isLeaf() const
{
	return (_left == nullptr && _right == nullptr);
}

BSNode::~BSNode()
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

void BSNode::insert(std::string value)
{ 
	if(value == _data)
	{
		_count++;
	}
	//if compare returns bigger than 0 my string is "bigger"
	else if (_data.compare(value) < 0)
	{
		if (_right == nullptr)
		{
			_right = new BSNode(value);
		}
		else
		{
			_right->insert(value);
		}
	}
	else if (_data.compare(value) > 0)
	{
		if (_left == nullptr)
		{
			_left  = new BSNode(value);
		}
		else
		{
			_left->insert(value);
		}
	}
	
}

bool BSNode::search(std::string value) const
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

std::string BSNode::getData() const
{
	return _data;
}

BSNode& BSNode::operator=(const BSNode& other)
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
		_right = new BSNode(*other._right);
	}
	if (other._left)
	{
		_left = new BSNode(*other._left);
	}

	
	_count = other._count;
	return *this;
}

void BSNode::printNodesConsole() const
{
	//print inorder traversal
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



int BSNode::getCurrNodeDistFromInputNode(const BSNode* ancestor) const
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

int BSNode::getDepth(const BSNode& root) const
{
	return getCurrNodeDistFromInputNode(&root);
}

int BSNode::getHeight() const
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
			rightHeight = _right->getHeight() +1;
		}
		// calculate the height of left sub tree 
		if (_left)
		{
			leftHeight = _left->getHeight()+1;
		}

		// check which sub tree is higher
		height = (leftHeight > rightHeight ? leftHeight : rightHeight);

	}

	return height;

}