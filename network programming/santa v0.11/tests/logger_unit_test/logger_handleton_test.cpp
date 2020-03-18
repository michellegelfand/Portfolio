#include "handleton.hpp"
#include "logger.hpp"


using namespace ilrd;

int main()
{
    Logger* logger = Handleton<Logger>::get_instance();

    return 0;
}