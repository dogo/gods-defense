TARGET = GodsDefense
OBJS = Src/Main.o Src/AnykeyScreen.o Src/ScreenManager.o Src/TitleScreen.o Src/MainMenuScreen.o Src/GameOptionsScreen.o \
Src/GameScreen.o Src/OptionsScreen.o Src/HelpScreen.o Src/AboutScreen.o Src/MultiplayerScreen.o Src/PauseScreen.o \
Src/Resource.o Src/SaveLoad.o

CFLAGS = -O2 -g -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS =  -losl -lpng -lz -lpspaudiolib -lpspaudio -lpspsdk -lpspctrl -lpspumd -lpsprtc \
		-lpsppower -lpspgum -lpspgu -lm -lpspaudiolib -lpspaudiocodec -lstdc++

BUILD_PRX = 1
PSP_FW_VERSION=390
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Gods Defense
PSP_EBOOT_ICON = ICON0.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak