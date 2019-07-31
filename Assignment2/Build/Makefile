TARGET = kernel7.img
ELFILE = myos.elf
CC = arm-none-eabi-gcc.exe
OC = arm-none-eabi-objcopy.exe
EM = qemu-system-arm.exe
CPU = cortex-a7
MEM = 1024

SHELL = C:/Windows/system32/cmd.exe

CFLAGS = -mcpu=$(CPU) -fpic -ffreestanding -Wall
EMFLAGS = -m $(MEM) -M raspi2 -serial stdio -kernel $(OBJS_DIR)/$(ELFILE)
CSRCFLAGS = -g -O2 -Wall -Wextra
LFLAGS = -ffreestanding -O2 -nostdlib

SRC_CMN_DIR = ../Source/Common
SRC_KER_DIR = ../Source/Kernel
INC_CMN_DIR = ../Include/Common
INC_KER_DIR = ../Include/Kernel
OBJS_DIR = Objects
EM_DIR = D:\QEMU-embedded2\qemu
CC_DIR = C:/Program Files (x86)/GNU Tools ARM Embedded/8 2019-q3-update/bin

all: $(TARGET)

#convert the elf file to an img file
$(TARGET) : $(OBJS_DIR)/$(ELFILE)
	@$(CC_DIR)/$(OC) $(OBJS_DIR)/$(ELFILE) -O binary $(OBJS_DIR)/$(TARGET)
	@echo Kernel Image File: $(TARGET) created

#link all the objects file, output ELFILE
$(OBJS_DIR)/$(ELFILE) : $(OBJS_DIR)/boot.o $(OBJS_DIR)/uart.o $(OBJS_DIR)/kernel.o $(OBJS_DIR)/stdio.o $(OBJS_DIR)/stdlib.o
	@echo Linking Objects Files: $^
	@$(CC_DIR)/$(CC) -T linker.ld -o $(OBJS_DIR)/$(ELFILE) $(LFLAGS) $^
	@echo Extensible Linkable Format File: $@ created

#Compile all assembly sources files, located in one directory
$(OBJS_DIR)/%.o : $(SRC_KER_DIR)/%.s
	@echo Compiling Assembler Source File $<
	@$(CC_DIR)/$(CC) $(CFLAGS) -c $< -o $@

#Compile C source file containing "kernel_main" function
$(OBJS_DIR)/%.o : $(SRC_KER_DIR)/%.c
	@echo Compiling C Sourcefile $<
	@$(CC_DIR)/$(CC) $(CFLAGS) -I$(INC_CMN_DIR) -I$(INC_KER_DIR) -c $< -o $@ $(CSRCFLAGS)

#Compile all C sources files from Source/Kernel
$(OBJS_DIR)/%.o : $(SRC_KER_DIR)/%.c $(INC_KER_DIR)/%.h
	@echo Compiling C Sourcefile $<
	@$(CC_DIR)/$(CC) $(CFLAGS) -I$(INC_CMN_DIR) -I$(INC_KER_DIR) -c $< -o $@ $(CSRCFLAGS)

#Compile all C source files from Source/Common 
$(OBJS_DIR)/%.o : $(SRC_CMN_DIR)/%.c $(INC_CMN_DIR)/%.h
	@echo Compiling C Sourcefile $<
	@$(CC_DIR)/$(CC) $(CFLAGS) -I$(INC_CMN_DIR) -I$(INC_KER_DIR) -c $< -o $@ $(CSRCFLAGS)

.PHONY: clean run

clean:
	@echo Removing Objects Files $(wildcard $(OBJS_DIR)/*.o)
	@del $(OBJS_DIR)\*.o
	@echo Removing $(ELFILE)
	@del $(OBJS_DIR)\$(ELFILE)
	@echo Removing $(TARGET)
	@del $(OBJS_DIR)\$(TARGET)

run: $(OBJS_DIR)/$(ELFILE)
	$(EM_DIR)/$(EM) $(EMFLAGS)

