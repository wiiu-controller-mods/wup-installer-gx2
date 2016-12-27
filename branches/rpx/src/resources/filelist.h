/****************************************************************************
 * Loadiine resource files.
 * This file is generated automatically.
 * Includes 28 files.
 *
 * NOTE:
 * Any manual modification of this file will be overwriten by the generation.
 ****************************************************************************/
#ifndef _FILELIST_H_
#define _FILELIST_H_

#include <gctypes.h>

typedef struct _RecourceFile
{
	const char *filename;
	const u8   *DefaultFile;
	const u32  &DefaultFileSize;
	u8		   *CustomFile;
	u32		    CustomFileSize;
} RecourceFile;

extern const u8 bgMusic_ogg[];
extern const u32 bgMusic_ogg_size;

extern const u8 button_click_mp3[];
extern const u32 button_click_mp3_size;

extern const u8 choiceCheckedRectangle_png[];
extern const u32 choiceCheckedRectangle_png_size;

extern const u8 choiceSelectedRectangle_png[];
extern const u32 choiceSelectedRectangle_png_size;

extern const u8 choiceUncheckedRectangle_png[];
extern const u32 choiceUncheckedRectangle_png_size;

extern const u8 errorIcon_png[];
extern const u32 errorIcon_png_size;

extern const u8 exclamationIcon_png[];
extern const u32 exclamationIcon_png_size;

extern const u8 font_ttf[];
extern const u32 font_ttf_size;

extern const u8 informationIcon_png[];
extern const u32 informationIcon_png_size;

extern const u8 messageBox_png[];
extern const u32 messageBox_png_size;

extern const u8 messageBoxButton_png[];
extern const u32 messageBoxButton_png_size;

extern const u8 messageBoxButtonSelected_png[];
extern const u32 messageBoxButtonSelected_png_size;

extern const u8 minus_png[];
extern const u32 minus_png_size;

extern const u8 player1_point_png[];
extern const u32 player1_point_png_size;

extern const u8 player2_point_png[];
extern const u32 player2_point_png_size;

extern const u8 player3_point_png[];
extern const u32 player3_point_png_size;

extern const u8 player4_point_png[];
extern const u32 player4_point_png_size;

extern const u8 plus_png[];
extern const u32 plus_png_size;

extern const u8 progressBar_png[];
extern const u32 progressBar_png_size;

extern const u8 progressWindow_png[];
extern const u32 progressWindow_png_size;

extern const u8 questionIcon_png[];
extern const u32 questionIcon_png_size;

extern const u8 scrollbarButton_png[];
extern const u32 scrollbarButton_png_size;

extern const u8 scrollbarLine_png[];
extern const u32 scrollbarLine_png_size;

extern const u8 select_button_png[];
extern const u32 select_button_png_size;

extern const u8 splash_png[];
extern const u32 splash_png_size;

extern const u8 titleHeader_png[];
extern const u32 titleHeader_png_size;

extern const u8 validIcon_png[];
extern const u32 validIcon_png_size;

extern const u8 warningIcon_png[];
extern const u32 warningIcon_png_size;

static RecourceFile RecourceList[] =
{
	{"bgMusic.ogg", bgMusic_ogg, bgMusic_ogg_size, NULL, 0},
	{"button_click.mp3", button_click_mp3, button_click_mp3_size, NULL, 0},
	{"choiceCheckedRectangle.png", choiceCheckedRectangle_png, choiceCheckedRectangle_png_size, NULL, 0},
	{"choiceSelectedRectangle.png", choiceSelectedRectangle_png, choiceSelectedRectangle_png_size, NULL, 0},
	{"choiceUncheckedRectangle.png", choiceUncheckedRectangle_png, choiceUncheckedRectangle_png_size, NULL, 0},
	{"errorIcon.png", errorIcon_png, errorIcon_png_size, NULL, 0},
	{"exclamationIcon.png", exclamationIcon_png, exclamationIcon_png_size, NULL, 0},
	{"font.ttf", font_ttf, font_ttf_size, NULL, 0},
	{"informationIcon.png", informationIcon_png, informationIcon_png_size, NULL, 0},
	{"messageBox.png", messageBox_png, messageBox_png_size, NULL, 0},
	{"messageBoxButton.png", messageBoxButton_png, messageBoxButton_png_size, NULL, 0},
	{"messageBoxButtonSelected.png", messageBoxButtonSelected_png, messageBoxButtonSelected_png_size, NULL, 0},
	{"minus.png", minus_png, minus_png_size, NULL, 0},
	{"player1_point.png", player1_point_png, player1_point_png_size, NULL, 0},
	{"player2_point.png", player2_point_png, player2_point_png_size, NULL, 0},
	{"player3_point.png", player3_point_png, player3_point_png_size, NULL, 0},
	{"player4_point.png", player4_point_png, player4_point_png_size, NULL, 0},
	{"plus.png", plus_png, plus_png_size, NULL, 0},
	{"progressBar.png", progressBar_png, progressBar_png_size, NULL, 0},
	{"progressWindow.png", progressWindow_png, progressWindow_png_size, NULL, 0},
	{"questionIcon.png", questionIcon_png, questionIcon_png_size, NULL, 0},
	{"scrollbarButton.png", scrollbarButton_png, scrollbarButton_png_size, NULL, 0},
	{"scrollbarLine.png", scrollbarLine_png, scrollbarLine_png_size, NULL, 0},
	{"select_button.png", select_button_png, select_button_png_size, NULL, 0},
	{"splash.png", splash_png, splash_png_size, NULL, 0},
	{"titleHeader.png", titleHeader_png, titleHeader_png_size, NULL, 0},
	{"validIcon.png", validIcon_png, validIcon_png_size, NULL, 0},
	{"warningIcon.png", warningIcon_png, warningIcon_png_size, NULL, 0},
	{NULL, NULL, 0, NULL, 0}
};

#endif
