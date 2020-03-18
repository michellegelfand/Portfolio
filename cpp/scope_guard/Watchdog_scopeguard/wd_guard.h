#ifndef __WD_GUARD_H__
#define __WD_GUARD_H__

extern "C"
{
    #include "wd.h"
}

namespace ilrd
{

class WDGuard
{

public:
    WDGuard(char **argv);
	~WDGuard();

    void ExecWD();
    void KillWD();

private:
    int m_argc;
    char** m_argv;
    watchdog_t* m_wd_key;
};

}//ilrd

#endif /* __WD_GUARD_H__ */
