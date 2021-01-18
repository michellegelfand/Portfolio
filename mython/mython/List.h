#pragma once

#include <vector>
#include "Sequence.h"
class List :
    public Sequence
{
public:
    List(const std::vector<Type*>& members);
    virtual bool isPrintable() const override;
    virtual std::string toString() const override;

private:
    std::vector<Type*> _members;
};

