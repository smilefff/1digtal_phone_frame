
CROSS_COMPILE = arm-linux-

AS			= $(CROSS_COMPILE)as

LD			= $(CROSS_COMPILE)ld

CC			= $(CROSS_COMPILE)gcc

CPP			= $(CC) -E

AR			= $(CROSS_COMPILE)ar

NM			= $(CROSS_COMPILE)nm

 

STRIP		= $(CROSS_COMPILE)strip

OBJCOPY		= $(CROSS_COMPILE)objcopy

OBJDUMP		= $(CROSS_COMPILE)objdump



export AS LD CC CPP AR NM

export STRIP OBJCOPY OBJDUMP

 

CFLAGS := -Wall -O2 -g

CFLAGS += -I $(shell pwd)/include

LDFLAGS := 

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)

export TOPDIR

TARGET := dig

obj-y += main.o
obj-y += display/

all :
	make -C ./ -f $(TOPDIR)/Makefile.build
	$(CC) $(LDFLAGS) -o $(TARGET) built-in.o
	
cp :
	cp ../1digtal_phone_frame/* /root/rootfs/2rootfs/rootfs/root/phone/ -rf

clean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)



