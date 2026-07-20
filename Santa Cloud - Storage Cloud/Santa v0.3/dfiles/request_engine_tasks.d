objs/request_engine_tasks.o: srcs/request_engine_tasks.cpp \
 srcs/../include/arg_data.hpp srcs/../include/driver_data.hpp \
 srcs/../include/driver_proxy.hpp srcs/../include/storage.hpp \
 srcs/../include/request_engine_tasks.hpp srcs/../include/retask.hpp \
 srcs/../include/tptask.hpp srcs/../include/nbd_gateway.hpp \
 srcs/../include/gateway.hpp srcs/../include/arg_data.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/request_engine_tasks.o srcs/request_engine_tasks.cpp
objs/request_engine_tasks_pi.o: srcs/request_engine_tasks.cpp \
 srcs/../include/arg_data.hpp srcs/../include/driver_data.hpp \
 srcs/../include/driver_proxy.hpp srcs/../include/storage.hpp \
 srcs/../include/request_engine_tasks.hpp srcs/../include/retask.hpp \
 srcs/../include/tptask.hpp srcs/../include/nbd_gateway.hpp \
 srcs/../include/gateway.hpp srcs/../include/arg_data.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/request_engine_tasks_pi.o srcs/request_engine_tasks.cpp
