objs/nbd_data.o: srcs/nbd_data.cpp include/nbd_data.hpp \
 include/driver_data.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/nbd_data.o srcs/nbd_data.cpp
objs/nbd_data_pi.o: srcs/nbd_data.cpp include/nbd_data.hpp \
 include/driver_data.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/nbd_data_pi.o srcs/nbd_data.cpp
