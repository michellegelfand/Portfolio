#!/bin/bash
#shared object:

g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 -fpic -shared globals.cpp -o libglobals.so

g++ -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -std=c++11 -c -fpic -o animal.o animal.cpp
g++ -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -std=c++11 -fpic -shared -L. -o libanimal.so animal.o logger.cpp libglobals.so

g++ -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -std=c++11 -c -fpic -o dog.o dog.cpp
g++ -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -std=c++11 -fpic -shared -o libdog.so dog.o logger.cpp libglobals.so

g++ -ansi -pedantic-errors -Wall -Wextra -g -std=c++11 dllLoader_test.cpp dll_loader.cpp dir_monitor.cpp epoll_wrapper.cpp monitor.cpp logger.cpp -L. -pthread -ldl -Wl,-rpath=. -lglobals -o test.out

sudo chmod 777 *.so

./test.out
