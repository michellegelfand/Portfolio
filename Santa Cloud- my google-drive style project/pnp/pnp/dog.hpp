#include "animal.hpp"


class dog : public animal
{
private:
    /* data */
public:
    dog();
    ~dog();

    void execute(/* args */);
    static std::unique_ptr<animal> create();
};
