make:
	make build

build:
	mkdir -p bin
	gcc -o ./bin/text main.c -lncurses
	make run

run:
	./bin/text

vector:
	gcc -o ./bin/vector char_vector.c
	./bin/vector
