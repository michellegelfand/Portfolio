#include "../include/err.hpp"

namespace ilrd
{

BadCreate::BadCreate(std::string str, std::string error)
    :std::runtime_error(error), m_orig(str)
{
}

BadKey::BadKey(std::string str, std::string error)
    :std::logic_error(error), m_orig(str)
{
}

NBDError::NBDError(std::string str, std::string error)
    :std::runtime_error(error), m_orig(str)
{
}

}