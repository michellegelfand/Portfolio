../objs/request_engine_tasks.o: ../srcs/request_engine_tasks.cpp \
 ../srcs/../include/request_engine_tasks.hpp \
 ../srcs/../include/tptask.hpp ../srcs/../include/driver_data.hpp \
 ../srcs/../include/nbd_driver_proxy.hpp \
 ../srcs/../include/driver_proxy.hpp \
 ../srcs/../include/../include/driver_data.hpp \
 ../srcs/../include/storage.hpp ../srcs/../include/handleton.hpp \
 ../srcs/../include/lock_guard.hpp ../srcs/../include/logger.hpp \
 ../srcs/../include/handleton.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE -DDO_DEBUG -g -c -I../include/ -o ../objs/request_engine_tasks.o ../srcs/request_engine_tasks.cpp
