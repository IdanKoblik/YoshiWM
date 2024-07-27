CC          = gcc
CFLAGS      = -Wall -I/usr/include/X11
LDFLAGS     = -L/usr/lib -lX11


BUILDDIR	= build

SRCFILES 	= $(wildcard *.c)
OBJFILES    = $(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(SRCFILES)))

EXEC 		= YoshiWm

all: $(BUILDDIR)/$(EXECUTABLE)

$(BUILDDIR)/$(EXEC): $(OBJFILES)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXEC)
