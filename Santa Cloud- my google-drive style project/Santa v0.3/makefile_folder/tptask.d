../objs/tptask.o: ../srcs/tptask.cpp ../include/tptask.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -std=c++11 -D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE -DDO_DEBUG -g -c -I../include/ -o ../objs/tptask.o ../srcs/tptask.cpp
