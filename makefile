ifeq ($(ARCH),bbb) #Checking for beagle bone
	PREFIX:=arm-linux-gnueabi-
else ifeq ($(ARCH),frdm) #Checking for KL25Z
	PREFIX:= arm-none-eabi-
endif

CFLAGS1:=-E -o #first set of CFLAGS for preprocessing
CFLAGS2:=-S -o #second set of CFLAGS for assembly files
SOURCE:=memory.c data.c project_1.c main.c #list of source files
ifeq ($(ARCH),frdm)
	CC:=$(PREFIX)gcc -Dfrdm -DPROJECT_1 -std=c99
else
	CC:=$(PREFIX)gcc -DPROJECT_1 -std=c99
endif

SIZE:=$(PREFIX)size #specifying the right command for size fucntion
OBJECTDUMP:=$(PREFIX)objdump # specifying the right command for object dump
CFLAGS:=-c -Wall -g -O0 #third set of CFLAGS for te object files

.phony:preprocess

preprocess:$(SOURCE) #generating preprocessed output
	$(CC) memory.c $(CFLAGS1) memory.i
	$(CC) data.c $(CFLAGS1) data.i
	$(CC) project_1.c $(CFLAGS1) project_1.i
	$(CC) main.c $(CFLAGS1) main.i

%.i:%.c
	$(CC) $^ $(CFLAGS1) $@

.phony:asm-file

asm-file:$(SOURCE) #generating assembly output
	$(CC) memory.c $(CFLAGS2) memory.s
	$(CC) data.c $(CFLAGS2) data.s
	$(CC) project_1.c $(CFLAGS2) project_1.s
	$(CC) main.c $(CFLAGS2) main.s

%.s:%.c
	$(CC) $^ $(CFLAGS2) $@

%.o:%.c#generating object files and dependencies
	$(CC) $^ $(CFLAGS)
	$(CC) -MM $*.c > $*.dep
	$(OBJECTDUMP) -d -M intel -S $@

.phony:compile-all

compile-all:$(SOURCE)
	$(CC) memory.c $(CFLAGS)
	$(CC) -MM memory.c > memory.dep
	$(CC) data.c $(CFLAGS)
	$(CC) -MM data.c > data.dep
	$(CC) project_1.c $(CFLAGS)
	$(CC) -MM project_1.c > project_1.dep
	$(CC) main.c $(CFLAGS)
	$(CC) -MM main.c > main.dep

.phony:build

build:$(SOURCE) #linking and generating map file
	$(CC) $(SOURCE) -Wl,-Map,project.map -Wall -g -o project
	$(SIZE) project

.phony:upload

upload:build #uses SCP to transfer the executable to BeagleBone ,assumes already connected via SSH
	scp project root@192.168.7.2:/home/debian/bin

.phony:build-lib

build-lib:memory.o data.o
	ar -r libproject1.a memory.o data.o
	ranlib libproject1.a

.phony:clean

clean:    #removes the generated files
	$(RM) *.o *.i *.s *.out *.map *.a *.dep main project

