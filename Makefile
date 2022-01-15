default:
	gcc src/string.c src/login_screen.c src/main.c -lncurses -o build/main

run:
	./build/main

