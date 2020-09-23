#include<map>
#include <unordered_map>
#include <set>


#include"Customer.h"
#include "Item.h"

#define MILK "00001"
#define COOKIES "00002"
#define BREAD "00003"
#define CHOCOLATE "00004"
#define CHEESE "00005"
#define RICE "00006"
#define FISH "00007"
#define CHICKEN "00008"
#define CUCUMBER "00009"
#define TOMATO "00010"


const int NEW_CUSTOMER = 1;
const int EXISTING_CUSTOMER = 2;
const int PRINT_HIGHEST_PAYER = 3;
const int EXIT = 4;



void printForSale(unordered_map<string, Item> items);

void printPurchases(std::map<string, Customer>abcCustomers, string inputStr);

int main()
{

	map<string, Customer> abcCustomers;
	
	//For items I chose unordered map to access by key. I considered using unordered_set but the key then would have to
	//be the item itself which caused a problem. Unordered_map is good because it has an insert and access
	//complexity of O(1) and because sorting is unnecessary here.
	
	unordered_map<string,Item> items;

	items.insert(std::map< string, Item >::value_type(MILK, Item("Milk", MILK, 5.3)));
	items.insert(std::map< string, Item >::value_type(COOKIES, Item("Cookies", COOKIES, 12.6)));
	items.insert(std::map< string, Item >::value_type(BREAD, Item("bread", BREAD, 8.9)));
	items.insert(std::map< string, Item >::value_type(CHOCOLATE, Item("chocolate", CHOCOLATE, 7.00)));
	items.insert(std::map< string, Item >::value_type(CHEESE, Item("cheese", CHEESE, 15.3)));
	items.insert(std::map< string, Item >::value_type(RICE, Item("rice", RICE, 6.2)));
	items.insert(std::map< string, Item >::value_type(FISH, Item("fish", FISH, 31.65)));
	items.insert(std::map< string, Item >::value_type(CHICKEN, Item("chicken", CHICKEN, 25.99)));
	items.insert(std::map< string, Item >::value_type(CUCUMBER, Item("cucumber", CUCUMBER, 1.21)));
	items.insert(std::map< string, Item >::value_type(TOMATO, Item("tomato", TOMATO, 2.32)));


	int inputNum;
	string inputStr;

	while (1)
	{
		cout << "Welcome to MagshiMart!" << endl;
		cout << "1. if you are a new customer" << endl;
		cout << "2. to update existing customer's items" << endl;
		cout << "3. to print highest paying customer" << endl;
		cout << "4. to exit" << endl;

		cin >> inputNum;

		switch (inputNum)
		{
		case NEW_CUSTOMER:
			cout << "please enter new customer name\n";
			cin >> inputStr;

			if (abcCustomers.find(inputStr) != abcCustomers.end())//if name taken
			{
				cout << "Error: name already taken" << endl;
				break; //return to main screen
			}

			abcCustomers.insert(std::map<string, Customer>::value_type(inputStr, Customer(inputStr)));

		case EXISTING_CUSTOMER:
			if (inputNum == EXISTING_CUSTOMER)//not new customer
			{
				cout << "Please enter exiting customer name\n";
				cin >> inputStr;

				if (abcCustomers.find(inputStr) == abcCustomers.end())//if name doesnt exist
				{
					cout << "Customer does not exist. returning to main menu\n";
					break; //return to main screen
				}
			}

			if (EXISTING_CUSTOMER == inputNum)
			{
				printPurchases(abcCustomers, inputStr);

				cout << "1. Add items\n";
				cout << "2. Remove items\n";
				cout << "3. Back to menu\n";
				cin >> inputNum;
			}

			if (1 == inputNum || NEW_CUSTOMER == inputNum)//ADD ITEMS
			{
				while (inputNum != 0)
				{
					printForSale(items);

					cin >> inputNum;
					switch (inputNum)
					{
					case 1://milk
						abcCustomers.find(inputStr)->second.addItem(Item("Milk", MILK, items.find(MILK)->second.getUnitPrice()));

						printPurchases(abcCustomers, inputStr);
						break;
					case 2://cookies 
						abcCustomers.find(inputStr)->second.addItem(Item("Cookies", COOKIES, items.find(COOKIES)->second.getUnitPrice()));
						printPurchases(abcCustomers, inputStr);
						break;
					case 3:
						abcCustomers.find(inputStr)->second.addItem(Item("Bread", BREAD, items.find(BREAD)->second.getUnitPrice()));
						printPurchases(abcCustomers, inputStr);
						break;
					case 4:
						abcCustomers.find(inputStr)->second.addItem(Item("Chocolate", CHOCOLATE, items.find(CHOCOLATE)->second.getUnitPrice()));
						printPurchases(abcCustomers, inputStr);
						break;
					case 5:
						abcCustomers.find(inputStr)->second.addItem(Item("Cheese", CHEESE, items.find(CHEESE)->second.getUnitPrice()));
						printPurchases(abcCustomers, inputStr);
						break;
					case 6:
						abcCustomers.find(inputStr)->second.addItem(Item("rice", RICE, items.find(RICE)->second.getUnitPrice()));
						printPurchases(abcCustomers, inputStr);
						break;
					case 7:
						abcCustomers.find(inputStr)->second.addItem(Item("Fish", FISH, items.find(FISH)->second.getUnitPrice()));
						printPurchases(abcCustomers, inputStr);
						break;
					case 8:
						abcCustomers.find(inputStr)->second.addItem(Item("Chicken", CHICKEN, items.find(CHICKEN)->second.getUnitPrice()));
						printPurchases(abcCustomers, inputStr);
						break;
					case 9:
						abcCustomers.find(inputStr)->second.addItem(Item("Cucumber", CUCUMBER, items.find(CUCUMBER)->second.getUnitPrice()));
						printPurchases(abcCustomers, inputStr);
						break;
					case 10:
						abcCustomers.find(inputStr)->second.addItem(Item("Tomato", TOMATO, items.find(TOMATO)->second.getUnitPrice()));
						printPurchases(abcCustomers, inputStr);
						break;
					}
				}
			}
			if (2 == inputNum)//REMOVE ITEMS
			{

				while (inputNum != 0)
				{
					printPurchases(abcCustomers, inputStr);
					cin >> inputNum;
					switch (inputNum)
					{
					case 1:
						for (Item item : abcCustomers.find(inputStr)->second.getItems())
						{
							if (item == Item("Milk", MILK, 5.3))
							{
								abcCustomers.find(inputStr)->second.removeItem(item);
								cout << "1 milk removed\n";
							}

						}
						break;
					case 2:

						for (Item item : abcCustomers.find(inputStr)->second.getItems())
						{
							if (item == Item("Cookies", COOKIES, 12.6))
							{
								abcCustomers.find(inputStr)->second.removeItem(item);
								cout << "1 cookies removed\n";
							}
						}
						break;
					case 3:

						for (Item item : abcCustomers.find(inputStr)->second.getItems())
						{
							if (item == Item("Bread", BREAD, 8.9))
							{
								abcCustomers.find(inputStr)->second.removeItem(item);
								cout << "1 bread removed\n";
							}
						}
						break;
					case 4:
						for (Item item : abcCustomers.find(inputStr)->second.getItems())
						{
							if (item == Item("Chocolate", CHOCOLATE, 7.00))
							{
								abcCustomers.find(inputStr)->second.removeItem(item);
								cout << "1 chocolate removed\n";
							}

						}
						break;
					case 5:
						for (Item item : abcCustomers.find(inputStr)->second.getItems())
						{
							if (item == Item("Cheese", CHEESE, 15.3))
							{
								abcCustomers.find(inputStr)->second.removeItem(item);
								cout << "1 cheese removed\n";
							}

						}
						break;
					case 6:
						for (Item item : abcCustomers.find(inputStr)->second.getItems())
						{
							if (item == Item("Rice", RICE, 6.2))
							{
								abcCustomers.find(inputStr)->second.removeItem(item);
								cout << "1 rice removed\n";
							}

						}
						break;
					case 7:
						for (Item item : abcCustomers.find(inputStr)->second.getItems())
						{
							if (item == Item("Fish", FISH, 31.65))
							{
								abcCustomers.find(inputStr)->second.removeItem(item);
								cout << "1 fish removed\n";
							}

						}
						break;
					case 8:
						for (Item item : abcCustomers.find(inputStr)->second.getItems())
						{
							if (item == Item("Chicken", CHICKEN, 25.99))
							{
								abcCustomers.find(inputStr)->second.removeItem(item);
								cout << "1 chicken removed\n";
							}

						}
						break;
					case 9:
						for (Item item : abcCustomers.find(inputStr)->second.getItems())
						{
							if (item == Item("Cucumber", CUCUMBER, 1.21))
							{
								abcCustomers.find(inputStr)->second.removeItem(item);
								cout << "1 cucumber removed\n";
							}

						}
						break;
					
		case 10:
			for (Item item : abcCustomers.find(inputStr)->second.getItems())
			{
				if (item == Item("Tomato", TOMATO, 2.32))
				{
					abcCustomers.find(inputStr)->second.removeItem(item);
					cout << "1 tomato removed\n";
				}

			}
			break;
				}
			}
		}
	
		break;


		case PRINT_HIGHEST_PAYER:
			if (abcCustomers.empty())
			{
				break;
			}
			cout << "Highest paying customer is: " << abcCustomers.cbegin()->second.getName();
			cout << "\nTotal sum: " << abcCustomers.cbegin()->second.totalSum() << endl;
			break;
		case EXIT:

			cout << "Thank you, come again!" << endl;
			return 0;

		}
	}

	return 0;
}


