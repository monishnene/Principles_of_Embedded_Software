	
	defined = -DPROJECT1	-DCMOCKA 

	common_sources= main.c \
			project1.c \
			conversion.c \
			debug.c	\
			memory.c\
			circbuf.c	
	
	common_includes= -I ../include/common\
			$(cmocka_includes)


	common_flags=	$(defined) \
			-Wall \
			-Werror \
			-g \
			-O0 \
			-std=c99 \
			-DVERBOSE \
	       		-lc\
			$(cmocka_flags) 

	objdir=../object
	srcdir=../src
	bindir=../bin
	asmdir=../asm
	depdir=../dep
	headdir=../header

ifeq	($(PLATFORM),BBB)
	CC=arm-linux-gnueabihf-gcc
	flags=	$(common_flags) \
		-mcpu=cortex-a8 \
		-mthumb \	
		-mfloat-abi=hard
	sources =	$(common_sources)
	includes =	$(common_includes)		
endif

ifeq	($(PLATFORM),KL25Z)
	CC=arm-none-eabi-gcc
	flags=	$(common_flags) \
		-mthumb \
		-mfpu=fpv4-sp-d16 \
		-specs=nosys.specs \
	 	-mcpu=cortex-m0 \
		-march=armv6-m	\
		-mfloat-abi=soft
		-Wl
		-Map=project1.map 
		-T ../platform/MKL25Z128xxx4_flash.ld	
	c_sources =	$(common_sources) \
			-system_MKL25Z4.c
	s_sources =	-startup_MKL25Z4.S
	sources =	$(c_sources) \
			$(s_sources)
	includes =	$(common_includes) \
			-I ../include/CMSIS\
			-I ../include/kl25z	

endif

ifeq	($(PLATFORM),HOST)
	CC=gcc
	flags=	$(common_flags)
	sources =	$(common_sources)
	includes =	$(common_includes)
else
	CC=gcc
	flags=	$(common_flags)
	sources =	$(common_sources)
	includes =	$(common_includes)
	
endif

ifeq ($(PLATFORM),KL25Z)
	OBJS:= $(c_sources:.c=.o) $(s_sources:.S=.o)
	C_DEPS:= $(c_sources:.c=.d) $(s_sources:.S=.d)
else
	objects:= $(sources:.c=.o)
	deps:= $(sources:.c=.d)	
endif

.PHONY:	compile-all \
	clean \
	build \
	upload\
	cmocka_test	(CC)	$(flags)	$(includes)	-E	$<	-o	$@

%.asm:%.c	
	$(CC)	$(flags)	$(includes)	-S	$<	-o	$@

%.o:%.c	
	$(CC)	$(flags)	$(includes)	-c	$<	-o	$@

%.o:%.s	
	$(CC)	$(flags)	$(includes)	-c	$<	-o	$@

%.d:%.c	
	$(CC)	$(flags)	$(includes)	-M	$<	-o	$@

%.d:%.s	
	$(CC)	$(flags)	$(includes)	-M	$<	-o	$@

build:	$(objects)	$(deps)
	$(CC) $(flags) $(includes)	-o	project1.elf	$(objects)

compile-all:	$(objects)

upload: 
	scp	project1.elf	root@192.168.7.2:~/home

cmocka_test:$(objects)	$(deps)
	$(CC)	cmocka_test.c	-lcmocka -o cmockatest $(includes) 
 
clean :
	rm	-f	*.o	*.s	*.i	*.o	*.d	*.elf *.swp
