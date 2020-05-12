CXX       = g++
CXXFLAGS  = -Wall -pedantic -O3 -fsanitize=address -g -fno-omit-frame-pointer -fno-optimize-sibling-calls -std=c++14
LIBFLAGS  = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
_DEPS     =			CApplication.h	CCoord.h	CTexturePack.h	gameobjects/CGameObject.h	gameobjects/collectibles/CCollectible.h	gameobjects/CMovable.h	gameobjects/CPlayer.h	CBoard.h	CSDLInterface.h	CGameManager.h	CLevelLoader.h
_OBJ      = main.o	CApplication.o	CCoord.o	CTexturePack.o	gameobjects/CGameObject.o	gameobjects/collectibles/CCollectible.o	gameobjects/CMovable.o	gameobjects/CPlayer.o	CBoard.o	CSDLInterface.o	CGameManager.o	CLevelLoader.o
OBJDIR    = obj
SRCDIR    = src
DEPS      = $(patsubst %,$(SRCDIR)/%,$(_DEPS))
OBJ       = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: bomberman doc

$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir $(OBJDIR)/gameobjects
	mkdir $(OBJDIR)/gameobjects/collectibles

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
