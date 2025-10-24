objs/mmap_storage.o: srcs/mmap_storage.cpp \
 srcs/../include/mmap_storage.hpp srcs/../include/storage.hpp \
 srcs/../include/driver_data.hpp srcs/../include/lock_guard.hpp
	g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/mmap_storage.o srcs/mmap_storage.cpp
objs/mmap_storage_pi.o: srcs/mmap_storage.cpp \
 srcs/../include/mmap_storage.hpp srcs/../include/storage.hpp \
 srcs/../include/driver_data.hpp srcs/../include/lock_guard.hpp
	/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -c -fpic -Iinclude/ -Iinclude/master/ -Iinclude/slave/ -o objs/mmap_storage_pi.o srcs/mmap_storage.cpp
