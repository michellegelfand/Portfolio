objs/epoll_wrapper.o: srcs/epoll_wrapper.cpp srcs/../include/monitor.hpp \
 srcs/../include/epoll_wrapper.hpp srcs/../include/epoll_wrapper.hpp \
 srcs/../include/monitor.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/epoll_wrapper.o srcs/epoll_wrapper.cpp
objs/epoll_wrapper_pi.o: srcs/epoll_wrapper.cpp \
 srcs/../include/monitor.hpp srcs/../include/epoll_wrapper.hpp \
 srcs/../include/epoll_wrapper.hpp srcs/../include/monitor.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/epoll_wrapper_pi.o srcs/epoll_wrapper.cpp
