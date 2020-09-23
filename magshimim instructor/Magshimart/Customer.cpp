#include "Customer.h"

Customer::Customer(string name)
	:_name(name)
{

}

double Customer::totalSum() const
{
	double totalSum = 0;

	for (Item item : _items)
	{
		totalSum += item.totalPrice();
	}

	return totalSum;
}
	
void Customer::addItem(Item toAdd)//add item to the set
{
	set<Item>::iterator i = _items.find(toAdd);
	if (i == _items.end())
	{
		_items.insert(toAdd);
		return;
	}

	toAdd.setCount(toAdd.getCount() + i->getCount());

	_items.erase(i);//set members are read only, therefor need to replace member with item with new count
	_items.insert(toAdd);
}

void Customer::removeItem(Item toRemove)//remove item from the set
{
	set<Item>::iterator i = _items.find(toRemove);
	if (i == _items.end())
	{
		cout << "item not found in shopping cart\n";
		return;
	}

	if (i->getCount() == 1)
	{
		_items.erase(i);
		return;
	}
	 

	Item toReplace = Item(i->getName(), i->getSerialNumber(), i->getUnitPrice());
	toReplace.setCount(i->getCount() - 1);
	_items.erase(toRemove);
	_items.insert(toReplace);

}


string Customer::getName() const
{
	return _name;
}

set<Item> Customer::getItems()
{
	return _items;
}

void Customer::setName(string name)
{
	
	_name = name;
}



