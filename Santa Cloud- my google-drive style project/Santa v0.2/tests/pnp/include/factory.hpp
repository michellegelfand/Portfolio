#ifndef __FACTORY_H__
#define __FACTORY_H__
/**
 *  Project: factory.hpp
 *  Date: 18/11/2019
 * Author: Inbar Duek
 
 *  Factory class handles creation of objects of diffrent types of
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

#include <unordered_map>    // unorderd map
#include <memory>         // 

#include "handleton.hpp"
#include "logger.hpp"
#include "err.hpp"
#include "inbar_tools.hpp"

namespace ilrd
{

//------------------------------------------------------------------------------
template <typename Base, typename Key, typename... Args>
class Factory
{

public:
    enum add_type_t
    {
        ADDED,
        UPDATED
    };

    using CreatorFunc = std::function<std::unique_ptr<Base>(Args... args)>;   

    add_type_t add(const Key& key, CreatorFunc creator);
    
    std::unique_ptr<Base> create(const Key& key, Args... args);

    ~Factory() = default;
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;
    Factory(Factory&&) = delete;
    Factory& operator=(Factory&&) = delete;

    //will mv to private after test to use with handleton
    Factory() = default;
private:
    friend Handleton<Factory<Base,Key,Args...>>;
    std::unordered_map<Key, CreatorFunc> m_creators;

};

template <typename Base, typename Key, typename... Args>
typename Factory< Base, Key, Args...>::add_type_t 
    Factory< Base, Key, Args...>::add(
    const Key& key, Factory< Base, Key, Args...>::CreatorFunc creator)
{
/*     Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, "Factory add:\n", 
        __FILE__, __LINE__); */

    //DEBUG_ONLY("enter factory\n");
    
    add_type_t status = ADDED;
   
    std::pair<Key, Factory::CreatorFunc> pair(key, creator);
    
    //Insert returns a pair, pair.first- iterator to either the new element  
    //or to the element with the equivalent key.
    //pair.second- true if new_element inserted/false if key allready existed.
    auto res = m_creators.insert(pair);

    //if insert seccedded res.secound =true
    if(!res.second)
    {
        m_creators[key] = creator;
        status = UPDATED;
    }
    
    return status;
}

template <typename Base, typename Key, typename... Args>
std::unique_ptr<Base> Factory<Base, Key, Args...>::create(
                                                const Key& key, Args... args)
{
    try
    {
        return (m_creators.at(key)(std::forward<Args>(args)...));
    }
    catch(const std::bad_alloc& err)
    {
       /*  Handleton<Logger>::get_instance()->Log(Logger::ERROR, 
            std::string("Factory::create failed: bad_alloc, ") + err.what(), 
            __FILE__, __LINE__); */
        //TODO
        //hrow BadCreate(std::string("Factory::create failed: bad_alloc"), err.what());
        throw std::runtime_error("Factory::create failed: bad_alloc");
    }
    catch(const std::out_of_range& err)
    {
    /*     Handleton<Logger>::get_instance()->Log(Logger::ERROR, 
            std::string("Factory::create failed: out_of_range,") + err.what(),
            __FILE__, __LINE__); */
        //TODO
        //throw BadKey(std::string("Factory::create failed: out_of_range"), err.what());
        throw std::runtime_error("Factory::create failed: out_of_range");
        
    }
}

} //ilrd

#endif //__FACTORY_H__