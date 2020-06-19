CXX       = g++
CXXFLAGS  = -Wall -pedantic -O3 -std=c++14
LIBFLAGS  = -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
_DEPS     = CBody.h CTexturePack.h CLevelLoader.h CCoord.h CSettings.h enums/EGameStatus.h enums/EApplicationStatus.h enums/ECollectibleType.h enums/ETextureType.h enums/EEnemyType.h Messages.h CScoreSaver.h CAnimation.h CApplication.h blocks/CWall.h blocks/CBomb.h blocks/CFire.h blocks/collectibles/CCollectible.h blocks/collectibles/CBoost.h blocks/collectibles/CDoor.h blocks/CBlock.h CInput.h CBoard.h movables/CEnemy.h movables/CEnemySmart.h movables/CPlayer.h movables/CEnemyDumb.h movables/CMovable.h interfaceitems/CText.h interfaceitems/CImage.h interfaceitems/CButton.h interfaceitems/CSelectBoxItem.h interfaceitems/CSelectBox.h interfaceitems/CInterfaceItem.h CGameClock.h CRandom.h CTimer.h CSDLInterface.h scenes/CGameScene.h scenes/CSoloGameScene.h scenes/CSettingsScene.h scenes/CMultiplayerGameScene.h scenes/CScene.h scenes/CMenuScene.h
_OBJ      = main.o CBody.o CTexturePack.o CLevelLoader.o CScoreSaver.o CAnimation.o CApplication.o blocks/CWall.o blocks/CBomb.o blocks/CFire.o blocks/collectibles/CCollectible.o blocks/collectibles/CBoost.o blocks/collectibles/CDoor.o blocks/CBlock.o CInput.o CBoard.o movables/CEnemy.o movables/CEnemySmart.o movables/CPlayer.o movables/CEnemyDumb.o movables/CMovable.o interfaceitems/CText.o interfaceitems/CButton.o interfaceitems/CSelectBoxItem.o interfaceitems/CInterfaceItem.o CSDLInterface.o scenes/CGameScene.o scenes/CSoloGameScene.o scenes/CSettingsScene.o scenes/CMultiplayerGameScene.o scenes/CScene.o scenes/CMenuScene.o
OBJDIR    = obj
SRCDIR    = src

DEPS      = $(patsubst %,$(SRCDIR)/%,$(_DEPS))
OBJ       = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

.PHONY: all
all: compile doc

.PHONY: compile
compile: fikarja3

$(OBJDIR):
	mkdir $(OBJDIR)
	mkdir $(OBJDIR)/blocks
	mkdir $(OBJDIR)/blocks/collectibles
	mkdir $(OBJDIR)/scenes
	mkdir $(OBJDIR)/enums
	mkdir $(OBJDIR)/interfaceitems
	mkdir $(OBJDIR)/movables

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS) $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

fikarja3: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)

doc: Doxyfile README.md
	doxygen

.PHONY: clean
clean:
	rm -f fikarja3
	rm -rf doc
	rm -rf $(OBJDIR)

.PHONY: run
run: compile
	./fikarja3
