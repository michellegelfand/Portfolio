#!/bin/bash
#shared object:


#clang++ -pedantic-errors -Wall -Wextra -g -std=c++11  singleton_shared.cpp -fPIC -c

gc+11 handleton_shared.cpp globals.cpp -fPIC -c

# gc+11 globals.cpp -fPIC -c


#clang++ -pedantic-errors -Wall -Wextra -g -std=c++11  -shared -fPIC -o libsingleton_shared.so singleton_shared.o


gc+11 -shared  -fPIC -o libglobals.so globals.o

gc+11 -shared -fPIC -o libhandleton_shared.so -L. -lglobals handleton_shared.o 

export LD_LIBRARY_PATH=.


#implicit

#clang++ -pedantic-errors -Wall -Wextra -g -std=c++11 singleton_test_implicit.cpp -L. -lsingleton_shared -ldl -pthread

# gc+11 handleton_test_implicit.cpp -L. -lhandleton_shared - -ldl -pthread

#explicit 


#clang++ -pedantic-errors -Wall -Wextra -g -std=c++11 singleton_test_explicit.cpp -L. -ldl -pthread
# gc+11 handleton_test_explicit.cpp -L. -lglobals -ldl -pthread
gc+11 handleton_test_explicit.cpp -L. -lglobals -ldl -pthread

#solution to multiple singletons
# gc+11 handleton_test_explicit.cpp -L. -ldl -pthread -rdynamic
