#define _XOPEN_SOURCE
#define _POSIX_SOURCE

#include <unistd.h>//sleep


#include "test_tools.h"
#include "scope_guard.h"
#include "wd_guard.h"

using namespace ilrd;

size_t RUNFOR = 50;

int main(int argc, char **argv)
{
	WDGuard wdobj(argv);
	ScopeGuard< WDGuard, &WDGuard::ExecWD, &WDGuard::KillWD > guard(&wdobj);

	(void)argc;

	while(RUNFOR)
    {
        RUNFOR = sleep(RUNFOR);
    }

	return 0;
}

