COMPILER       = g++
COMPILERFLAGS  = -Wall -pedantic -O3 -std=c++14
LD        = g++
LIBS      = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
OBJDIR    = obj
SRCDIR    = src
DEPDIR    = dep

search = $(foreach d,$(wildcard $(1:=/*)),$(call search,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call search,$(SRCDIR),*.cpp)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
HEADERS = $(call search,$(SRCDIR),*.h)
DEP = $(patsubst $(SRCDIR)/%.cpp,$(DEPDIR)/%.d,$(SRC))

all: compile doc

compile: fikarja3 ;

# Kompiluje výsledný produkt. Slinkuje všechny .o objekty a nalinkuje k nim knihovny.
fikarja3: $(OBJ)
	$(LD) -o fikarja3 -fsanitize=address $^ $(LIBS)
	#$(LD) -o fikarja3 $^ $(LIBS)

# Kompilace jednoho .o souboru
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(COMPILER) -c -o $@ $< $(COMPILERFLAGS)

# Pro každý .cpp nalzený soubor vezme závislosti (includované .h soubory) a
$(DEPDIR)/%.d: $(SRCDIR)/%.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(COMPILER) -MM $< -MT $(OBJDIR)/$*.o > $@

doc: $(HEADERS) $(SRC) Doxyfile README.md
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -f fikarja3
	rm -rf doc
	rm -rf $(DEPDIR)
	rm -rf $(OBJDIR)

.PHONY: run
run: compile
	./fikarja3

-include $(DEP)
