import os
import sys

RED = "\033[31m"
GREEN = "\033[32m"
RESET = "\033[0m"

TESTS_DIRECTORY = "tests"
REGISTERS_DUMP_FILE = "registers.dump"

tests = {
	"mov_low.bin": {
		"AL": 5, "BL": 8, "CL": 5, "DL": 8,
		"AH": 0, "BH": 0, "CH": 0, "DH": 0,
		"AX": 5, "BX": 8, "CX": 5, "DX": 8
	},
	"mov_high.bin": {
		"AL": 0, "BL": 0, "CL": 0, "DL": 0,
		"AH": 2, "BH": 5, "CH": 2, "DH": 5,
		"AX": 512, "BX": 1280, "CX": 512, "DX": 1280
	},
	"mov_base.bin": {
		"AL": 1, "BL": 8, "CL": 1, "DL": 8,
		"AH": 0, "BH": 0, "CH": 0, "DH": 0,
		"AX": 1, "BX": 8, "CX": 1, "DX": 8
	},
	"add_low.bin": {
		"AL": 10, "BL": 7, "CL": 10, "DL": 0,
		"AH": 0,  "BH": 0, "CH": 0,  "DH": 0,
		"AX": 10, "BX": 7, "CX": 10, "DX": 0
	},
	"add_high.bin": {
		"AL": 0,   "BL": 0,  "CL": 0,  "DL": 0,
		"AH": 7,   "BH": 5,  "CH": 7,  "DH": 0,
		"AX": 1792,"BX": 1280,"CX": 1792,"DX": 0
	},
	"add_base.bin": {
		"AL": 15,  "BL": 10, "CL": 15, "DL": 0,
		"AH": 0,   "BH": 0,  "CH": 0,  "DH": 0,
		"AX": 15,  "BX": 10, "CX": 15, "DX": 0
	},
	"sub_low.bin": {
		"AL": 5,  "BL": 3, "CL": 5,  "DL": 0,
		"AH": 0,  "BH": 0, "CH": 0,  "DH": 0,
		"AX": 5,  "BX": 3, "CX": 5,  "DX": 0
	},
	"sub_high.bin": {
		"AL": 0,  "BL": 0,  "CL": 0,  "DL": 0,
		"AH": 5,  "BH": 2,  "CH": 5,  "DH": 0,
		"AX": 1280, "BX": 512, "CX": 1280, "DX": 0
	},
	"sub_base.bin": {
		"AL": 14,  "BL": 6, "CL": 14, "DL": 0,
		"AH": 0,   "BH": 0, "CH": 0,  "DH": 0,
		"AX": 14,  "BX": 6, "CX": 14, "DX": 0
	},
	"inc_low.bin": {
		"AL": 5,  "BL": 9,  "CL": 5,  "DL": 9,
		"AH": 0,  "BH": 0,  "CH": 0,  "DH": 0,
		"AX": 5,  "BX": 9,  "CX": 5,  "DX": 9
	},
	"inc_high.bin": {
		"AL": 0,  "BL": 0,  "CL": 0,   "DL": 0,
		"AH": 2,  "BH": 7,  "CH": 2,   "DH": 7,
		"AX": 512, "BX": 1792, "CX": 512, "DX": 1792
	},
	"inc_base.bin": {
		"AL": 11, "BL": 4,  "CL": 11, "DL": 4,
		"AH": 0,  "BH": 0,  "CH": 0,  "DH": 0,
		"AX": 11, "BX": 4,  "CX": 11, "DX": 4
	},
	"dec_low.bin": {
		"AL": 5,  "BL": 2,  "CL": 5,  "DL": 2,
		"AH": 0,  "BH": 0,  "CH": 0,  "DH": 0,
		"AX": 5,  "BX": 2,  "CX": 5,  "DX": 2
	},
	"dec_high.bin": {
		"AL": 0,   "BL": 0,  "CL": 0,   "DL": 0,
		"AH": 8,   "BH": 3,  "CH": 8,   "DH": 3,
		"AX": 2048,"BX": 768,"CX": 2048,"DX": 768
	},
	"dec_base.bin": {
		"AL": 19,  "BL": 12, "CL": 19, "DL": 12,
		"AH": 0,   "BH": 0,  "CH": 0,  "DH": 0,
		"AX": 19,  "BX": 12, "CX": 19, "DX": 12
	},
	"and_low.bin": {
		"AL": 0b10100000, "BL": 0, "CL": 0b10100000, "DL": 0,
		"AH": 0, "BH": 0, "CH": 0, "DH": 0,
		"AX": 0b10100000, "BX": 0, "CX": 0b10100000, "DX": 0
	},
	"and_high.bin": {
		"AL": 0, "BL": 0, "CL": 0, "DL": 0,
		"AH": 0b10001000, "BH": 0, "CH": 0b10001000, "DH": 0,
		"AX": 0b10001000 << 8, "BX": 0, "CX": 0b10001000 << 8, "DX": 0
	},
	"and_base.bin": {
		"AL": 0xFF, "BL": 0, "CL": 0xFF, "DL": 0,
		"AH": 0, "BH": 0, "CH": 0, "DH": 0,
		"AX": 0x00FF, "BX": 0, "CX": 0x00FF, "DX": 0
	},
	"or_low.bin": {
		"AL": 0xFF, "BL": 0, "CL": 0xFF, "DL": 0,
		"AH": 0, "BH": 0, "CH": 0, "DH": 0,
		"AX": 0xFF, "BX": 0, "CX": 0xFF, "DX": 0
	},
	"or_high.bin": {
		"AL": 0, "BL": 0, "CL": 0, "DL": 0,
		"AH": 0x0F, "BH": 0, "CH": 0x0F, "DH": 0,
		"AX": 0x0F << 8, "BX": 0, "CX": 0x0F << 8, "DX": 0
	},
	"or_base.bin": {
		"AL": 0xFF, "BL": 0, "CL": 0xFF, "DL": 0,
		"AH": 0xFF, "BH": 0, "CH": 0xFF, "DH": 0,
		"AX": 0xFFFF, "BX": 0, "CX": 0xFFFF, "DX": 0
	},

	"not_low.bin": {
		"AL": 0x0F, "BL": 0, "CL": 0x0F, "DL": 0,
		"AH": 0, "BH": 0, "CH": 0, "DH": 0,
		"AX": 0x0F, "BX": 0, "CX": 0x0F, "DX": 0
	},
	"not_high.bin": {
		"AL": 0, "BL": 0, "CL": 0, "DL": 0,
		"AH": 0x55, "BH": 0, "CH": 0x55, "DH": 0,
		"AX": 0x55 << 8, "BX": 0, "CX": 0x55 << 8, "DX": 0
	},
	"not_base.bin": {
		"AL": 0xF0, "BL": 0, "CL": 0xF0, "DL": 0,
		"AH": 0xF0, "BH": 0, "CH": 0xF0, "DH": 0,
		"AX": 0xF0F0, "BX": 0, "CX": 0xF0F0, "DX": 0
	}
}

def load_registers_dump(filename):
	registers = {}

	with open(filename, "r") as file:
		lines = file.readlines()

		for line in lines:
			line_splited = line.split(":")
			register_name = line_splited[0]
			value = int(line_splited[1], 0)

			registers[register_name] = value

	return registers

def run_test():
	for test in tests:
		if not os.path.exists(f"{TESTS_DIRECTORY}/{test}"):
			print(f"Error: file {TESTS_DIRECTORY}/{test} not exists")
			sys.exit()

		os.system(f"./vm-i8086 {TESTS_DIRECTORY}/{test} -rd")

		registers = load_registers_dump(REGISTERS_DUMP_FILE)

		if registers != tests[test]:
			for key in tests[test]:
				if tests[test][key] != registers.get(key):
					print(f"{RED}[FAIL]{RESET} {test}: expected {key}={hex(tests[test][key])}, got {key}={hex(registers.get(key))}")
		else:
			print(f"{GREEN}[PASS]{RESET} {test}")

if __name__ == "__main__":
	run_test()