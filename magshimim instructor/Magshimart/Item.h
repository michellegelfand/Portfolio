#pragma once
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

class Item
{
public:
	Item(std::string, std::string, double);
	~Item() = default;

	double totalPrice() const; //returns _count*_unitPrice
	bool operator <(const Item& other) const; //compares the _serialNumber of those items.
	bool operator >(const Item& other) const; //compares the _serialNumber of those items.
	bool operator ==(const Item& other) const; //compares the _serialNumber of those items.

	//get and set functions
	std::string getName() const;
	std::string getSerialNumber() const;
	int getCount() const;
	double getUnitPrice() const;


	void setName(std::string name);
	void setSerialNumber(std::string serialNum);
	void setCount(int count);//works if count=>1
	void setUnitPrice(double price);//works if price>0

private:
	std::string _name;
	std::string _serialNumber; //consists of 5 numbers
	int _count; //default is 1, can never be less than 1!
	double _unitPrice; //always bigger than 0!

};