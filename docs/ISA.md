# Instructions Set Architecture (ISA) Intel 8086

Архитектура набора инструкций процессора Intel 8086

### MOV
Пересылка данных
- Из регистра в регистр. Пример: mov bx, ax

16 REGs
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

8 REGs
```
mov al, al = 88 C0
mov al, bl = 88 D8
mov al, cl = 88 C8
mov al, dl = 88 D0
mov bl, al = 88 C3
mov bl, bl = 88 DB
mov bl, cl = 88 CB
mov bl, dl = 88 D3
mov cl, al = 88 C1
mov cl, bl = 88 D9
mov cl, cl = 88 C9
mov cl, dl = 88 D1
mov dl, al = 88 C2
mov dl, bl = 88 DA
mov dl, cl = 88 CA
mov dl, dl = 88 D2
mov ah, ah = 88 E4
mov ah, bh = 88 FC
mov ah, ch = 88 EC
mov ah, dh = 88 F4
mov bh, ah = 88 E7
mov bh, bh = 88 FF
mov bh, ch = 88 EF
mov bh, dh = 88 F7
mov ch, ah = 88 E5
mov ch, bh = 88 FD
mov ch, ch = 88 ED
mov ch, dh = 88 F5
mov dh, ah = 88 E6
mov dh, bh = 88 FE
mov dh, ch = 88 EE
mov dh, dh = 88 F6
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
add al, al = 00 C0
add al, bl = 00 D8
add al, cl = 00 C8
add al, dl = 00 D0
add bl, al = 00 C3
add bl, bl = 00 DB
add bl, cl = 00 CB
add bl, dl = 00 D3
add cl, al = 00 C1
add cl, bl = 00 D9
add cl, cl = 00 C9
add cl, dl = 00 D1
add dl, al = 00 C2
add dl, bl = 00 DA
add dl, cl = 00 CA
add dl, dl = 00 D2
```

### SUB
Вычитание

```
sub ax, ax = 29 C0
sub ax, bx = 29 D8
sub ax, cx = 29 C8
sub ax, dx = 29 D0
sub bx, ax = 29 C3
sub bx, bx = 29 DB
sub bx, cx = 29 CB
sub bx, dx = 29 D3
sub cx, ax = 29 C1
sub cx, bx = 29 D9
sub cx, cx = 29 C9
sub cx, dx = 29 D1
sub dx, ax = 29 C2
sub dx, bx = 29 DA
sub dx, cx = 29 CA
sub dx, dx = 29 D2
sub al, al = 28 C0
sub al, bl = 28 D8
sub al, cl = 28 C8
sub al, dl = 28 D0
sub bl, al = 28 C3
sub bl, bl = 28 DB
sub bl, cl = 28 CB
sub bl, dl = 28 D3
sub cl, al = 28 C1
sub cl, bl = 28 D9
sub cl, cl = 28 C9
sub cl, dl = 28 D1
sub dl, al = 28 C2
sub dl, bl = 28 DA
sub dl, cl = 28 CA
sub dl, dl = 28 D2s
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