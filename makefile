#CC = gcc
#CFLAGS = -g -Wall -Wextra $(shell pkg-config --cflags sdl2)
#LIBS = $(shell pkg-config --libs sdl2)

#all:
#	$(CC) main.c init.c -o out $(CFLAGS) $(LIBS)

all:
	meson setup build --wipe
	ninja -C build
