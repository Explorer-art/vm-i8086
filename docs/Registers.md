# Регистры процессора Intel 8086
Здесь описаны все регистры процессора Intel 8086

### Регистры данных
AX = 0xB8			AH = 0xB4		AL = 0xB0
CX = 0xB9			CH = 0xB5		CL = 0xB1
DX = 0xBA			DH = 0xB6		DL = 0xB2
BX = 0xBB			BH = 0xB7		BL = 0xB3

### Регистры указателей и индексов
SP = 0xBC
BP = 0xBD
SI = 0xBE
DI = 0xBF

### Сегментные регистры
CS = 0xC8
DS = 0xD8
SS = 0xD0
ES = 0xC0

### Указатель инструкций
IP

### Регистр флагов
15		  11  10  9   8   7   6  15			4  3		 2  1  		 0
Reserved  OF  DF  IF  TF  SF  ZF Reserved   AF Reserved  PF   Reserved   CF