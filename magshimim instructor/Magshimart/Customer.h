#pragma once
#include"Item.h"
#include<set>

class Customer
{
public:
	Customer(string);
	~Customer() = default;
	double totalSum() const;//returns the total sum for payment
	void addItem(Item);//add item to the set
	void removeItem(Item);//remove item from the set

	//get and set functions
	string getName() const;

	void setName(string name);

	set<Item> getItems();


private:
	string _name;
	set<Item> _items;


};
