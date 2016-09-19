The first section of the makefile uses conditionals to select one among the following compilers
•	gcc
•	arm-linux-gnueabi-gcc
•	arm-none-eabi

The user can specify this using one of the following compile time switches
bbb for Beagle Bone Black
frdm for KL25Z
host for gcc

eg. make build ARCH=bbb

where build is the target name and ARCH specifies the compiler selection

Multiple CFLAGS are defined for various scenarios such as preprocessing, assembly and linking. The source files are defined under SOURCES.

The first target is preprocess which generates preprocessed output from the compiler using the -E -o switches for gcc.

eg. make preprocess
eg. make memory.i

Similarly the second target is asm-file which generates assembly output from the compiler using the -S -o switches for gcc.

eg. make asm-file
eg. make data.S

The third target is %.o which is used to generate the object files and the corresponding dependencies.

eg. make memory.o

The compile-all target compiles all the files and creates the corresponding dependencies.

eg. make compile-all

The build target creates a map file called project.map and the executable named project. It also displays the size parameters for the executable file.

eg. make build

The upload target uses SCP to transfer the executable file to the Beagle Bone Black. It has been assumed that the Beagle Bone is already connected over SSH.

To connect the Beagle Bone using SSH use : sudo ssh root@192.168.7.2

eg. make upload

The build-lib target creates a static library named libproject1.a from memory.o and data.o

eg. make build-lib

The clean target deletes all the files generated during the intermediate processes.

eg. make clean