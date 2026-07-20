objs/dir_monitor.o: srcs/dir_monitor.cpp srcs/../include/logger.hpp \
 srcs/../include/lock_guard.hpp srcs/../include/handleton.hpp \
 srcs/../include/handleton.hpp srcs/../include/monitor.hpp \
 srcs/../include/dir_monitor.hpp srcs/../include/callback_dispatcher.hpp \
 srcs/../include/epoll_wrapper.hpp srcs/../include/epoll_wrapper.hpp \
 srcs/../include/monitor.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/dir_monitor.o srcs/dir_monitor.cpp
objs/dir_monitor_pi.o: srcs/dir_monitor.cpp srcs/../include/logger.hpp \
 srcs/../include/lock_guard.hpp srcs/../include/handleton.hpp \
 srcs/../include/handleton.hpp srcs/../include/monitor.hpp \
 srcs/../include/dir_monitor.hpp srcs/../include/callback_dispatcher.hpp \
 srcs/../include/epoll_wrapper.hpp srcs/../include/epoll_wrapper.hpp \
 srcs/../include/monitor.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/dir_monitor_pi.o srcs/dir_monitor.cpp
