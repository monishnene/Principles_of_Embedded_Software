ifeq	($(PLATFORM),HOST)
	CC=gcc
	flags=	-DVERBOSE
endif

ifeq	($(PLATFORM),BBB)
	CC=arm-linux-gnueabihf-gcc
	flags=	-DVERBOSE
endif

ifeq	($(PLATFORM),KL25Z)
	CC=arm-none-eabi-gcc
	flags=	-mthumb	-mfpu=fpv4-sp-d16	-specs=nosys.specs	-mcpu=cortex-m0	-march=armv6-m	-mfloat-abi=soft		
endif	

	cfiles=	main.c	project1.c	conversion.c	debug.c	memory.c	

	CCFLAGS=	$(flags)	-DPROJECT1	-Wall	-Werror	-g	-O0	-std=c99	-I /home/monish/PES_Project1  -lc	

build:	main.o	memory.o	debug.o	conversion.o	project1.o
	$(CC)	-o	project1	main.o	memory.o	debug.o	conversion.o	project1.o	$(CCFLAGS)

compile-all:	$(cfiles)	
	$(CC)	-c	$(cfiles)	$(CCFLAGS)

main.o:	main.c	project1.h	conversion.h	debug.h	memory.h	platform.h	
	$(CC)	-c	main.c	$(CCFLAGS)	

project1.o:	project1.c	debug.c	conversion.h	debug.h	memory.h	platform.h
	$(CC)	-c	project1.c	debug.c	$(CCFLAGS)	

conversion.o:	conversion.c	platform.h
	$(CC)	-c	conversion.c	$(CCFLAGS)	 

memory.o:	memory.c	platform.h
	$(CC)	-c	memory.c	$(CCFLAGS)	

debug.o:	debug.c	platform.h
	$(CC)	-c	debug.c	$(CCFLAGS)	

main.i:	main.c	project1.h	conversion.h	debug.h	memory.h	platform.h	
	$(CC)	-E	main.c	$(CCFLAGS)	

project1.i:	project1.c	debug.c	conversion.h	debug.h	memory.h	platform.h
	$(CC)	-E	project1.c	debug.c	$(CCFLAGS)	

conversion.i:	conversion.c	memory.h	platform.h
	$(CC)	-E	conversion.c	$(CCFLAGS)	

memory.i:	memory.c	platform.h
	$(CC)	-E	memory.c	$(CCFLAGS)	

debug.i:	debug.c	platform.h
	$(CC)	-E	debug.c	$(CCFLAGS)	

main.asm:	main.c	project1.h	conversion.h	debug.h	memory.h	platform.h	
	$(CC)	-S	main.c	$(CCFLAGS)	

project1.asm:	project1.c	debug.c	conversion.h	debug.h	memory.h	platform.h
	$(CC)	-S	project1.c	debug.c	$(CCFLAGS)	

conversion.asm:	conversion.c	memory.h	platform.h
	$(CC)	-S	conversion.c	$(CCFLAGS)	

memory.asm:	memory.c	platform.h
	$(CC)	-S	memory.c	$(CCFLAGS)	

debug.asm:	debug.c	platform.h
	$(CC)	-S	debug.c	$(CCFLAGS)	

.PHONY:	conversiontest.c	memory.c	debug.c		conversion.c	project1.c	main.c		

compile-all:


clean :
	rm	-f	*.o	*.s	*.e	
