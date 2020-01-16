../objs/driver_data.o: ../srcs/driver_data.cpp \
 ../srcs/../include/driver_data.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE -DDO_DEBUG -g -c -I../include/ -o ../objs/driver_data.o ../srcs/driver_data.cpp
