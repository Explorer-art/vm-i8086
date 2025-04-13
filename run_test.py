import os
import sys

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
					print(f"[FAIL] {test}: expected {key}={tests[test][key]}, got {key}={registers.get(key)}")
		else:
			print(f"[PASS] {test}")

if __name__ == "__main__":
	run_test()