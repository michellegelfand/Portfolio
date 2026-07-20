objs/slave/slave_tasks.o: srcs/slave/slave_tasks.cpp \
 srcs/slave/../../include/slave_tasks.hpp \
 srcs/slave/../../include/retask.hpp srcs/slave/../../include/tptask.hpp \
 srcs/slave/../../include/storage.hpp \
 srcs/slave/../../include/driver_data.hpp \
 srcs/slave/../../include/driver_proxy.hpp \
 srcs/slave/../../include/nbd_gateway.hpp \
 srcs/slave/../../include/gateway.hpp \
 srcs/slave/../../include/arg_data.hpp \
 srcs/slave/../../include/arg_data.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/slave/slave_tasks.o srcs/slave/slave_tasks.cpp
objs/slave/slave_tasks_pi.o: srcs/slave/slave_tasks.cpp \
 srcs/slave/../../include/slave_tasks.hpp \
 srcs/slave/../../include/retask.hpp srcs/slave/../../include/tptask.hpp \
 srcs/slave/../../include/storage.hpp \
 srcs/slave/../../include/driver_data.hpp \
 srcs/slave/../../include/driver_proxy.hpp \
 srcs/slave/../../include/nbd_gateway.hpp \
 srcs/slave/../../include/gateway.hpp \
 srcs/slave/../../include/arg_data.hpp \
 srcs/slave/../../include/arg_data.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/slave/slave_tasks_pi.o srcs/slave/slave_tasks.cpp
