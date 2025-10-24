#include <istream>
#include <ostream>
#include <iosfwd>//std::stringbuf
#include <sstream>//std::stringbuf

#include "serializer.hpp"


using namespace ilrd;

class Animal
{
public:
	Animal(){m_cuteness = 9000;};
	virtual ~Animal() = default;

	virtual void serialize(std::ostream& os)const;
	virtual void deserialize(std::istream& is);

	friend std::ostream& operator<<(std::ostream& os, const Animal& a);
	friend std::istream& operator>>(std::istream& is, Animal& a);

	virtual void make_sound(){std::cout << "\nahoo"<< std::endl;};

/* private: */
	size_t m_cuteness = 9000;

};

// << >> ///////
std::ostream& operator<<(std::ostream& os, const Animal& a)
{
	a.serialize(os);

	return os;
}

std::istream& operator>>(std::istream& is, Animal& a)
{
	a.deserialize(is);

	return is;
}


// serialize deserialized

void Animal::serialize(std::ostream& os)const
{
	os << m_cuteness;
}

void Animal::deserialize(std::istream& is)
{
	is >> m_cuteness;
}


// deriveds

class Monkey: public Animal
{
public:
	Monkey() = default;
	~Monkey() = default;

	friend std::ostream& operator<<(std::ostream& os, const Animal& a);
	friend std::istream& operator>>(std::istream& is, Animal& a);

	virtual void serialize(std::ostream& os)const;
	virtual void deserialize(std::istream& is);

	virtual void make_sound(){std::cout << "\noooo oooo ahh ahh screeeech";};
};

void Monkey::serialize(std::ostream& os)const
{
	Animal::serialize(os);
}

void Monkey::deserialize(std::istream& is)
{
	Animal::deserialize(is);
}


class Moose: public Animal
{
public:
	Moose() = default;
	~Moose() = default;

	friend std::ostream& operator<<(std::ostream& os, const Animal& a);
	friend std::istream& operator>>(std::istream& is, Animal& a);

	virtual void serialize(std::ostream& os)const;
	virtual void deserialize(std::istream& is);

	virtual void make_sound(){std::cout << "\nprrrrwwww";};
	
};

void Moose::serialize(std::ostream& os)const
{
	Animal::serialize(os);
}

void Moose::deserialize(std::istream& is)
{
	Animal::deserialize(is);
}

int main()
{
	Monkey monkey;
	Moose moose;

	Serializer<Animal> serializer;
	std::stringbuf buff;
	std::iostream stream(&buff);

	serializer.add<Monkey>();
	serializer.add<Moose>();

	serializer.serialize(monkey, stream);
	serializer.serialize(moose, stream);

	std::unique_ptr<Animal> monkey_back = serializer.deserialize(stream);
	std::unique_ptr<Animal> moose_back = serializer.deserialize(stream);

	monkey_back->make_sound();
	moose_back->make_sound();

	std::cout << monkey_back->m_cuteness << std::endl;

	return 0;
}