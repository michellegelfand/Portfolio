objs/driver_data.o: srcs/driver_data.cpp srcs/../include/driver_data.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/driver_data.o srcs/driver_data.cpp
objs/driver_data_pi.o: srcs/driver_data.cpp \
 srcs/../include/driver_data.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/driver_data_pi.o srcs/driver_data.cpp
