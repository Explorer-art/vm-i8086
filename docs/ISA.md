# Instructions Set Architecture (ISA) Intel 8086

Архитектура набора инструкций процессора Intel 8086

### MOV
Пересылка данных
- Из регистра в регистр. Пример: mov bx, ax

```
mov ax, ax = 89 C0
mov ax, bx = 89 D8
mov ax, cx = 89 C8
mov ax, dx = 89 D0
mov bx, ax = 89 C3
mov bx, bx = 89 DB
mov bx, cx = 89 CB
mov bx, dx = 89 D3
mov cx, ax = 89 C1
mov cx, bx = 89 D9
mov cx, cx = 89 C9
mov cx, dx = 89 D1
mov dx, ax = 89 C2
mov dx, bx = 89 DA
mov dx, cx = 89 CA
mov dx, dx = 89 D2
```

- Число в регистр. Пример: mov ax, 100h

```
mov ax, 100h = B8 00 01
```

### ADD
Сложение

```
add ax, ax = 01 C0
add ax, bx = 01 D8
add ax, cx = 01 C8
add ax, dx = 01 D0
add bx, ax = 01 C3
add bx, bx = 01 DB
add bx, cx = 01 CB
add bx, dx = 01 D3
add cx, ax = 01 C1
add cx, bx = 01 D9
add cx, cx = 01 C9
add cx, dx = 01 D1
add dx, ax = 01 C2
add dx, bx = 01 DA
add dx, cx = 01 CA
add dx, dx = 01 D2
```

### SUB
Вычитание

```
sub ax, ax = 29 C0
```

### INC
Инкрементировать регистр

```
inc ax = 40
inc bx = 43
inc cx = 41
inc dx = 42
```

inc [8 bit regs] = FE [reg]
```
inc al = FE C0
```
### CLI = 0xFA
Отключение прерываний. Disable interrupts.

### STI = 0xFB
Включение прерываний. Enable interrupts.

### NOP = 0x90
Пустая операция. No operation.

### HLT = 0xF4
Останов. Halt processor execution.