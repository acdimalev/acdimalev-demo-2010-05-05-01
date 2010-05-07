all: demo-1 demo-2 demo-3
demo-1: demo-1.c core.h core.o
	gcc -o demo-1 demo-1.c core.o `pkg-config --cflags --libs sdl cairo`
demo-2: demo-2.c core.h core.o
	gcc -o demo-2 demo-2.c core.o `pkg-config --cflags --libs sdl cairo`
demo-3: demo-3.c core.h core.o
	gcc -o demo-3 demo-3.c core.o `pkg-config --cflags --libs sdl cairo`
core.o: core.c core.h config.h
	gcc -c core.c `pkg-config --cflags --libs sdl cairo`
