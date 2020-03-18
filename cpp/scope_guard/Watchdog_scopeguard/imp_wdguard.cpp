#include "wd_guard.h"

namespace ilrd
{

   WDGuard::WDGuard(char **argv)
        : m_argv(argv),m_wd_key(0) 
   {
       ExecWD();
   }

    WDGuard::~WDGuard()
    {
        KillWD();
    }

   void WDGuard::ExecWD()
   {
       m_wd_key = KeepMeAlive(m_argv);

   }
   
   void WDGuard::KillWD()
   {
       if(m_wd_key)
       {
            LetMeDie(m_wd_key);
       }
   }

}//ilrd