#include "Item.h"

const int DEFAULT_COUNT = 1;

Item::Item(std::string name, std::string serialNum, double unitPrice)
	:_name(name), _serialNumber(serialNum), _unitPrice(unitPrice), _count(DEFAULT_COUNT)
{

}

double Item::totalPrice() const
{
	return _unitPrice * _count;
}

bool Item::operator <(const Item& other) const//compares the _serialNumber of those items.
{
	int thisSerialNum = atoi(_serialNumber.c_str());
	int otherSerialNum = atoi(other.getSerialNumber().c_str());

	return (thisSerialNum < otherSerialNum);
}
bool Item::operator >(const Item& other) const   //compares the _serialNumber of those items.
{
	int thisSerialNum = atoi(_serialNumber.c_str());
	int otherSerialNum = atoi(other.getSerialNumber().c_str());

	return (thisSerialNum > otherSerialNum);

}
bool Item::operator ==(const Item& other) const //compares the _serialNumber of those items.
{
	int thisSerialNum = atoi(_serialNumber.c_str());
	int otherSerialNum = atoi(other.getSerialNumber().c_str());

	return (thisSerialNum == otherSerialNum);
}

string Item::getSerialNumber() const
{
	return _serialNumber;
}


std::string Item::getName() const
{
	return _name;
}

int Item::getCount() const
{
	return _count;
}
double Item::getUnitPrice() const
{
	return _unitPrice;
}

void Item::setName(std::string name)
{
	_name = name;
}
void Item::setSerialNumber(std::string serialNum)
{
	_serialNumber = serialNum;
}
void Item::setCount(int count)
{
	if (count >= 1)
	{
		_count = count;
	}
}

void Item::setUnitPrice(double price)
{
	if (price > 0)
	{
		_unitPrice = price;
	}
}


