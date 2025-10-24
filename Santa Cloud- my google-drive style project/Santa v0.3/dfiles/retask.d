objs/retask.o: srcs/retask.cpp include/retask.hpp include/tptask.hpp \
 include/tptask.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/retask.o srcs/retask.cpp
objs/retask_pi.o: srcs/retask.cpp include/retask.hpp include/tptask.hpp \
 include/tptask.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/retask_pi.o srcs/retask.cpp
