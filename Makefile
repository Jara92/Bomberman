CXX       = g++
CXXFLAGS  = -Wall -pedantic -O3 -std=c++14
LD        = g++
LIBRARIES = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
OBJDIR    = obj
SRCDIR    = src
DEPDIR    = dep

PROJECTNAME = fikarja3

# Load sources and headers file names from every folder - No shell find. :(
SOURCES = $(wildcard src/*.cpp src/blocks/*.cpp src/blocks/collectibles/*.cpp src/enums/*.cpp src/interfaceitems/*.cpp src/movables/*.cpp src/scenes/*.cpp)
HEADERS = $(wildcard src/*.h src/blocks/*.h src/blocks/collectibles/*.h src/enums/*.h src/interfaceitems/*.h src/movables/*.h src/scenes/*.h)

# Load object and dependencies file names.
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
DEP = $(patsubst $(SRCDIR)/%.cpp,$(DEPDIR)/%.d,$(SOURCES))

.PHONY: all
all: compile doc

.PHONY: compile
compile: $(PROJECTNAME)

$(PROJECTNAME): $(OBJ)
	$(LD) -o $(PROJECTNAME) $^ $(LIBRARIES)
	#$(LD) -o $(PROJECTNAME) -fsanitize=address $^ $(LIBRARIES)

# Compile object file and create its directory.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

doc: $(HEADERS) $(SOURCES) Doxyfile README.md
	doxygen

.PHONY: clean
clean:
	rm -f $(PROJECTNAME)
	rm -rf doc
	rm -rf $(DEPDIR)
	rm -rf $(OBJDIR)

.PHONY: run
run: compile
	./$(PROJECTNAME)

# Create dependencies folder and file for every .cpp source file.
$(DEPDIR)/%.d: $(SRCDIR)/%.cpp $(HEADERS)
	mkdir -p $(@D)
	$(CXX) -MM $< -MT $(OBJDIR)/$*.o > $@ # Load dependencies for xxx.cpp file and redirect it into xxx.d

# Include dependencies.
-include $(DEP)
