../objs/ram_storage.o: ../srcs/ram_storage.cpp \
 ../srcs/../include/test_tools.hpp ../srcs/../include/ram_storage.hpp \
 ../srcs/../include/storage.hpp ../srcs/../include/driver_data.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE -DDO_DEBUG -g -c -I../include/ -o ../objs/ram_storage.o ../srcs/ram_storage.cpp
