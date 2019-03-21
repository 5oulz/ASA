#Makefile

SOURCES = main.c GRAPHlst.c stack.c
OBJS = $(SOURCES:%.c=%.o)
CC   = gcc
CFLAGS =-Wall -g -std=gnu99 -I../
LDFLAGS=-lm
TARGET = proj

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS) 

main.o: main.c GRAPH.h
GRAPHlst.o: GRAPHlst.c GRAPH.h
stack.o: stack.c GRAPH.h

$(OBJS):
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo Cleaning...
	rm -f $(OBJS) $(TARGET)


