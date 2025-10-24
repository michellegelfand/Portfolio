#shared object:

gc+11 singleton_shared.cpp -fPIC -c

gc+11 -shared -fPIC -o libsingleton_shared.so singleton_shared.o

export LD_LIBRARY_PATH=.


#implicit

gc+11 singleton_test_implicit.cpp -L. -lsingleton_shared -ldl -pthread

#explicit 

gc+11 singleton_test_explicit.cpp -L. -ldl -pthread

#solution to multiple singletons

gc+11 singleton_test_explicit.cpp -L. -ldl -pthread -rdynamic
