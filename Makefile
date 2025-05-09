all: clean vm

vm:
	gcc src/main.c src/cpu.c src/isa.c src/utils.c -o vm-i8086 -I src/include

test: clean_test
	nasm -f bin tests/test.asm -o tests/test

clean:
	rm -f vm

clean_test:
	rm -f tests/test