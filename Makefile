CXX       = g++
CXXFLAGS  = -Wall -pedantic -O3 -std=c++14 -fsanitize=address
LD        = g++
LIBS      = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
OBJDIR    = obj
SRCDIR    = src
DEPDIR    = dep

rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
HEADERS = $(call rwildcard,$(SRCDIR),*.h)
DEP = $(patsubst $(SRCDIR)/%.cpp,$(DEPDIR)/%.d,$(SRC))



all: compile doc

compile: bomberman ;

bomberman: $(OBJ)
	$(LD) -o bomberman $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS)



doc: $(HEADERS) $(SRC) Doxyfile README.md
	doxygen



clean:
	rm -f bomberman
	rm -rf doc
	rm -rf $(DEPDIR)
	rm -rf $(OBJDIR)



run: compile
	./bomberman



$(DEPDIR)/%.d: $(SRCDIR)/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(CXX) -MM $< -MT $(OBJDIR)/$*.o > $@

-include $(DEP)
