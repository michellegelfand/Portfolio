#include "../include/handleton.hpp"
#include "../include/logger.hpp"
#include "../include/factory.hpp"
#include "animal.hpp"

namespace  ilrd
{
    INITHANDLETON(int)
    INITHANDLETON(Logger)

    /* using factory_type = Factory<char, int, int>;
    INITHANDLETON(factory_type) */

    using factory_animal = Factory<animal, std::string>;
    INITHANDLETON(factory_animal)
}