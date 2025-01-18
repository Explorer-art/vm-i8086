all: clean vm

vm:
	gcc vm.c -o vm

test: clean_test
	nasm -f bin tests/test.asm -o tests/test

clean:
	rm -f vm

clean_test:
	rm -f tests/test