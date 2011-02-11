TARGET = GodsDefense
CFLAGS = -O2 -g -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DTIXML_USE_STL
ASFLAGS = $(CFLAGS)

GAMEOBJECTS=Src/Main.o Src/AnykeyScreen.o Src/ScreenManager.o Src/TitleScreen.o Src/MainMenuScreen.o Src/GameOptionsScreen.o \
Src/GameScreen.o Src/HelpScreen.o Src/AboutScreen.o Src/MultiplayerScreen.o Src/PauseScreen.o Src/GameGUI.o \
Src/Resource.o Src/ExitScreen.o Src/WarningScreen.o Src/Tower.o Src/Projectile.o Src/Enemy.o Src/Map.o \
Src/EndingScreen.o Src/Adhoc.o Src/TrophiesScreen.o Src/MemoryWarningScreen.o
UTIL=Src/util/Fps.o Src/util/Sprites.o Src/util/Drawing.o Src/util/ReferenceCounted.o Src/util/Coordinates2D.o \
Src/util/MemoryStick.o Src/util/Debug.o Src/util/PspIO.o
TINYXML=tinyxml/tinystr.o tinyxml/tinyxml.o tinyxml/tinyxmlerror.o tinyxml/tinyxmlparser.o

OBJS = $(TINYXML) $(GAMEOBJECTS) $(UTIL)

LIBDIR =
LDFLAGS =
LIBS =  -losl -lpng -lz -lpsphprm -lpspaudiolib -lpspaudio -lpspsdk -lpspctrl -lpspumd -lpsprtc \
		-lpsppower -lpspgum -lpspgu -lm -lpspaudiolib -lpspaudiocodec -lstdc++ -lpspwlan -lpsphttp -lpspssl \
		-lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl

BUILD_PRX = 1
SIGN_PRX = 1
PSP_FW_VERSION=390
PSP_LARGE_MEMORY = 1
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Gods Defense
PSP_EBOOT_ICON = ICON0.png
PSP_EBOOT_PIC1 = PIC1.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak