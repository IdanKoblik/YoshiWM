CC          = gcc
CFLAGS      = -Wall -I/usr/include/X11 -Iexternals/tomlc99
LDFLAGS     = -L/usr/lib -lX11 -lm

BUILDDIR    = build

# Main source files
SRCFILES    = $(filter-out stb_image.c, $(wildcard *.c))
OBJFILES    = $(patsubst %.c,$(BUILDDIR)/%.o,$(SRCFILES))

# Include tomlc99 source files
TOMLC99_SRC = externals/tomlc99/toml.c
TOMLC99_OBJ = $(BUILDDIR)/toml.o

# Include stb_image_impl source file
STB_IMAGE_SRC = stb_image.c
STB_IMAGE_OBJ = $(BUILDDIR)/stb_image.o

EXEC        = YoshiWm

all: $(BUILDDIR)/$(EXEC)

$(BUILDDIR)/$(EXEC): $(OBJFILES) $(TOMLC99_OBJ) $(STB_IMAGE_OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJFILES) $(TOMLC99_OBJ) $(STB_IMAGE_OBJ) $(LDFLAGS)

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TOMLC99_OBJ): $(TOMLC99_SRC)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(TOMLC99_SRC) -o $(TOMLC99_OBJ)

$(STB_IMAGE_OBJ): $(STB_IMAGE_SRC)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(STB_IMAGE_SRC) -o $(STB_IMAGE_OBJ)

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean