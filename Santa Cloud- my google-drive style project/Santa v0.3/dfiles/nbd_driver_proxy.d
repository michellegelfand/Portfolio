objs/nbd_driver_proxy.o: srcs/nbd_driver_proxy.cpp \
 srcs/../include/nbd_driver_proxy.hpp srcs/../include/driver_proxy.hpp \
 srcs/../include/driver_data.hpp srcs/../include/driver_data.hpp \
 srcs/../include/handleton.hpp srcs/../include/lock_guard.hpp \
 srcs/../include/logger.hpp srcs/../include/handleton.hpp \
 srcs/../include/lock_guard.hpp srcs/../include/nbd_data.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/nbd_driver_proxy.o srcs/nbd_driver_proxy.cpp
objs/nbd_driver_proxy_pi.o: srcs/nbd_driver_proxy.cpp \
 srcs/../include/nbd_driver_proxy.hpp srcs/../include/driver_proxy.hpp \
 srcs/../include/driver_data.hpp srcs/../include/driver_data.hpp \
 srcs/../include/handleton.hpp srcs/../include/lock_guard.hpp \
 srcs/../include/logger.hpp srcs/../include/handleton.hpp \
 srcs/../include/lock_guard.hpp srcs/../include/nbd_data.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/nbd_driver_proxy_pi.o srcs/nbd_driver_proxy.cpp
