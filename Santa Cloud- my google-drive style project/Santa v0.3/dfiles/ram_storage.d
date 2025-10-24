objs/ram_storage.o: srcs/ram_storage.cpp srcs/../include/test_tools.hpp \
 srcs/../include/ram_storage.hpp srcs/../include/storage.hpp \
 srcs/../include/driver_data.hpp srcs/../include/lock_guard.hpp \
 srcs/../include/lock_guard.hpp srcs/../include/logger.hpp \
 srcs/../include/handleton.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/ram_storage.o srcs/ram_storage.cpp
objs/ram_storage_pi.o: srcs/ram_storage.cpp \
 srcs/../include/test_tools.hpp srcs/../include/ram_storage.hpp \
 srcs/../include/storage.hpp srcs/../include/driver_data.hpp \
 srcs/../include/lock_guard.hpp srcs/../include/lock_guard.hpp \
 srcs/../include/logger.hpp srcs/../include/handleton.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/ram_storage_pi.o srcs/ram_storage.cpp
