objs/thread_pool.o: srcs/thread_pool.cpp include/lock_guard.hpp \
 include/thread_pool.hpp include/tptask.hpp include/waitable_pqueue.hpp \
 include/tptask.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/thread_pool.o srcs/thread_pool.cpp
objs/thread_pool_pi.o: srcs/thread_pool.cpp include/lock_guard.hpp \
 include/thread_pool.hpp include/tptask.hpp include/waitable_pqueue.hpp \
 include/tptask.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/thread_pool_pi.o srcs/thread_pool.cpp
