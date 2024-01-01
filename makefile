# Compiler
CXX = g++
# Flags
CXXFLAGS = -std=c++11 -Wall
# Directories
SRCDIR = src
INCDIR = include
EXTDIR = external
BUILDDIR = build
BINDIR = bin
# Executable name
TARGET = password-generator

# Files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))
DEPS = $(wildcard $(INCDIR)/*.h)
# Library flags
LIB = -lncurses

# Build executable
$(BINDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIB)

# Build object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

.PHONY: clean

# Clean build files
clean:
	rm -rf $(BUILDDIR) $(BINDIR)
