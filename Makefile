CC      = gcc
CFLAGS  = -g
RM      = rm -rf
OBJDIR  = build/
SRCDIR  = ray_tracing/

default: all

all: $(OBJDIR)main

$(OBJDIR)main: $(OBJDIR)colour.o $(OBJDIR)vec3.o
	$(CC) $(CFLAGS) -o $(OBJDIR)main $(SRCDIR)main.c $(OBJDIR)colour.o $(OBJDIR)vec3.o

$(OBJDIR)colour.o: $(SRCDIR)colour.c $(SRCDIR)colour.h
	$(CC) $(CFLAGS) -c $(SRCDIR)colour.c -o $(OBJDIR)colour.o

$(OBJDIR)vec3.o: $(SRCDIR)vec3.c $(SRCDIR)vec3.h
	$(CC) $(CFLAGS) -c $(SRCDIR)vec3.c -o $(OBJDIR)vec3.o

clean:
	$(RM) $(OBJDIR)main $(OBJDIR)colour.o $(OBJDIR)vec3.o $(OBJDIR)main.dSYM