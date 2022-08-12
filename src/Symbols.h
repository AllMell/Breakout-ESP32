#ifndef __SYMBOLS_H__
#define __SYMBOLS_H__


const PROGMEM byte zx_font_8x8[][8] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char  
        0x00, 0x00, 0x00, 0x5E, 0x00, 0x00, 0x00, 0x00,  // Code for char !
        0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00,  // Code for char "
        0x00, 0x24, 0x7E, 0x24, 0x24, 0x7E, 0x24, 0x00,  // Code for char #
        0x00, 0x00, 0x5C, 0x54, 0xFE, 0x54, 0x74, 0x00,  // Code for char $
        0x00, 0x46, 0x26, 0x10, 0x08, 0x64, 0x62, 0x00,  // Code for char %
        0x00, 0x20, 0x54, 0x4A, 0x54, 0x20, 0x50, 0x00,  // Code for char &
        0x00, 0x00, 0x00, 0x04, 0x02, 0x00, 0x00, 0x00,  // Code for char '
        0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x00, 0x00,  // Code for char (
        0x00, 0x00, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x00,  // Code for char )
        0x00, 0x00, 0x10, 0x54, 0x38, 0x54, 0x10, 0x00,  // Code for char *
        0x00, 0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x00,  // Code for char +
        0x00, 0x00, 0x00, 0x80, 0x60, 0x00, 0x00, 0x00,  // Code for char ,
        0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00,  // Code for char -
        0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00,  // Code for char .
        0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x00,  // Code for char /
        0x00, 0x3C, 0x62, 0x52, 0x4A, 0x46, 0x3C, 0x00,  // Code for char 0
        0x00, 0x00, 0x44, 0x42, 0x7E, 0x40, 0x40, 0x00,  // Code for char 1
        0x00, 0x64, 0x52, 0x52, 0x52, 0x52, 0x4C, 0x00,  // Code for char 2
        0x00, 0x24, 0x42, 0x42, 0x4A, 0x4A, 0x34, 0x00,  // Code for char 3
        0x00, 0x30, 0x28, 0x24, 0x7E, 0x20, 0x20, 0x00,  // Code for char 4
        0x00, 0x2E, 0x4A, 0x4A, 0x4A, 0x4A, 0x32, 0x00,  // Code for char 5
        0x00, 0x3C, 0x4A, 0x4A, 0x4A, 0x4A, 0x30, 0x00,  // Code for char 6
        0x00, 0x02, 0x02, 0x62, 0x12, 0x0A, 0x06, 0x00,  // Code for char 7
        0x00, 0x34, 0x4A, 0x4A, 0x4A, 0x4A, 0x34, 0x00,  // Code for char 8
        0x00, 0x0C, 0x52, 0x52, 0x52, 0x52, 0x3C, 0x00,  // Code for char 9
        0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00,  // Code for char :
        0x00, 0x00, 0x80, 0x64, 0x00, 0x00, 0x00, 0x00,  // Code for char ;
        0x00, 0x00, 0x00, 0x10, 0x28, 0x44, 0x00, 0x00,  // Code for char <
        0x00, 0x00, 0x28, 0x28, 0x28, 0x28, 0x28, 0x00,  // Code for char =
        0x00, 0x00, 0x00, 0x44, 0x28, 0x10, 0x00, 0x00,  // Code for char >
        0x00, 0x04, 0x02, 0x02, 0x52, 0x0A, 0x04, 0x00,  // Code for char ?
        0x00, 0x3C, 0x42, 0x5A, 0x56, 0x5A, 0x1C, 0x00,  // Code for char @
        0x00, 0x7C, 0x12, 0x12, 0x12, 0x12, 0x7C, 0x00,  // Code for char A
        0x00, 0x7E, 0x4A, 0x4A, 0x4A, 0x4A, 0x34, 0x00,  // Code for char B
        0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x24, 0x00,  // Code for char C
        0x00, 0x7E, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00,  // Code for char D
        0x00, 0x7E, 0x4A, 0x4A, 0x4A, 0x4A, 0x42, 0x00,  // Code for char E
        0x00, 0x7E, 0x0A, 0x0A, 0x0A, 0x0A, 0x02, 0x00,  // Code for char F
        0x00, 0x3C, 0x42, 0x42, 0x52, 0x52, 0x30, 0x00,  // Code for char G
        0x00, 0x7E, 0x08, 0x08, 0x08, 0x08, 0x7E, 0x00,  // Code for char H
        0x00, 0x00, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00,  // Code for char I
        0x00, 0x30, 0x40, 0x40, 0x40, 0x40, 0x3E, 0x00,  // Code for char J
        0x00, 0x7E, 0x08, 0x08, 0x14, 0x22, 0x40, 0x00,  // Code for char K
        0x00, 0x7E, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00,  // Code for char L
        0x00, 0x7E, 0x04, 0x08, 0x08, 0x04, 0x7E, 0x00,  // Code for char M
        0x00, 0x7E, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x00,  // Code for char N
        0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00,  // Code for char O
        0x00, 0x7E, 0x12, 0x12, 0x12, 0x12, 0x0C, 0x00,  // Code for char P
        0x00, 0x3C, 0x42, 0x52, 0x62, 0x42, 0x3C, 0x00,  // Code for char Q
        0x00, 0x7E, 0x12, 0x12, 0x12, 0x32, 0x4C, 0x00,  // Code for char R
        0x00, 0x24, 0x4A, 0x4A, 0x4A, 0x4A, 0x30, 0x00,  // Code for char S
        0x02, 0x02, 0x02, 0x7E, 0x02, 0x02, 0x02, 0x00,  // Code for char T
        0x00, 0x3E, 0x40, 0x40, 0x40, 0x40, 0x3E, 0x00,  // Code for char U
        0x00, 0x1E, 0x20, 0x40, 0x40, 0x20, 0x1E, 0x00,  // Code for char V
        0x00, 0x3E, 0x40, 0x20, 0x20, 0x40, 0x3E, 0x00,  // Code for char W
        0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00,  // Code for char X
        0x02, 0x04, 0x08, 0x70, 0x08, 0x04, 0x02, 0x00,  // Code for char Y
        0x00, 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x00,  // Code for char Z
        0x00, 0x00, 0x00, 0x00, 0x7E, 0x42, 0x42, 0x00,  // Code for char [
        0x00, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00,  // Code for char BackSlash
        0x00, 0x42, 0x42, 0x7E, 0x00, 0x00, 0x00, 0x00,  // Code for char ]
        0x00, 0x08, 0x04, 0x7E, 0x04, 0x08, 0x00, 0x00,  // Code for char ^
        0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,  // Code for char _
        0x00, 0x00, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00,  // Code for char `
        0x00, 0x20, 0x54, 0x54, 0x54, 0x78, 0x00, 0x00,  // Code for char a
        0x00, 0x00, 0x7E, 0x48, 0x48, 0x48, 0x30, 0x00,  // Code for char b
        0x00, 0x00, 0x38, 0x44, 0x44, 0x44, 0x00, 0x00,  // Code for char c
        0x00, 0x30, 0x48, 0x48, 0x48, 0x7E, 0x00, 0x00,  // Code for char d
        0x00, 0x38, 0x54, 0x54, 0x54, 0x08, 0x00, 0x00,  // Code for char e
        0x00, 0x00, 0x00, 0x7C, 0x0A, 0x02, 0x00, 0x00,  // Code for char f
        0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, 0x00, 0x00,  // Code for char g
        0x00, 0x7E, 0x08, 0x08, 0x08, 0x70, 0x00, 0x00,  // Code for char h
        0x00, 0x00, 0x48, 0x7A, 0x40, 0x00, 0x00, 0x00,  // Code for char i
        0x00, 0x00, 0x40, 0x80, 0x80, 0x7A, 0x00, 0x00,  // Code for char j
        0x00, 0x00, 0x7E, 0x18, 0x24, 0x40, 0x00, 0x00,  // Code for char k
        0x00, 0x00, 0x00, 0x3E, 0x40, 0x40, 0x00, 0x00,  // Code for char l
        0x00, 0x7C, 0x04, 0x78, 0x04, 0x78, 0x00, 0x00,  // Code for char m
        0x00, 0x7C, 0x04, 0x04, 0x04, 0x78, 0x00, 0x00,  // Code for char n
        0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00,  // Code for char o
        0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, 0x00, 0x00,  // Code for char p
        0x00, 0x18, 0x24, 0x24, 0x24, 0xFC, 0x80, 0x00,  // Code for char q
        0x00, 0x00, 0x78, 0x04, 0x04, 0x04, 0x00, 0x00,  // Code for char r
        0x00, 0x48, 0x54, 0x54, 0x54, 0x20, 0x00, 0x00,  // Code for char s
        0x00, 0x00, 0x04, 0x3E, 0x44, 0x40, 0x00, 0x00,  // Code for char t
        0x00, 0x3C, 0x40, 0x40, 0x40, 0x3C, 0x00, 0x00,  // Code for char u
        0x00, 0x0C, 0x30, 0x40, 0x30, 0x0C, 0x00, 0x00,  // Code for char v
        0x00, 0x3C, 0x40, 0x38, 0x40, 0x3C, 0x00, 0x00,  // Code for char w
        0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00,  // Code for char x
        0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, 0x00, 0x00,  // Code for char y
        0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, 0x00,  // Code for char z
        0x00, 0x00, 0x08, 0x08, 0x76, 0x42, 0x42, 0x00,  // Code for char {
        0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,  // Code for char |
        0x00, 0x42, 0x42, 0x76, 0x08, 0x08, 0x00, 0x00,  // Code for char }
        0x00, 0x00, 0x02, 0x01, 0x02, 0x01, 0x00, 0x00,  // Code for char ~
        0x1C, 0x3E, 0x7E, 0xFC, 0x7E, 0x3E, 0x1C, 0x00,  // Code for char 
        0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, 0x00, 0x00,  // Code for char Ђ
        0x00, 0x38, 0x44, 0x44, 0x44, 0x44, 0x00, 0x00,  // Code for char Ѓ
        0x00, 0x04, 0x04, 0x7C, 0x04, 0x04, 0x00, 0x00,  // Code for char ‚
        0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, 0x00, 0x00,  // Code for char ѓ
        0x38, 0x44, 0x44, 0xFE, 0x44, 0x44, 0x38, 0x00,  // Code for char „
        0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00, 0x00,  // Code for char …
        0x00, 0x7C, 0x40, 0x40, 0x40, 0x7C, 0xC0, 0x00,  // Code for char †
        0x00, 0x0C, 0x10, 0x10, 0x10, 0x7C, 0x00, 0x00,  // Code for char ‡
        0x00, 0x7C, 0x40, 0x7C, 0x40, 0x7C, 0x00, 0x00,  // Code for char €
        0x00, 0x7C, 0x40, 0x7C, 0x40, 0x7C, 0xC0, 0x00,  // Code for char ‰
        0x04, 0x7C, 0x50, 0x50, 0x50, 0x20, 0x00, 0x00,  // Code for char Љ
        0x7C, 0x50, 0x50, 0x50, 0x20, 0x00, 0x7C, 0x00,  // Code for char ‹
        0x00, 0x7C, 0x50, 0x50, 0x50, 0x20, 0x00, 0x00,  // Code for char Њ
        0x00, 0x28, 0x44, 0x54, 0x54, 0x38, 0x00, 0x00,  // Code for char Ќ
        0x00, 0x7C, 0x10, 0x38, 0x44, 0x44, 0x38, 0x00,  // Code for char Ћ
        0x00, 0x48, 0x34, 0x14, 0x14, 0x7C, 0x00, 0x00,  // Code for char Џ
        0x00, 0x7C, 0x12, 0x12, 0x12, 0x12, 0x7C, 0x00,  // Code for char ђ
        0x00, 0x7E, 0x4A, 0x4A, 0x4A, 0x4A, 0x30, 0x00,  // Code for char ‘
        0x00, 0x7E, 0x4A, 0x4A, 0x4A, 0x4A, 0x34, 0x00,  // Code for char ’
        0x00, 0x7E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00,  // Code for char “
        0x00, 0xC0, 0x7C, 0x42, 0x42, 0x7E, 0xC0, 0x00,  // Code for char ”
        0x00, 0x7E, 0x4A, 0x4A, 0x4A, 0x4A, 0x42, 0x00,  // Code for char •
        0x62, 0x14, 0x08, 0x7E, 0x08, 0x14, 0x62, 0x00,  // Code for char –
        0x00, 0x24, 0x42, 0x42, 0x4A, 0x4A, 0x34, 0x00,  // Code for char —
        0x00, 0x7E, 0x20, 0x10, 0x08, 0x04, 0x7E, 0x00,  // Code for char 
        0x00, 0x7E, 0x20, 0x11, 0x09, 0x04, 0x7E, 0x00,  // Code for char ™
        0x00, 0x7E, 0x08, 0x08, 0x14, 0x22, 0x40, 0x00,  // Code for char љ
        0x40, 0x40, 0x3E, 0x02, 0x02, 0x02, 0x7E, 0x00,  // Code for char ›
        0x00, 0x7E, 0x04, 0x08, 0x08, 0x04, 0x7E, 0x00,  // Code for char њ
        0x00, 0x7E, 0x08, 0x08, 0x08, 0x08, 0x7E, 0x00,  // Code for char ќ
        0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00,  // Code for char ћ
        0x00, 0x7E, 0x02, 0x02, 0x02, 0x02, 0x7E, 0x00,  // Code for char џ
        0x00, 0x7E, 0x12, 0x12, 0x12, 0x12, 0x0C, 0x00,  // Code for char  
        0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x24, 0x00,  // Code for char Ў
        0x02, 0x02, 0x02, 0x7E, 0x02, 0x02, 0x02, 0x00,  // Code for char ў
        0x00, 0x0E, 0x50, 0x50, 0x50, 0x50, 0x3E, 0x00,  // Code for char Ј
        0x1C, 0x22, 0x22, 0x7E, 0x22, 0x22, 0x1C, 0x00,  // Code for char ¤
        0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00,  // Code for char Ґ
        0x00, 0x7E, 0x40, 0x40, 0x40, 0x7E, 0xC0, 0x00,  // Code for char ¦
        0x00, 0x0E, 0x10, 0x10, 0x10, 0x10, 0x7E, 0x00,  // Code for char §
        0x7E, 0x40, 0x40, 0x7E, 0x40, 0x40, 0x7E, 0x00,  // Code for char Ё
        0x7E, 0x40, 0x40, 0x7E, 0x40, 0x40, 0xFE, 0x00,  // Code for char ©
        0x02, 0x7E, 0x48, 0x48, 0x48, 0x48, 0x30, 0x00,  // Code for char Є
        0x7E, 0x48, 0x48, 0x48, 0x30, 0x00, 0x7E, 0x00,  // Code for char «
        0x00, 0x7E, 0x48, 0x48, 0x48, 0x48, 0x30, 0x00,  // Code for char ¬
        0x00, 0x24, 0x42, 0x42, 0x4A, 0x4A, 0x3C, 0x00,  // Code for char ­
        0x7E, 0x08, 0x3C, 0x42, 0x42, 0x42, 0x3C, 0x00,  // Code for char ®
        0x00, 0x4C, 0x32, 0x12, 0x12, 0x12, 0x7E, 0x00,  // Code for char Ї
        0x00, 0x20, 0x54, 0x54, 0x54, 0x78, 0x00, 0x00,  // Code for char °
        0x00, 0x34, 0x4A, 0x4A, 0x4A, 0x32, 0x00, 0x00,  // Code for char ±
        0x00, 0x7C, 0x54, 0x54, 0x54, 0x28, 0x00, 0x00,  // Code for char І
        0x00, 0x7C, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00,  // Code for char і
        0x00, 0x60, 0x38, 0x24, 0x3C, 0x60, 0x00, 0x00,  // Code for char ґ
        0x00, 0x38, 0x54, 0x54, 0x54, 0x48, 0x00, 0x00,  // Code for char µ
        0x44, 0x28, 0x10, 0x7C, 0x10, 0x28, 0x44, 0x00,  // Code for char ¶
        0x00, 0x44, 0x54, 0x54, 0x54, 0x28, 0x00, 0x00,  // Code for char ·
        0x00, 0x7C, 0x20, 0x10, 0x08, 0x7C, 0x00, 0x00,  // Code for char ё
        0x00, 0x7C, 0x21, 0x12, 0x09, 0x7C, 0x00, 0x00,  // Code for char №
        0x00, 0x7C, 0x10, 0x10, 0x28, 0x44, 0x00, 0x00,  // Code for char є
        0x00, 0x70, 0x08, 0x04, 0x04, 0x7C, 0x00, 0x00,  // Code for char »
        0x00, 0x7C, 0x08, 0x10, 0x08, 0x7C, 0x00, 0x00,  // Code for char ј
        0x00, 0x7C, 0x10, 0x10, 0x10, 0x7C, 0x00, 0x00,  // Code for char Ѕ
        0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00, 0x00,  // Code for char ѕ
        0x00, 0x7C, 0x04, 0x04, 0x04, 0x7C, 0x00, 0x00,  // Code for char ї
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,  // Code for char А
        0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,  // Code for char Б
        0x7E, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,  // Code for char В
        0x7E, 0x7E, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18,  // Code for char Г
        0x00, 0x7E, 0x7E, 0x00, 0x18, 0x18, 0x18, 0x18,  // Code for char Д
        0x18, 0x00, 0x7E, 0x7E, 0x00, 0x18, 0x18, 0x18,  // Code for char Е
        0x18, 0x18, 0x00, 0x7E, 0x7E, 0x00, 0x18, 0x18,  // Code for char Ж
        0x18, 0x18, 0x18, 0x00, 0x7E, 0x7E, 0x00, 0x18,  // Code for char З
        0x18, 0x18, 0x18, 0x18, 0x00, 0x7E, 0x7E, 0x00,  // Code for char И
        0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x7E, 0x7E,  // Code for char Й
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x7E,  // Code for char К
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00,  // Code for char Л
        0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00,  // Code for char М
        0x00, 0x7E, 0x7E, 0x3C, 0x3C, 0x18, 0x18, 0x00,  // Code for char Н
        0x00, 0x18, 0x3C, 0x7E, 0x18, 0x3C, 0x7E, 0x00,  // Code for char О
        0x00, 0x7E, 0x3C, 0x18, 0x7E, 0x3C, 0x18, 0x00,  // Code for char П
        0x00, 0x7E, 0x4B, 0x4A, 0x4A, 0x4B, 0x42, 0x00,  // Code for char Р
        0x00, 0x38, 0x55, 0x54, 0x55, 0x18, 0x00, 0x00,  // Code for char С
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x81,  // Code for char Т
        0x81, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char У
        0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,  // Code for char Ф
        0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,  // Code for char Х
        0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,  // Code for char Ц
        0xBD, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81, 0x81,  // Code for char Ч
        0xBD, 0xBD, 0xBD, 0xBD, 0x81, 0x81, 0x81, 0x81,  // Code for char Ш
        0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0x81, 0x81, 0x81,  // Code for char Щ
        0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0x81, 0x81,  // Code for char Ъ
        0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0x81,  // Code for char Ы
        0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD,  // Code for char Ь
        0x81, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD,  // Code for char Э
        0x81, 0x81, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD,  // Code for char Ю
        0x81, 0x81, 0x81, 0xBD, 0xBD, 0xBD, 0xBD, 0xBD,  // Code for char Я
        0x81, 0x81, 0x81, 0x81, 0xBD, 0xBD, 0xBD, 0xBD,  // Code for char а
        0x81, 0x81, 0x81, 0x81, 0x81, 0xBD, 0xBD, 0xBD,  // Code for char б
        0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xBD, 0xBD,  // Code for char в
        0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xBD,  // Code for char г
        0x08, 0x22, 0x00, 0x4F, 0x08, 0x22, 0x08, 0x00,  // Code for char д
        0x08, 0x22, 0x00, 0x49, 0x0C, 0x22, 0x08, 0x00,  // Code for char е
        0x08, 0x22, 0x00, 0x49, 0x08, 0x2A, 0x08, 0x00,  // Code for char ж
        0x08, 0x22, 0x00, 0x49, 0x18, 0x22, 0x08, 0x00,  // Code for char з
        0x08, 0x22, 0x00, 0x79, 0x08, 0x22, 0x08, 0x00,  // Code for char и
        0x08, 0x22, 0x10, 0x49, 0x08, 0x22, 0x08, 0x00,  // Code for char й
        0x08, 0x2A, 0x08, 0x49, 0x08, 0x22, 0x08, 0x00,  // Code for char к
        0x08, 0x22, 0x04, 0x49, 0x08, 0x22, 0x08, 0x00,  // Code for char л
        0x00, 0x7E, 0x7E, 0x00, 0x00, 0x7E, 0x7E, 0x00,  // Code for char м
        0x00, 0x68, 0x6C, 0x6E, 0x6E, 0x6C, 0x68, 0x00,  // Code for char н
        0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char о
        0x7E, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char п
        0x7E, 0x7E, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char р
        0x7E, 0x7E, 0x7E, 0x7E, 0x00, 0x00, 0x00, 0x00,  // Code for char с
        0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00, 0x00, 0x00,  // Code for char т
        0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00, 0x00,  // Code for char у
        0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00,  // Code for char ф
        0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,  // Code for char х
        0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,  // Code for char ц
        0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,  // Code for char ч
        0x00, 0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E,  // Code for char ш
        0x00, 0x00, 0x00, 0x00, 0x7E, 0x7E, 0x7E, 0x7E,  // Code for char щ
        0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x7E, 0x7E,  // Code for char ъ
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x7E,  // Code for char ы
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E,  // Code for char ь
        0x1C, 0x3E, 0x7E, 0xFC, 0x7E, 0x3E, 0x1C, 0x00,  // Code for char э
        0x38, 0x6C, 0xEE, 0x82, 0xEE, 0x6C, 0x38, 0x00,  // Code for char ю
        0x38, 0x6C, 0xEE, 0xEE, 0xEE, 0x6C, 0x38, 0x00   // Code for char я
        };

#endif
