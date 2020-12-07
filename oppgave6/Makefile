# Use this for the exam
# Remember to:
	# Have these directories: include and obj
	# Lists all needed headerfiles to _DEPS
	# Lists all objectfiles to _OBJS

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)
CFLAGS += -lpthread -Wno-unused-result

OBJDIR = obj

#Headerfiles goes below
_DEPS =
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

#Objectfiles goes below
_OBJS = oppgave6.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

oppgave6: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f oppgave6 $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
