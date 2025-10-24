
#ifndef __CALLBACK_DISPATCHER_HPP__
#define __CALLBACK_DISPATCHER_HPP__

/**
 * implementation of mediators suporting publisher-subscriber design pattern.
 * this classes act as mediatores to decouple publishe and subscriber. 
 *
 * Author: Inbar Duek
 * Date Modified: 29.11.19
 *
 */

#include <unordered_set>    //unordered_set
#include <vector>           //vector
#include <cstring>          //strerror
#include <cstring>          //strerror

#include "../include/err.hpp"
#include "../include/logger.hpp"
#include "../include/handleton.hpp"
#include "../include/inbar_tools.hpp"

namespace ilrd
{

template <typename Msg>
class CallbackBase;

template <typename Msg>
class Dispatcher
{
public:
    
    Dispatcher() = default;

    // must notify all of the viewers on destruction
    ~Dispatcher();
    
    Dispatcher(const Dispatcher&)            = delete; 
    Dispatcher(Dispatcher&&)                 = delete; 
    
    Dispatcher& operator=(const Dispatcher&) = delete;
    Dispatcher& operator=(Dispatcher&&)      = delete; 
    
    // from where does this func take a message to send?
    void notify_all(const Msg& msg);


private:
    // unordered_set can be good alternative because we want to remove element with unique id in O(1)
    std::unordered_set<CallbackBase<Msg>*> m_subscribers;
    std::vector<CallbackBase<Msg>*> m_to_erase;

    friend class CallbackBase<Msg>;
    
    // adds new subscriber
    void add(CallbackBase<Msg>* callback);
   
    void remove(CallbackBase<Msg>* callback);

    //notify all subscribers on dtor
    void notify_out_of_service();

    void garbage_collector();
};

template <typename Msg>
class CallbackBase
{
public:
    explicit CallbackBase(Dispatcher<Msg>* dispatcher);//or set func and default ctor
    //pure virtual but, has implementation for dderived dtor
    virtual ~CallbackBase() = 0;
    virtual void remove();
    CallbackBase(const CallbackBase&)            = delete;
    CallbackBase(CallbackBase&&)                 = delete; 
    
    CallbackBase& operator=(const CallbackBase&) = delete; 
    CallbackBase& operator=(CallbackBase&&)      = delete; 

private:
    Dispatcher<Msg>* m_dispatcher; 

    virtual void notify(const Msg& msg) = 0;
    virtual void out_of_service() = 0;

    friend class Dispatcher<Msg>;
};

//------------------------------------------------------------------------------
template <typename Msg, typename Observer>
class Callback : public CallbackBase<Msg>
{
public:
    //ensure member function
    using ActionMethod = void (Observer::*)(const Msg&); 
    using StopMethod = void (Observer::*)();

    explicit Callback(Dispatcher<Msg>* dispatcher, 
                      Observer& observer, 
                      ActionMethod action_method, 
                      StopMethod stop_method = nullptr);
    ~Callback() override;
    void remove() override;

    Callback(const Callback&)            = delete; 
    Callback(Callback&&)                 = delete; 
    
    Callback& operator=(const Callback&) = delete; 
    Callback& operator=(Callback&&)      = delete; 
        
private:
    void notify(const Msg& msg) override;
    void out_of_service() override;

    Observer& m_observer;
    ActionMethod m_action_method;
    StopMethod m_stop_method;
};

//------------------------------------------------------------------------------
//dispatcher
//------------------------------------------------------------------------------
template <typename Msg>
Dispatcher<Msg>::~Dispatcher()
{
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "Dispatcher: dtor", __FILE__, __LINE__);
    try
    {
        notify_out_of_service();
    }
    catch(const std::exception& err)
    {
        Handleton<Logger>::get_instance()->Log(Logger::ERROR, 
            "Dispatcher: dtor failed: " + std::string(err.what()), __FILE__, __LINE__);
    }
}

//------------------------------------------------------------------------------
template <typename Msg>
void Dispatcher<Msg>::garbage_collector()
{
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "Dispatcher: garbage_collector: ", __FILE__, __LINE__);
    for(auto& iter : m_to_erase)
    {
       m_subscribers.erase(iter);
    }

    m_to_erase.clear();
}