void printForSale(unordered_map<string,Item> items)
{
	cout << "\n\n---------------------------------\n";
	cout << "Items for sale are: (0 to exit)\n";

	//cant do for(pair p : items) because 1 has to be milk etc by order
	cout << "1." << "Milk " << "price: " << items.find(MILK)->second.getUnitPrice() << endl;
	cout << "2." << "Cookies " << "price: " << items.find(COOKIES)->second.getUnitPrice() << endl;
	cout << "3." << "Bread " << "price: " << items.find(BREAD)->second.getUnitPrice() << endl;
	cout << "4." << "Chocolate " << "price: " << items.find(CHOCOLATE)->second.getUnitPrice() << endl;
	cout << "5." << "Cheese " << "price: " << items.find(CHEESE)->second.getUnitPrice() << endl;
	cout << "6." << "Rice " << "price: " << items.find(RICE)->second.getUnitPrice() << endl;
	cout << "7." << "Fish " << "price: " << items.find(FISH)->second.getUnitPrice() << endl;
	cout << "8." << "Chicken " << "price: " << items.find(CHICKEN)->second.getUnitPrice() << endl;
	cout << "9." << "Cucumber " << "price: " << items.find(CUCUMBER)->second.getUnitPrice() << endl;
	cout << "10." << "Tomato " << "price: " << items.find(TOMATO)->second.getUnitPrice() << endl;
}


void printPurchases(std::map<string, Customer>abcCustomers, string inputStr)
{
	cout << "\n---------------------------------\n";
	cout << "Purchased items: (0 to exit)\n";

	std::map<string, Customer>::iterator curr = abcCustomers.find(inputStr);

	Customer c = curr->second;

	int num;

	for (Item item : c.getItems())
	{
		num = item.getSerialNumber().back() - 48;
		if (num == 0)
		{
			num += 10; //for tomatos, 2 digits
		}
		cout << num <<". "<< item.getName() << " amount: " << item.getCount() << endl;
	}
	cout << "________________________________\n\n\n";
}