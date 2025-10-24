../objs/nbd_driver_proxy.o: ../srcs/nbd_driver_proxy.cpp \
 ../srcs/../include/nbd_driver_proxy.hpp \
 ../srcs/../include/driver_proxy.hpp \
 ../srcs/../include/../include/driver_data.hpp \
 ../srcs/../include/driver_data.hpp ../srcs/../include/handleton.hpp \
 ../srcs/../include/lock_guard.hpp ../srcs/../include/logger.hpp \
 ../srcs/../include/handleton.hpp ../srcs/../include/lock_guard.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE -DDO_DEBUG -g -c -I../include/ -o ../objs/nbd_driver_proxy.o ../srcs/nbd_driver_proxy.cpp
