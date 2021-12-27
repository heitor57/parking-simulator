MKDIR = mkdir -p
CC = gcc
CFLAGS	= -Wall -g
COFLAGS	= -Wall -c -g
OBJDIR = obj
PERFECT_OBJS = $(addprefix $(OBJDIR)/, perfect_main.o hash.o object.o io.o parking.o maneuvers.o collission.o time.o)
OBJS = $(addprefix $(OBJDIR)/, main.o hash.o object.o io.o parking.o maneuvers.o collission.o time.o)
GENERATOR_OBJS = $(addprefix $(OBJDIR)/,generator.o collission.o object.o io.o time.o)
LDFLAGS = -lm
MAIN_TARGET = parking-simulator
GENERATOR_TARGET = generator
PERFECT_TARGET = parking-simulator-perfect
vpath %.c  src
vpath %.h  src
.PHONY: directories
all: directories $(MAIN_TARGET) $(GENERATOR_TARGET) $(PERFECT_TARGET)
$(MAIN_TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(GENERATOR_TARGET): $(GENERATOR_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(PERFECT_TARGET): $(PERFECT_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(OBJDIR)/%.o: %.c %.h
	gcc $(COFLAGS) $< -o $@
$(OBJDIR)/%.o: %.c
	gcc $(COFLAGS) $< -o $@
directories: $(OBJDIR)
$(OBJDIR):
	$(MKDIR) $@
clean:
	rm -rf $(OBJDIR) 
	rm -f $(MAIN_TARGET) $(GENERATOR_TARGET) $(PERFECT_TARGET) *~
