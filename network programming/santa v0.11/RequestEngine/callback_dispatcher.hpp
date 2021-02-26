#ifndef __CALLBACK_DISPATCHER_HPP__
#define __CALLBACK_DISPATCHER_HPP__

/* 
Michelle Gelfand
 
Since v0.13                                                                           
Implemented for the plug&play feature of the request engine.

	                                                                          */

#include <unordered_set> // std::unordered_set
#include <vector>        // std::vector

namespace ilrd
{

//forward class declaration
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

    friend class CallbackBase<Msg>;

    // unordered_set can be good alternative because we want to remove element with unique id in O(1)
    std::unordered_set<CallbackBase<Msg>*> m_subscribers; 
    std::vector<CallbackBase<Msg>*>to_remove;                                                                  
    
    // adds new subscriber
    void add(CallbackBase<Msg>* callback);

    void remove(CallbackBase<Msg>* callback);
    
    void notify_out_of_service();
};

template <typename Msg>
class CallbackBase
{
public:
    explicit CallbackBase(Dispatcher<Msg>* dispatcher);//or set func and default ctor
    virtual ~CallbackBase() = 0;
    
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

//*****Dispatcher***************************************************************
template <typename Msg>
void Dispatcher<Msg>::add(CallbackBase<Msg>* callback)
{
	m_subscribers.emplace(callback);
}


template <typename Msg>
void Dispatcher<Msg>::remove(CallbackBase<Msg>* callback)
{
    m_subscribers.erase(callback);
}


template <typename Msg>
void Dispatcher<Msg>::notify_all(const Msg& msg)
{
    for (auto& callback_elem : m_subscribers)
    {
        callback_elem->notify(msg);   
    }  
}


template <typename Msg>
Dispatcher<Msg>::~Dispatcher()
{
    notify_out_of_service();
}




template <typename Msg>
void Dispatcher<Msg>::notify_out_of_service()
{
    for (auto& callback_elem : m_subscribers)
    {
        callback_elem->out_of_service();   
    }  
}
//*****CallbackBase***************************************************************




} // namespace ilrd
#endif // __CALLBACK_DISPATCHER_HPP__