demo: demo.c core.o
	gcc -o demo demo.c core.o `pkg-config --cflags --libs sdl cairo`
core.o: core.c config.h
	gcc -c core.c `pkg-config --cflags --libs sdl cairo`