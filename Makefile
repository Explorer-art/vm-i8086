all: clean vm

vm:
	gcc src/vm.c -o vm -I src/include

test: clean_test
	nasm -f bin tests/test.asm -o tests/test

clean:
	rm -f vm

clean_test:
	rm -f tests/test