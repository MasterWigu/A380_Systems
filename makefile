CC=g++ # use GCC as a compiler

# Directories
BDIR = out# dir for binaries
ODIR := obj# dir for C++ objects
SDIR := src# dur for engine source
S := src/plugin

SRC := $(wildcard $(SDIR)/*.cpp) $(wildcard $(SDIR)/*/*.cpp) $(wildcard $(SDIR)/*/*/*.cpp) $(wildcard $(SDIR)/*/*/*/*.cpp) $(wildcard $(SDIR)/*/*/*/*/*.cpp)# all C++ files - too lazy to do recursion, goes up to src/ase/ase/module/submodule or src/plugin/module/submodule/subsubmodule

# Objects
OBJ := $(SRC:.cpp=.o) # all C++, except suffix is .o

# Dependencies
_DEPS = include/sdk/cheaders/xplm include/sdk/cheaders/widgets #include/glew/cheaders
DEPS = $(addprefix -I,$(_DEPS)) # append -I

# Library Directories
_LDIRS = include/sdk/libraries/win #include/glew/libraries
LDIRS = $(addprefix -L,$(_LDIRS)) # append -L

# Libraries
_LIBS = XPLM_64 XPWidgets_64 stdc++ #glew32 opengl32
LIBS = $(addprefix -l, $(_LIBS)) # append -l

# Definitions
_DEFS = IBM XPLM200 XPLM210 XPLM300 XPLM301 XPLM302	ASE_XP
DEFS = $(addprefix -D, $(_DEFS)) # append -D

# Flags
CXXFLAGS = -I$(SDIR) -m64 $(DEFS) $(DEPS) -Isrc
LDFLAGS = -shared $(LDIRS) $(LIBS)

#%.cpp:
#	echo $@
#

%.o: %.cpp %.hpp
	@echo Compiling $<
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(BDIR)/win.exe: $(OBJ)
	@echo Linking $@
	$(CC) -o $@ $^ $(LDFLAGS)

