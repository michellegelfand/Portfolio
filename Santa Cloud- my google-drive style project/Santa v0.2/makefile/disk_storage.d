../objs/disk_storage.o: ../srcs/disk_storage.cpp \
 ../srcs/../include/disk_storage.hpp ../srcs/../include/storage.hpp \
 ../srcs/../include/driver_data.hpp ../srcs/../include/lock_guard.hpp \
 ../srcs/../include/logger.hpp ../srcs/../include/lock_guard.hpp \
 ../srcs/../include/handleton.hpp ../srcs/../include/test_tools.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE -DDO_DEBUG -g -c -I../include/ -o ../objs/disk_storage.o ../srcs/disk_storage.cpp
