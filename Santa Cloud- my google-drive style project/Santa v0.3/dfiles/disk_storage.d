objs/disk_storage.o: srcs/disk_storage.cpp \
 srcs/../include/disk_storage.hpp srcs/../include/storage.hpp \
 srcs/../include/driver_data.hpp srcs/../include/lock_guard.hpp \
 srcs/../include/logger.hpp srcs/../include/lock_guard.hpp \
 srcs/../include/handleton.hpp srcs/../include/test_tools.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/disk_storage.o srcs/disk_storage.cpp
objs/disk_storage_pi.o: srcs/disk_storage.cpp \
 srcs/../include/disk_storage.hpp srcs/../include/storage.hpp \
 srcs/../include/driver_data.hpp srcs/../include/lock_guard.hpp \
 srcs/../include/logger.hpp srcs/../include/lock_guard.hpp \
 srcs/../include/handleton.hpp srcs/../include/test_tools.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/disk_storage_pi.o srcs/disk_storage.cpp
