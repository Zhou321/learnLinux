OBJS:=main.o multi.o 
ELF:=main
CC:=gcc
CFLAGS:=-Wall -O2 -g
$(ELF):$(OBJS)
	gcc -o $@ $^
clean:
	rm -rf $(ELF) $(OBJS)

