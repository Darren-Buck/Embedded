all: hello_world

hello_world.: hello_world.0
	gcc -o hello_world hello_world.o

hello_world.o: hello_world.c
	gcc -c hello_world.c

clean:
	rm -f hello_world.o hello_world