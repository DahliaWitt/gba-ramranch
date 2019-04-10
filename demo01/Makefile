CFLAGS = -c -O3
MODEL = -mthumb -mthumb-interwork 
all : demo01.bin

demo01.bin: demo01.elf
	objcopy -O binary demo01.elf demo01.bin

demo01.elf : main.o sfx.o
    gcc -Tlnkscript $(MODEL) -o demo01.elf main.o sfx.o

sfx.o: sfx.c sfx.h gba.h
    gcc $(CFLAGS) $(MODEL) sfx.c

main.o: main.c sfx.h gba.h
	gcc $(CFLAGS) $(MODEL) main.c
