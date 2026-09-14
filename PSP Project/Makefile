TARGET = GodsDefense
CFLAGS = -O2 -g -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

GAMEOBJECTS = \
    Src/Main.o \
    Src/AnykeyScreen.o \
    Src/ScreenManager.o \
    Src/TitleScreen.o \
    Src/MainMenuScreen.o \
    Src/GameOptionsScreen.o \
    Src/GameScreen.o \
    Src/HelpScreen.o \
    Src/AboutScreen.o \
    Src/MultiplayerScreen.o \
    Src/PauseScreen.o \
    Src/GameGUI.o \
    Src/Resource.o \
    Src/ExitScreen.o \
    Src/WarningScreen.o \
    Src/Tower.o \
    Src/Projectile.o \
    Src/Enemy.o \
    Src/Map.o \
    Src/EndingScreen.o \
    Src/Adhoc.o \
    Src/TrophyManager.o \
    Src/TrophiesScreen.o \
    Src/MemoryWarningScreen.o

UTIL = \
    Src/util/Fps.o \
    Src/util/Sprites.o \
    Src/util/Drawing.o \
    Src/util/ReferenceCounted.o \
    Src/util/Coordinates2D.o \
    Src/util/MemoryStick.o \
    Src/util/Debug.o \
    Src/util/PspIO.o

RENDERERS = \
    Src/renderers/TowerRenderer.o \
    Src/renderers/EnemyRenderer.o \
    Src/renderers/ProjectileRenderer.o \
    Src/renderers/MapRenderer.o

OBJS = $(GAMEOBJECTS) $(UTIL) $(RENDERERS)

LIBDIR =
LDFLAGS =
LIBS = \
    -losl \
    -lpng \
    -lz \
    -lpsphprm \
    -ltinyxml2 \
    -lstdc++ \
    -lpspsdk \
    -lpspctrl \
    -lpspumd \
    -lpsprtc \
    -lpsppower \
    -lpspgu \
    -lpspaudiolib \
    -lpspaudio \
    -lm \
    -lpspwlan \
    -lpsphttp \
    -lpspssl \
    -lpspnet_adhocmatching \
    -lpspnet_adhoc \
    -lpspnet_adhocctl

BUILD_PRX = 1
SIGN_PRX = 0
PSP_FW_VERSION = 390
PSP_LARGE_MEMORY = 1
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Gods Defense
PSP_EBOOT_ICON = ICON0.png
PSP_EBOOT_PIC1 = PIC1.png

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

PPSSPP      = flatpak run --command=PPSSPPSDL org.ppsspp.PPSSPP
PPSSPPFLAGS =
RUNLOG      = ppsspp.log

# PPSSPP escreve seus logs no stderr; 2>&1 | tee joga tudo no terminal e no $(RUNLOG).
run: EBOOT.PBP
	$(PPSSPP) $(PPSSPPFLAGS) "$(CURDIR)/EBOOT.PBP" 2>&1 | tee "$(RUNLOG)"

run-prx: $(TARGET).prx
	$(PPSSPP) $(PPSSPPFLAGS) "$(CURDIR)/$(TARGET).prx" 2>&1 | tee "$(RUNLOG)"

# Log level debug: mostra SCEIO/SCEKERNEL/G3D (muito verboso, ~40k linhas/15s).
run-debug: PPSSPPFLAGS += -d
run-debug: run

.PHONY: run run-prx run-debug