template <typename Msg>
void Dispatcher<Msg>::notify_out_of_service()
{
    garbage_collector();

    for(const auto& iter : m_subscribers)
    {
        iter->out_of_service();
    }
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "Dispatcher: notify_out_of_service: ", __FILE__, __LINE__);
}
//------------------------------------------------------------------------------
template <typename Msg>
void Dispatcher<Msg>::notify_all(const Msg& msg)
{
    garbage_collector();

    for(const auto& iter : m_subscribers)
    {
        iter->notify(msg);
    }
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "Dispatcher: notify_all: ", __FILE__, __LINE__);
}

//------------------------------------------------------------------------------
template <typename Msg>
void Dispatcher<Msg>::add(CallbackBase<Msg>* callback)
{
    if(m_subscribers.emplace(callback).second == false)
    {
        //TODO
        //throw BadCreate("dispatcher: add failed", strerror(errno));
        throw std::runtime_error("dispatcher: add failed" + std::string(strerror(errno)));
    }
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "Dispatcher: add ", __FILE__, __LINE__);
}

//------------------------------------------------------------------------------
template <typename Msg>
void Dispatcher<Msg>::remove(CallbackBase<Msg>* callback)
{
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "Dispatcher: remove ", __FILE__, __LINE__);
    //add callback to vector to_be_removed, will be removed on next notify_all;
    m_to_erase.push_back(callback);
}

//------------------------------------------------------------------------------
//callback base
//------------------------------------------------------------------------------
template <typename Msg>
CallbackBase<Msg>::CallbackBase(Dispatcher<Msg>* dispatcher) //or set func and default ctor
    :m_dispatcher(dispatcher)
{
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "CallbackBase: ctor ", __FILE__, __LINE__);
    m_dispatcher->add(this);
}

//------------------------------------------------------------------------------
template <typename Msg>
CallbackBase<Msg>::~CallbackBase()
{
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "CallbackBase: dtor ", __FILE__, __LINE__);
    try
    {
        if(m_dispatcher)
        {
            m_dispatcher->remove(this);
        }
    }
    catch(const std::exception& err)
    {
        Handleton<Logger>::get_instance()->Log(Logger::ERROR, 
            "CallbackBase dtor failed: " + std::string(err.what()), __FILE__, __LINE__);
    }
}

template <typename Msg>
void CallbackBase<Msg>::remove()
{
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "CallbackBase: remove ", __FILE__, __LINE__);
    
    m_dispatcher->remove(this);
    m_dispatcher = nullptr;
}

//------------------------------------------------------------------------------
//callback
//------------------------------------------------------------------------------
template <typename Msg, typename Observer>
Callback<Msg, Observer>::Callback(Dispatcher<Msg>* dispatcher,
                      Observer& observer,
                      ActionMethod action_method,
                      StopMethod stop_method)
    : CallbackBase<Msg>(dispatcher), m_observer(observer), 
      m_action_method(action_method), m_stop_method(stop_method)
{}

//------------------------------------------------------------------------------
//will call base dtor
template <typename Msg, typename Observer>
Callback<Msg, Observer>::~Callback() {}

//------------------------------------------------------------------------------
template <typename Msg, typename Observer>
void Callback<Msg, Observer>::remove()
{
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "Callback: remove ", __FILE__, __LINE__);
    
    CallbackBase<Msg>::remove();
}

//------------------------------------------------------------------------------
//do action on observer with msg from dispatcher
template <typename Msg, typename Observer>
void Callback<Msg, Observer>::notify(const Msg& msg)
{
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "Callback: notify ", __FILE__, __LINE__);
    
    m_observer.m_action_method(std::string(msg));
}

//------------------------------------------------------------------------------
//do stop method on observer
template <typename Msg, typename Observer>
void Callback<Msg, Observer>::out_of_service()
{
    Handleton<Logger>::get_instance()->Log(Logger::DEBUGER, 
            "Callback: out_of_service notify ", __FILE__, __LINE__);
    m_observer.m_stop_method();
}

} //ilrd
#endif // __CALLBACK_DISPATCHER_HPP__