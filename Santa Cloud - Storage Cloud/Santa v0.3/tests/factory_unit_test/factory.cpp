#include <iostream>
#include "factory.hpp"
//#include "handleton.hpp"

using namespace ilrd;

class Animal
{
public:
	Animal(){};
	Animal(int a, int b){m_whiskers = a; m_weight = b;};
	virtual ~Animal() = default;
	
	static std::unique_ptr<Animal> create(int a, int b)
	{
		return std::unique_ptr<Animal>(new Animal(a, b));
	}
private:
	int m_whiskers;
	int m_weight;
};

class Kitten: public Animal
{
public:
	Kitten(){};
	Kitten(int a, int b){}
	~Kitten() = default;
	
	static std::unique_ptr<Animal> create(int, int)
	{
		std::cout<< "Meow RrRrr" << std::endl;
		return std::unique_ptr<Animal>(new Kitten());
	}	
};

class Dog: public Animal
{
public:
	Dog(){};
	Dog(int a, int b){};
	~Dog() = default;

	static std::unique_ptr<Animal> create(int, int)
	{
		std::cout<< "Ahoo Ahoo" << std::endl;
		return std::unique_ptr<Animal>(new Dog());
	}
};
 
int main()
{
	try
	{
		Factory<Animal, std::string, int, int> animal_farm;

		animal_farm.add("Animal", Animal::create);
		animal_farm.add("Kitten", Kitten::create);

		animal_farm.add("Dog", Dog::create);
		
		std::unique_ptr<Animal> mush = animal_farm.create("Kitten", 4, 4);
		std::unique_ptr<Animal> bon = animal_farm.create("Animal", 4, 4);
	}
	catch(const std::exception& e)
	{
		std::cout << "exception" << std::endl;
		std::cerr << e.what() << '\n';
	}

	
	return 0;
}
