CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -Og -fPIC
LDFLAGS = -lm -lpthread
DIR = $(shell pwd)
LIB = wd_main.a

################################
SRCS = $(filter-out $(wildcard *_test*) ,$(wildcard *.c))
HDRS = $(wildcard *.h)
OBJECTS = $(patsubst %.c,%.o,$(SRCS))
EXEC = $(patsubst %.c,%.out,$(wildcard *_test.c))
LIBS = $(wildcard ./lib/lib*.a)

################################
.PHONY = all
all: wd_main.a
	$(CC) $(CFLAGS) wd_shared.c -o libwd_shared.so  -fPIC -shared -c
	$(CC) $(CFLAGS) wd.c -o wd.o wd_main.a -lpthread
	$(CC) $(CFLAGS) wd_exec.c wd_main.a -o wd_exec.out
	$(CC) $(CFLAGS) wd_test.c wd_main.a -lpthread

###############################
.PHONY = release 
release: CFLAGS = -ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3
release: librelease.a

####### Static Librarry ######
%.a: $(SRCS) $(HDRS) $(OBJECTS)
	ar -rcs $@ $(OBJECTS)

#######   Executable  ########
%.out: %.o $(LIB)
	$(CC) $(CFLAGS) $< $(LIB) -o $@ $(LDFLAGS)

#######     Object    ########
%.o: %.d
	$(CC) $< -c -o $@

#################
%.d: %.c
	$(CC) -MM $< > $@


.PHONY = include
include:
	ln -sf $(DIR)/*.h $(DIR)/includes

####### Libraries #######
.PHONY = libs 
libs: $(SRCS) $(HDRS) $(LIBS)
	ln -sf $(DIR)/*.a $(DIR)/lib

#######   Test    #######
.PHONY = test
test: $(EXEC)
	ln -sf $(DIR)/*.out $(DIR)/test

#######   Clean   #######
.PHONY = clean
clean:
	find . -name '*.out' -delete
	find . -name '*.o'   -delete
	find . -name '*.so'  -delete
	find . -name '*.a'   -delete
	find . -name '*.d'   -delete

#gd wd_shared.c -o libwd_shared.so  -fPIC -shared -c 
#gd wd_test.c wd.o wd_shared.so wd_main.a -lpthread
#gd wd.c -o watchdog.o wd_shared.so libdebug.a -lpthread
#gd wd_exec.c wd_shared.so wd_main.a

