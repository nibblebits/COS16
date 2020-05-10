AS=nasm
CC=bcc
LD=ld86
INC=./src
SRC=./src
OBJECTS= ./build/kernel.o ./build/display.o ./build/displayasm.o ./build/memory/memory.o ./build/string/string.o  ./build/fs/file.o ./build/fs/fat/fat16.o
INC=./src
CFLAGS=-0 -I$(INC) -ansi -c 

all: ./bin/boot.bin ./bin/kernel.bin
	rm -f ./bin/os.bin
	dd if=./bin/boot.bin >> ./bin/os.bin
	dd if=./bin/kernel.bin >> ./bin/os.bin
	dd if=/dev/zero bs=1048576 count=16 >> ./bin/os.bin

./bin/boot.bin: ./src/boot.asm
	nasm -f bin ./src/boot.asm -o ./bin/boot.bin

./build/kernel.o: ./src/kernel.c ./src/kernel.h
	$(CC) $(CFLAGS) $(SRC)/kernel.c -o ./build/kernel.o

./build/display.o: ./src/display.c ./src/display.h
	$(CC) $(CFLAGS) $(SRC)/display.c -o ./build/display.o

./build/displayasm.o: ./src/display.asm
	nasm -f as86 ./src/display.asm -o ./build/displayasm.o

./build/memory/memory.o: ./src/memory/memory.c ./src/memory/memory.h
	$(CC) $(CFLAGS) -I./src/memory $(SRC)/memory/memory.c -o ./build/memory/memory.o

./build/string/string.o: ./src/string/string.c ./src/string/string.h
	$(CC) $(CFLAGS) -I./src/string $(SRC)/string/string.c -o ./build/string/string.o

./build/fs/file.o: ./src/fs/file.c ./src/fs/file.h
	$(CC) $(CFLAGS) -I./src/fs $(SRC)/fs/file.c -o ./build/fs/file.o

./build/fs/fat/fat16.o: ./src/fs/fat/fat16.c ./src/fs/fat/fat16.h
	$(CC) $(CFLAGS) -I./fs/fat $(SRC)/fs/fat/fat16.c -o ./build/fs/fat/fat16.o

./bin/kernel.bin: ${OBJECTS} 
	$(LD) -d -M ${OBJECTS} -L/usr/lib/bcc/ -lc -o ./bin/kernel.bin

clean:
	rm -f ./bin/boot.bin
	rm -f ./bin/kernel.bin
	rm -f ./bin/os.bin
	rm -f ${OBJECTS}

run:
