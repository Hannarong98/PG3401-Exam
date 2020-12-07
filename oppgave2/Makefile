# Use this for the exam
# Remember to:
	# Have these directories: include and obj
	# Lists all needed headerfiles to _DEPS
	# Lists all objectfiles to _OBJS
	# Rename output executable

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

#Headerfiles goes below
_DEPS = bubblesort.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

#Objectfiles goes below
_OBJS = oppgave2.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

oppgave2: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f oppgave2 $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
