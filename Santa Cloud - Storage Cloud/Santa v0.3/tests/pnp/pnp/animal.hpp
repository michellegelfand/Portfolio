
#include<iostream>
#include <memory>

#include "../include/factory.hpp"
#include "../include/handleton.hpp"

class animal
{ 
private:
    /* data */
public:
    animal() = default;
    virtual ~animal() = default;
    
    virtual void execute(/* args */);
    static std::unique_ptr<animal> create();
};
