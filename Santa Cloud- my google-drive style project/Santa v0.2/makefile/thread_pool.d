../objs/thread_pool.o: ../srcs/thread_pool.cpp ../include/lock_guard.hpp \
 ../include/thread_pool.hpp ../include/tptask.hpp \
 ../include/waitable_pqueue.hpp ../include/tptask.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE -DDO_DEBUG -g -c -I../include/ -o ../objs/thread_pool.o ../srcs/thread_pool.cpp
