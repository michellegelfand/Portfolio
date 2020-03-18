#ifndef __WD_H__
#define __WD_H__

#include "wd_shared.h"

watchdog_t *KeepMeAlive(char **argv);
void LetMeDie(watchdog_t *watchdog_key);

#endif /*__WD_H__ */
