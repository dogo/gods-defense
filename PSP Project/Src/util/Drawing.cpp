//**************************************************************************
//		PSP Project: 'Gods Defense' - Drawing.cpp
//		@author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
//**************************************************************************

#include "../../Include/util/Drawing.h"
#include "../../Include/util/MessageText.h"
#include <algorithm>
#include <math.h>

short gState = 0;
int gFade = 255;

void Drawing::drawControlHint(OSL_IMAGE *icon, int x, int centerY, const char *label)
{
	sceKernelDcacheWritebackAll();
	oslSyncDrawing(); // Finish earlier font/image commands before drawing the hint.
	oslSetFont(gFont);
	oslResetScreenClipping();
	oslSetAlpha(OSL_FX_DEFAULT, 0);
	sceGuDisable(GU_DEPTH_TEST);
	osl_curTexture = NULL; // intraFont binds textures outside OSLib's cache.
	oslDrawImageXY(icon, x, centerY - icon->stretchY / 2);
	oslIntraFontSetStyle(gFont, 0.60f, RGBA(255,232,163,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_LEFT);
	// The shared icons have transparent padding; align to the visible rim.
	oslDrawString(x + icon->stretchX * 54 / 64 + 8, centerY - 3, label);
	sceGuDisable(GU_DEPTH_TEST);
	sceKernelDcacheWritebackAll();
	oslSyncDrawing();
}

void Drawing::showMessage(const char *text, const char *title)
{
	OSL_IMAGE *button = Sprites::LoadSpriteFilePNG(Resource::IMG_MAIN_MENU_BUTTONS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888, 192, 28);
	OSL_IMAGE *cross = oslLoadImageFilePNG(Resource::IMG_CROSS, OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	if (!button || !cross)
	{
		if (button) oslDeleteImage(button);
		if (cross) oslDeleteImage(cross);
		oslMessageBox(text, title, oslMake3Buttons(OSL_KEY_CROSS, OSL_MB_OK, 0, 0, 0, 0));
		return;
	}

	OSL_IMAGE *previousBuffer = oslGetDrawBuffer();
	OSL_FONT *previousFont = osl_curFont;
	const float size = gFont->intra->size, angle = gFont->intra->angle;
	const unsigned int color = gFont->intra->color, shadow = gFont->intra->shadowColor, options = gFont->intra->options;
	oslSetFont(gFont);
	oslIntraFontSetStyle(gFont, 0.55f, RGBA(225,214,192,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_LEFT);
	const auto measure = [](const std::string &line) { return oslGetStringWidth(line.c_str()); };
	const std::vector<std::string> lines = wrapMessageText(text, 344, measure);
	int contentWidth = 192;
	for (size_t i = 0; i < lines.size(); ++i)
		contentWidth = std::max(contentWidth, measure(lines[i]));
	oslIntraFontSetStyle(gFont, 0.72f, RGBA(255,232,163,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER);
	contentWidth = std::min(344, std::max(contentWidth, oslGetStringWidth(title)));
	const int left = (480 - contentWidth - 48) / 2;
	const int right = 480 - left;
	// shortcut: current alerts fit nine lines; add paging if longer messages are introduced.
	const int height = std::min(244, 112 + (int)lines.size() * 14);
	const int top = (272 - height) / 2;
	const int bottom = top + height;
	const int buttonY = bottom - 44;
	oslStartDrawing();
	// Like oslMessageBox, draw over the visible frame without advancing gameplay.
	oslSetDrawBuffer(OSL_SECONDARY_BUFFER);
	oslSetAlpha(OSL_FX_DEFAULT, 0);
	oslDrawFillRect(0, 0, 480, 272, RGBA(0,0,0,150));
	oslDrawFillRect(left, top, right, bottom, RGBA(93,64,18,255));
	oslDrawFillRect(left + 2, top + 2, right - 2, bottom - 2, RGBA(189,149,36,255));
	oslDrawFillRect(left + 3, top + 3, right - 3, bottom - 3, RGBA(20,12,8,255));
	oslDrawFillRect(left + 24, top + 44, right - 24, top + 45, RGBA(93,64,18,255));
	oslSetImageFrame(button, 1);
	oslDrawImageXY(button, 144, buttonY);
	cross->stretchX = cross->stretchY = 32;
	oslIntraFontSetStyle(gFont, 0.60f, RGBA(255,232,163,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_LEFT);
	const int hintWidth = 22 + 8 + oslGetStringWidth(Resource::STR_OK);
	Drawing::drawControlHint(cross, (480 - hintWidth) / 2 - 5, buttonY + 14, Resource::STR_OK);

	oslSetFont(gFont);
	oslIntraFontSetStyle(gFont, 0.72f, RGBA(255,232,163,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_CENTER);
	oslDrawString(240, top + 16, title);
	oslIntraFontSetStyle(gFont, 0.55f, RGBA(225,214,192,255), RGBA(0,0,0,255), 0.f, INTRAFONT_ALIGN_LEFT);
	oslSetScreenClipping(left + 24, top + 54, right - 24, buttonY - 10);
	for (size_t i = 0; i < lines.size(); ++i)
		oslDrawString(left + 24, top + 57 + (int)i * 14, lines[i].c_str());
	oslResetScreenClipping();
	oslSyncDrawing();

	oslFlushKey();
	while (!osl_quit)
	{
		oslReadKeys();
		if (osl_keys->pressed.cross)
			break;
		sceDisplayWaitVblankStart();
	}
	oslFlushKey();
	oslIntraFontSetStyle(gFont, size, color, shadow, angle, options);
	oslSetFont(previousFont);
	oslSetDrawBuffer(previousBuffer);
	oslDeleteImage(cross);
	oslDeleteImage(button);
}

void Drawing::drawSplash(int iTime, OSL_IMAGE *Splash) {
	oslDrawImageXY(Splash, (480/2) - (Splash->stretchX/2), (272/2) - (Splash->stretchY/2));
	if(gState == 0 || gState == 2) {
		oslDrawFillRect(0, 0, 480, 272, RGBA(0, 0, 0, gFade));
	}
	if (gState == 0) {
		gFade = gFade - 2;
		if (gFade <= 0) {
			gFade = 0;
			gState = 1;
		}
	} else if (gState == 1) {
		sceKernelDelayThread(iTime);
		gState = 2;
	} else if (gState == 2) {
		gFade = gFade + 2;		 
	}
}

void Drawing::drawPixel(float x, float y, OSL_COLOR color)
{
	oslDrawFillRect((int)x, (int)y, (int)x+1, (int)y+1, color);
}

// Draw a smooth pixel with anti-aliasing effect (2x2 block for thin smooth line)
static void drawSmoothPixel(int x, int y, OSL_COLOR color)
{
	// Draw a 2x2 block for smooth but thin appearance
	oslDrawFillRect(x, y, x+2, y+2, color);
}

void Drawing::drawCircle(int x, int y, int radius, OSL_COLOR color)
{ 
	// Validate radius
	if (radius <= 0 || radius > 500)
		return;
	
	// Draw circle using trigonometry with very small step for perfectly smooth line
	// Using step of 0.2 degrees ensures smoothness with good performance
	float step = 0.2f;
	for (float angle = 0.0f; angle < 360.0f; angle += step)
	{
		float rad = angle * M_PI / 180.0f;
		float px = x + radius * oslSinf(rad);
		float py = y - radius * oslCosf(rad);
		
		// Draw smooth pixel with anti-aliasing effect (2x2 block for thin smooth line)
		int px_int = (int)(px + 0.5f); // Round to nearest integer
		int py_int = (int)(py + 0.5f);
		drawSmoothPixel(px_int, py_int, color);
	}
}
