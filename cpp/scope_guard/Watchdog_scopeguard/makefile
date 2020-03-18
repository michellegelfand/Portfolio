################################################################################
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -Og -fPIC 
LDFLAGS = -lm -lpthread 
DIR = $(shell pwd)
LIB = wd_activation.a

###############################################################################
SRCS = $(filter-out $(wildcard *_test*) ,$(wildcard *.c))
HDRS = $(wildcard *.h)
OBJECTS = $(patsubst %.c,%.o,$(SRCS))
EXEC = $(patsubst %.c,%.out,$(wildcard *_test.c))
LIBS = $(wildcard ./lib/lib*.a)

################################################################################
.PHONY = all
all: wd_activation.a
	$(CC) $(CFLAGS) wd_shared.c -o libwd_shared.so -fPIC -shared -c 
	$(CC) $(CFLAGS) wd.c -o wd.o $(LIB) -lpthread
	$(CC) $(CFLAGS) wd_exec.c $(LIB) -o wd_exec.out -lpthread
	g++ $(CFLAGS) wd_test.cpp imp_wdguard.cpp $(LIB) -lpthread -o wd_test.out

################################################################################
.PHONY = release 
release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 \
-D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE
release: librelease.a

####### Static Librarry ########################################################
%.a: $(SRCS) $(HDRS) $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

####### Executable #############################################################
%.out: %.o $(LIB)
	$(CC) $(CFLAGS) $< $(LIB) -o $@ $(LDFLAGS)

####### Object #################################################################
%.o: %.d
	$(CC) $< -c -o $@

################################################################################
%.d: %.c
	$(CC) -MM $< > $@

################################################################################
.PHONY = include
include:
	ln -sf $(DIR)/*.h $(DIR)/includes

####### Libraries ##############################################################
.PHONY = libs 
libs: $(SRCS) $(HDRS) $(LIBS)
	ln -sf $(DIR)/*.a $(DIR)/lib

####### Test ###################################################################
.PHONY = test
test: $(EXEC)
	ln -sf $(DIR)/*.out $(DIR)/test

####### Clean ##################################################################
.PHONY = clean
clean:
	find . -name '*.out' -delete
	find . -name '*.o' -delete
	find . -name '*.so' -delete
	find . -name '*.a' -delete
	find . -name '*.d' -delete

#gd wd_shared.c -o libwd_shared.so -fPIC -shared -c 

#gd wd_test.c wd_activation.o wd_shared.so wd_activation.a -lpthread

#gd wd_activation.c -o watchdog.o wd_shared.so libdebug.a -lpthread

#gd wd_exec.c wd_shared.so wd_activation.a
