default:
	gcc src/main.c -lncurses -o build/main

run:
	./build/main

