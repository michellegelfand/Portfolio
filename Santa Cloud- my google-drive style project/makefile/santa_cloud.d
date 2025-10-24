../objs/santa_cloud.o: ../srcs/santa_cloud.cpp \
 ../srcs/../include/ram_storage.hpp ../srcs/../include/storage.hpp \
 ../srcs/../include/driver_data.hpp ../srcs/../include/lock_guard.hpp \
 ../srcs/../include/driver_data.hpp \
 ../srcs/../include/nbd_driver_proxy.hpp \
 ../srcs/../include/driver_proxy.hpp \
 ../srcs/../include/../include/driver_data.hpp \
 ../srcs/../include/driver_proxy.hpp ../srcs/../include/epoll_wrapper.hpp \
 ../srcs/../include/monitor.hpp ../srcs/../include/logger.hpp \
 ../srcs/../include/handleton.hpp ../srcs/../include/handleton.hpp \
 ../srcs/../include/factory.hpp ../srcs/../include/exceptions.hpp \
 ../srcs/../include/disk_storage.hpp ../srcs/../include/tptask.hpp \
 ../srcs/../include/request_engine_tasks.hpp \
 ../srcs/../include/tptask.hpp ../srcs/../include/nbd_driver_proxy.hpp \
 ../srcs/../include/thread_pool.hpp \
 ../srcs/../include/waitable_pqueue.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE -DDO_DEBUG -g -c -I../include/ -o ../objs/santa_cloud.o ../srcs/santa_cloud.cpp
