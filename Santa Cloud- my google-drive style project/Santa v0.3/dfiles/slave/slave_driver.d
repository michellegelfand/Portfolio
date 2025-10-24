objs/slave/slave_driver.o: srcs/slave/slave_driver.cpp \
 include/../include/slave_driver.hpp include/../include/driver_proxy.hpp \
 include/../include/driver_data.hpp include/../include/handleton.hpp \
 include/../include/lock_guard.hpp include/../include/driver_data.hpp \
 include/../include/logger.hpp include/../include/handleton.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/slave/slave_driver.o srcs/slave/slave_driver.cpp
objs/slave/slave_driver_pi.o: srcs/slave/slave_driver.cpp \
 include/../include/slave_driver.hpp include/../include/driver_proxy.hpp \
 include/../include/driver_data.hpp include/../include/handleton.hpp \
 include/../include/lock_guard.hpp include/../include/driver_data.hpp \
 include/../include/logger.hpp include/../include/handleton.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/slave/slave_driver_pi.o srcs/slave/slave_driver.cpp
