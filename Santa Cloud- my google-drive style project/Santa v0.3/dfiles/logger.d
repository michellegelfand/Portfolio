objs/logger.o: srcs/logger.cpp include/logger.hpp include/lock_guard.hpp \
 include/handleton.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/logger.o srcs/logger.cpp
objs/logger_pi.o: srcs/logger.cpp include/logger.hpp \
 include/lock_guard.hpp include/handleton.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/logger_pi.o srcs/logger.cpp
