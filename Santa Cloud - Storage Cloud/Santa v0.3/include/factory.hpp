/**
 *  Project: factory.hpp
 *  Date: 18/11/2019
 
 *  Factory function handles creation of objects of diffrent types of
    the same heirarchy as required at runtime.
 
 *  Creator class sepcifies the creation function needed by each 
    diffrent concrete factory class.

 *  The derived classes must provide a static func that follows
    the signature of the creator func

 *  add() --> adds the <key, create_func> to the unordered_map.
    returns ADDED on success of new key insertion, if the key existsd REPLACED 
    will be returned.  
    on failure it throws  BadAdd (you shoul implement your own BadAdd class 
    that inherits from std::runtime_error)

 *  create() --> returns a pointer to newly allocated object.
    On failure it throws exception of incorrect key or bad allocation
    (you should implement your own BadKey which inherits from std::logic_error
    and BadCreate which inherits from std::runtime_error).

*/

#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <functional>    //std::function
#include <unordered_map>//unordered map
#include <memory>      //forward

#include "handleton.hpp"


namespace ilrd
{

struct Bad_Create : public std::runtime_error
{
	Bad_Create(const std::string& s = "bad create")
		: std::runtime_error(s) { }
};

struct Bad_Key : public std::logic_error
{
	Bad_Key(const std::string& s = "bad key")
		: std::logic_error(s) { }
};

template <typename Base, typename Key, typename... Args>
class Factory
{

public:
    enum add_type
    {
        ADDED,
        UPDATED
    };

    using CreatorFunc = std::function<std::unique_ptr<Base>(Args... args)>; 

    add_type add(const Key& key, CreatorFunc creator);

    std::unique_ptr<Base> create(const Key& key, Args... args);

    ~Factory() = default;
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;
    Factory(Factory&&) = delete;
    Factory& operator=(Factory&&) = delete;

    Factory() = default;
private:
    /* friend Handleton<Factory<Base,Key,Args>>; */
    std::unordered_map<Key, CreatorFunc> m_creators;

};


template <typename Base, typename Key, typename... Args>
std::unique_ptr<Base> Factory<Base, Key, Args...>::create(const Key& key, Args... args)
{
    try
    {
        //using forward in case of recieving unique_ptr argument, which
        //requires 'move'
        //at(key) - ctor, then next brackets for arguments sent to it
        return (m_creators.at(key)(std::forward<Args>(args)...));
    }
    catch(const std::logic_error e)
    {
       throw Bad_Key("bad key"); 
    }
    catch(const std::runtime_error e)
    {
        throw Bad_Create("bad create");
    }

}

template <typename Base, typename Key, typename... Args>
typename Factory<Base,Key, Args...> ::add_type Factory<Base, Key, Args...>::add(const Key& key, Factory<Base,Key, Args...>::CreatorFunc creator)
{
    try
    {
        auto to_add = m_creators.insert(std::pair<Key,
                                        Factory::CreatorFunc>(key, creator));

        //if insertion failed, there is no second for the iterator
        if (to_add.second)
        {
            return (add_type::ADDED);
        }
        else
        {
            m_creators[key] = creator;
            return add_type::UPDATED;
        }
    }
    catch(const std::exception& e)
    {
        throw Bad_Create("bad create");
    }
    

}


} //ilrd

#endif //__FACTORY_H__

