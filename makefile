###
# Manage variables for compilation
##
PROJECT = Solver

COMP 	= g++
CFLAGS 	= -c -Wall
LDFLAGS = 

OBJDIR 	= obj
SRCDIR 	= src

SRCS 	= $(shell find $(SRCDIR) -name '*.cpp')
OBJS 	= $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))	

###
# Compiling sources
##
all: $(PROJECT)

$(PROJECT): buildrepo $(OBJS)
	$(COMP) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
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