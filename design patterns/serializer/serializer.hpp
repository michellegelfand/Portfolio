//  SERIALIZER
//  Author: Michelle Gelfand
//
//  This program enables the client to serialize objects into ostreams
//  and Deserialize istreams to objects
//
//  The objects are constructed upon deserialization by calling the m_factory
//  object in the creator function
//



#ifndef __SERIALIZER_HPP__
#define __SERIALIZER_HPP__

#include <iostream>
#include "factory.hpp"
/* #include "handleton.hpp" */
#include "exceptions.hpp"

namespace ilrd
{


template <typename Base>
class Serializer
{ 
public:
    Serializer() = default;
    ~Serializer() = default;

    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer&) = delete;
    Serializer(Serializer&&) = delete;
    Serializer& operator=(Serializer&&) = delete;

    template<typename Derived>
    void add();

    void serialize(const Base& obj, std::ostream& stream) const;
    std::unique_ptr<Base> deserialize(std::istream& stream);

    template<typename Derived>
    static std::unique_ptr<Base> creator(std::istream& stream);

private:
    Factory<Base, std::string ,std::istream&> m_factory;
    
};

template <typename Base>
void Serializer<Base>::serialize(const Base& obj, std::ostream& stream) const
{
    try
    {
        std::string key= typeid(obj).name();
        stream << key <<"\n" << obj << "\n";
    }
    catch(const std::runtime_error& e)
    {
        throw Bad_Create("serializer::serialize failed");
    }
}

template <typename Base>
std::unique_ptr<Base> Serializer<Base>::deserialize(std::istream& stream)
{
    try
    {
        //stream into key, then we are left with obj in stream
        // std::string key;
        // stream >> key;

        std::stringbuf key;
        stream.get(key, '\n');
        return m_factory.m_creators[key](stream);
        // return m_factory.create(key, stream);

    }
    catch(const std::runtime_error& e)
    {
        throw Bad_Create("serializer::Deserialize: bad create");
    }
    catch(const std::logic_error& e)
    {
        throw Bad_Key("serializer::Deserialize: bad key: out of bounds");
    }
    
}

template <typename Base>
template<typename Derived>
void Serializer<Base>::add()
{
    try
    {
        std::string key = typeid(Derived).name();

        //add creator for derived class (see creator func)
        //the creator creates an object from the stream
        m_factory.add(key, creator<Derived>);
    }
    catch(const std::logic_error& e)
    {
        throw Bad_Key("serializer::add failed");
    }
}

template <typename Base>
template<typename Derived>
std::unique_ptr<Base> Serializer<Base>::creator(std::istream& stream)
{
    try
    {   
        std::unique_ptr<Base> deserialized_obj(new Derived);

        stream >> *deserialized_obj;

        return deserialized_obj;
    }
    catch(const std::runtime_error& e)
    {
        throw Bad_Create("serializer::creator: bad create");
    }
}   



}//ilrd

#endif //__SERIALIZER_HPP__
