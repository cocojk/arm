# makefile generated by mcp2make 1.0.2

CC=armcc
LD=armlink
#CORE=ARM720T
CORE=ARM920T

CCFLAGS = -O1 -g+ -cpu $(CORE)
LDFLAGS = -ro-base 0x10000

OBJS = mmuRoutines.o main.o

all: mmu.axf


rebuild: clean all

clean:
	rm *.o *.axf

mmu.axf: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o mmu.axf

mmuRoutines.o: mmuRoutines.c regions.h mmu.h
	$(CC) -c $(CCFLAGS) mmuRoutines.c -o mmuRoutines.o

main.o: main.c regions.h mmu.h
	$(CC) -c $(CCFLAGS) main.c -o main.o

