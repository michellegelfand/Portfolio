#define _XOPEN_SOURCE
#define _POSIX_SOURCE

#include <unistd.h> /* sleep */
#include "wd.h"

int main(int argc, char **argv)
{
	int sleeping_time = 20;
	watchdog_t *watchdog_args = {0};
	(void)argc;

	watchdog_args = KeepMeAlive(argv);

	while(sleeping_time)
    {
        sleeping_time = sleep(sleeping_time);
    }

	LetMeDie(watchdog_args);

	return 0;
}
