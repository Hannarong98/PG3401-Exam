# Use this for the exam
# Remember to:
	# Have these directories: include and obj
	# Lists all needed headerfiles to _DEPS
	# Lists all objectfiles to _OBJS

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)
CFLAGS += -Wno-unused-result


OBJDIR = obj

#Headerfiles goes below
_DEPS =
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

#Objectfiles goes below
_OBJS = server.o client.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJS)
	$(CC) -o client client.c $(CFLAGS)
	$(CC) -o server server.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f a.out client server $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
