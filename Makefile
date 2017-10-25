# Header files
HDIR := include

# Source files
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Dependencies
DEPDIR = dependencies
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# Object files
BUILDDIR = objects
OBJS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%.o,$(basename $(SRCS)))

# Binary files
BINDIR = bin
BINARYNAMES = battery low-battery power
BINARIES = $(BINARYNAMES:%=$(BINDIR)/%)

# Root Binary files
ROOTDIR = root
ROOTBINARIES = $(BINARIES:$(BINDIR)/%=$(ROOTDIR)/%)

# Common flags for compiling and linking
COMMONFLAGS = -g -O0 -std=c++11 -Wall -Wpedantic -Werror -Wfatal-errors

# Compilation options
CXXFLAGS = $(COMMONFLAGS) $(addprefix -I, $(HDIR)) $(DEPFLAGS)
COMPILE = $(CXX) -o $@ -c $< $(CXXFLAGS)

# Link Options
LDFLAGS += $(COMMONFLAGS)
LINK = $(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

.PHONY: all build install clean-install
all: install

build: $(BUILDDIR) $(DEPDIR) $(BINDIR) $(BINARIES)

install: build $(ROOTDIR) $(ROOTBINARIES)

clean:
	@$(RM) $(BUILDDIR)/*.o $(DEPDIR)/*.d $(BINARIES)

clean-install:
	@sudo $(RM) $(ROOTBINARIES)

clean-all: clean clean-install

$(BUILDDIR) $(DEPDIR) $(BINDIR) $(ROOTDIR):
	$(info $@)
	@mkdir -p $@

# Compiling Objects
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(info $@)
	@$(COMPILE)

# Compiling Binary
.SECONDEXPANSION:
pc := %

$(BINARIES): $$(patsubst $$(BINDIR)/$$(pc), $$(BUILDDIR)/$$(pc).o, $$@) $(filter-out $(BINARYNAMES:%=$(BUILDDIR)/%.o), $(OBJS))
	$(info $@)
	@$(LINK)

$(ROOTBINARIES): $$(patsubst $$(ROOTDIR)/$$(pc), $$(BINDIR)/$$(pc), $$@)
	$(info $@)
	@sudo cp $< $@
	@sudo chown root:kb-backlight $@
	@sudo chmod 4750 $@

include $(wildcard $(DEPDIR)/*.d)
