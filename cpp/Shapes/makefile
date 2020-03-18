CC= g++
CFLAGS= -std=c++98 -Wall -Wextra

CPP_FILES= shape.cpp square.cpp test.cpp line.cpp rectangle.cpp \
							circle.cpp composit.cpp

VPATH= src

shapes.out: $(CPP_FILES) 
	$(CC) $(CFLAGS) $^ -o $@ -Iinclude -Wl,-rpath=. lib/libpoint.a \
						lib/libglut_utils.so



