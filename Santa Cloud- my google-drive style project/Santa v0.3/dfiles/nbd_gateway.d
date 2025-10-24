objs/nbd_gateway.o: srcs/nbd_gateway.cpp srcs/../include/nbd_gateway.hpp \
 srcs/../include/gateway.hpp srcs/../include/arg_data.hpp \
 srcs/../include/driver_data.hpp srcs/../include/driver_proxy.hpp \
 srcs/../include/storage.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/nbd_gateway.o srcs/nbd_gateway.cpp
objs/nbd_gateway_pi.o: srcs/nbd_gateway.cpp \
 srcs/../include/nbd_gateway.hpp srcs/../include/gateway.hpp \
 srcs/../include/arg_data.hpp srcs/../include/driver_data.hpp \
 srcs/../include/driver_proxy.hpp srcs/../include/storage.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/nbd_gateway_pi.o srcs/nbd_gateway.cpp
