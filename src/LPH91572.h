//--------Display library LPH9157-2 from Siemens C75, 75---------
//                 Green PCB
//                132x176 px
//          
//             port to arduino 
//
//
//
//-----------------------------------------------------------------

#pragma once

// uncomment to use 8 bit colors
//#define _8_BIT_COLOR

// allow to use geometrical functions  
#define _GEOMETRICAL  
// uncomment to use additional reset pin
#define _USE_HARDWARE_RESET

//===============================================================
//		            
//===============================================================

#ifdef _USE_HARDWARE_RESET
#define LCD_RESET  	21	// hardware reset pin
#endif

#define LCD_RS		22	//RS pin (command/data select)

//*************************************************************
// command/data
#define CMD 0
#define DAT 1

#ifdef _8_BIT_COLOR
//8 bit color samples (256 colors)
#define GREEN       0x1C
#define DARK_GREEN  0x15
#define RED         0xE0
#define BLUE        0x1F
#define DARK_BLUE   0x03
#define YELLOW      0xFC
#define ORANGE      0xEC
#define VIOLET      0xE3
#define WHITE       0xFF
#define BLACK       0x00
#define GREY        0x6D

#else
//16 bit (RGB565) color samples (65536 colors)
#define    BLACK                0x0000 //
#define    WHITE                0xFFFF //
#define    GRAY                 0xE79C //
#define    GREEN                0x07E0 //
#define    BLUE                 0x001F //
#define    RED                  0xF800 //
#define    SKY                  0x5d1c //
#define    YELLOW               0xffe0 //
#define    MAGENTA              0xf81f //
#define    CYAN                 0x07ff // 
#define    ORANGE               0xfca0 //
#define    PINK                 0xF97F //
#define    BROWN                0x8200 //
#define    VIOLET               0x9199 //
#define    SILVER               0xa510 //
#define    GOLD                 0xa508 //
#define    BEGH                 0xf77b //
#define    NAVY                 0x000F //
#define    DARK_GREEN           0x03E0 //
#define    DARK_CYAN            0x03EF //
#define    MAROON               0x7800 //
#define    PURPLE               0x780F //
#define    OLIVE                0x7BE0 //
#define    LIGHT_GREY           0xC618 //
#define    DARK_GREY            0x7BEF //

#define    ZX_BLACK             0x0000 // 0x000000
#define    ZX_BLUE              0x001A // 0x0000d8
#define    ZX_BLUE_BR           0x001F // 0x0000ff
#define    ZX_RED               0xD000 // 0xd80000
#define    ZX_RED_BR            0xF800 // 0xff0000
#define    ZX_MAGENTA           0xD01A // 0xd800d8
#define    ZX_MAGENTA_BR        0xF81F // 0xff00ff
#define    ZX_GREEN             0x06A0 // 0x00d800
#define    ZX_GREEN_BR          0x07E0 // 0x00ff00
#define    ZX_CYAN              0x06BA // 0x00d8d8
#define    ZX_CYAN_BR           0x07FF // 0x00ffff
#define    ZX_YELLOW            0xD6A0 // 0xd8d800
#define    ZX_YELLOW_BR         0xFFE0 // 0xffff00
#define    ZX_WHITE             0xD6BA // 0xd8d8d8
#define    ZX_WHITE_BR          0xFFFF // 0xffffff

#endif

//*************************************************************
//functions prototypes

void LCD_init (void);
void Send_to_lcd (uint8_t RS, uint8_t data);
void SetArea (uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
void Put_Pixel (uint8_t x, uint8_t y, uint16_t color);
void Send_Symbol (char symbol, uint8_t x, uint8_t y, uint16_t t_color, uint16_t b_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot);
void LCD_Putchar (char symbol, uint8_t x, uint8_t y, uint16_t t_color, uint16_t b_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot);
void LCD_Puts (char *str, uint8_t x, uint8_t y,  uint16_t t_color, uint16_t b_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot);
void Send_Symbol_Shadow (char symbol, uint8_t x, uint8_t y, uint16_t t_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot);
void LCD_Putchar_Shadow (char symbol, uint8_t x, uint8_t y, uint16_t t_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot);
void LCD_Puts_Shadow (char *str, uint8_t x, uint8_t y,  uint16_t t_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot);
void LCD_FillScreen (uint16_t color);
void LCD_Output_image (uint8_t x, uint8_t y, uint8_t width, uint8_t height,  uint8_t *img, uint16_t rot);
void Send_Image (uint8_t x, uint8_t y, uint8_t width, uint8_t height,  uint8_t *img, uint16_t rot);
#ifdef _GEOMETRICAL
void LCD_DrawLine (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);
void LCD_DrawRect (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, uint8_t size, uint16_t color);
void LCD_DrawRect_my (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, uint8_t size, uint16_t color);
void LCD_FillRect (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, uint16_t color);
#endif

