CXX       = g++
CXXFLAGS  = -Wall -pedantic -O3 -fsanitize=address -std=c++14
LIBFLAGS  = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
_DEPS     =			CApplication.h	CCoord.h	CBoard.h	CSDLInterface.h
_OBJ      = main.o	CApplication.o	CCoord.o	CBoard.o	CSDLInterface.o
OBJDIR    = obj
SRCDIR    = src
DEPS      = $(patsubst %,$(SRCDIR)/%,$(_DEPS))
OBJ       = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: bomberman doc

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS) $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

bomberman: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)

doc:
	doxygen

clean:
	rm -f bomberman
	rm -rf doc
	rm -rf $(OBJDIR)

run: bomberman
		./bomberman
