#include "handleton.hpp"
#include "logger.hpp"
#include "factory.hpp"

using namespace ilrd;


init_handleton(Logger)
//init_handleton(Factory)

/* template <>\
std::atomic<Factory<Base, std::sring,int>*> Handleton<Factory<Base, std::sring,int>>::s_instance(nullptr);\
template <>\
std::mutex Handleton<Factory<Base, std::sring,int>>::s_mutex{};

template <>\
std::atomic<Factory<Base, std::sring,int, std::unique_ptr<int> >*> Handleton<Factory<Base, std::sring,int, std::unique_ptr<int> >>::s_instance(nullptr);\
template <>\
std::mutex Handleton<Factory<Base, std::sring,int, std::unique_ptr<int> >>::s_mutex{}; */
