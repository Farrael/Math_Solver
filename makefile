###
# Manage variables for compilation
##
PROJECT = Solver

COMP 	= g++
CFLAGS 	= -c -Wall
LDFLAGS = 

OBJDIR 	= obj
SRCDIR 	= src

SRCS 	= $(wildcard $(SRCDIR)/*.c)
#SRCS 	= $(shell find $(SRCDIR) -name '*.cpp')
OBJS 	= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))	

###
# Compiling sources
##
all: $(PROJECT)

$(PROJECT): buildrepo $(OBJS)
	$(COMP) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(COMP) $(CFLAGS) -c $< -o $@

###
# Cleaning for compilation
##
clean:
	rm -f $(OBJDIR)/*.o

mrproper: clean
	rm -f $(PROJECT)$(EXT)

###
# Build repository
##
buildrepo:
	@mkdir -p $(OBJDIR)