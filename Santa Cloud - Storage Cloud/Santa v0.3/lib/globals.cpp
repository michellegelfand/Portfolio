#include "../include/handleton.hpp"
#include "../include/logger.hpp"
#include "../include/factory.hpp"
#include "../include/retask.hpp"
#include "../include/arg_data.hpp"

using namespace ilrd;

using slave_task_factory = Factory<ilrd::RETask, unsigned int, ilrd::ArgData>;

init_handleton(Logger)
init_handleton(slave_task_factory)