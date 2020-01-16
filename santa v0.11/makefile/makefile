srcdir=../srcs/
objdir=../objs/
libdir=../lib/
incdir=../include/

SRCS = $(wildcard $(srcdir)*.cpp)
OBJS = $(patsubst $(srcdir)%.cpp, $(objdir)%.o, $(SRCS))
DEPS = $(patsubst $(srcdir)%.cpp, %.d ,$(SRCS))
BIN = ../ver0.out
CPP = g++
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -std=c++11 \
-D_POSIX_C_SOURCE=199506L -D_XOPEN_SOURCE=500 -D_POSIX_SOURCE
LDFLAGS = -pthread

GLOB_SRC 	:= globals.cpp
GLOB_OBJ 	:= lib$(GLOB_SRC:.cpp=.so)

LIB_PATH 	  := $(shell pwd)
FLG_LINK_GLOB := -L$(LIB_PATH)


DO_DEBUG ?= 1
ifeq ($(DO_DEBUG), 1)
	CFLAGS += -DDO_DEBUG -g
endif


$(BIN): $(OBJS)
	$(CPP) $(CFLAGS) -o $@ $^ $(LDFLAGS)


libglobals.so: ../srcs/globals.cpp 
	$(CPP) $(CFLAGS) -I$(incdir) -fPIC -c $<  -shared -o  libglobals.so


-include $(DEPS)
-include flags.conf

%.d: $(srcdir)%.cpp
	$(CPP) $(CFLAGS) -I$(incdir) -MM -MT $(patsubst %.d, $(objdir)%.o, $@) $< > $@ 
	echo "\t"$(CPP) $(CFLAGS) -c -I$(incdir) -o $(patsubst %.d, $(objdir)%.o ,$@) $< >> $@

.PHONY: clean

clean:
	rm  $(objdir)* $(BIN) *.d *.so


