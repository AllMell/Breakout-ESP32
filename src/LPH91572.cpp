#include <Arduino.h>
#include <SPI.h>
#include "Symbols.h"
#include "LPH91572.h"

//===============================================================
//                        init V
//===============================================================
void LCD_init(void)
{ SPI.begin();
  delay(10);
  pinMode(SS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  digitalWrite(SS, LOW);
  
 #ifdef _USE_HARDWARE_RESET
  pinMode(LCD_RESET, OUTPUT);
  digitalWrite(LCD_RESET, LOW);
  delay(10);
  digitalWrite(LCD_RESET, HIGH);
 #endif 

  delay(10);
  digitalWrite(LCD_RS, LOW);
  Send_to_lcd(CMD, 0x01); //soft reset
  delay(10);

  //Memory Access Control (Направление заполнения области дисплея (памяти): 0bVHRXXXXX, V - заполнение по вертикали (0 - сверху-вниз, 1 - снизу-вверх),
  //H - заполнение по горизонтали (0 - слева-направо, 1 - справа-налево), R - меняются местами строки и столбцы (при этом заполнение остается сверху-вниз, слева-направо))
  Send_to_lcd(CMD, 0x36); 
  Send_to_lcd(DAT, 0b0000000);

  delay(10);

  Send_to_lcd(DAT, 0x00);
  Send_to_lcd(CMD, 0x11); //wake up from sleep mode
  delay(10);

  
  Send_to_lcd(CMD, 0x3A); //set color mode
#ifdef _8_BIT_COLOR
  Send_to_lcd(DAT, 0x02); //256 colors
#else
  Send_to_lcd(DAT, 0x05); //65536 colors
#endif
  delay(10);
  Send_to_lcd(CMD, 0x29); //power on display
  delay(10);
  // 30MHz is maximum for that display
  // standart speed is 13MHz

#if defined(__AVR__)
  SPI.beginTransaction(SPISettings(8000000L, MSBFIRST, SPI_MODE0));
#elif defined(ESP32)
  SPI.beginTransaction(SPISettings(30000000L, MSBFIRST, SPI_MODE0));
#endif
}

//===============================================================
//LCD driver function (RS==0 - command, RS==1 - data) V
//===============================================================


void Send_to_lcd (uint8_t RS, uint8_t data)
{ 
    digitalWrite(LCD_RS, RS);

    SPI.transfer(data);
}


//===============================================================
//              Задание прямоугольной области экрана V
//===============================================================
void SetArea(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
{
  Send_to_lcd( CMD, 0x2A );  //задаем область по X
  Send_to_lcd( DAT, x1 );    //начальная
  Send_to_lcd( DAT, x2 );    //конечная

  Send_to_lcd( CMD, 0x2B );  //задаем область по Y
  Send_to_lcd( DAT, y1 );    //начальная
  Send_to_lcd( DAT, y2 );    //конечная

  Send_to_lcd( CMD, 0x2C );  //отправляем команду на начало записи в память и начинаем посылать данные
}


//===============================================================
//                          Рисуем точку V
//===============================================================
void Put_Pixel (uint8_t x, uint8_t y, uint16_t color)
{
  SetArea( x, x, y, y );
  digitalWrite (LCD_RS, HIGH);

#ifdef _8_BIT_COLOR //(8-ми битовая цветовая палитра (256 цветов))
  Send_to_lcd( DAT, color ); //Данные - задаём цвет пикселя
#else             //(16-ти битовая цветовая палитра (65536 цветов))
  Send_to_lcd( DAT, (color >> 8) );
  Send_to_lcd( DAT, ((color) & 0xFF));
#endif
}

//===============================================================
//           Функция прорисовки символа на дисплее V
//===============================================================
void Send_Symbol (char symbol, uint8_t x, uint8_t y, uint16_t t_color, uint16_t b_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot)
{
  char temp_symbol;
  uint8_t a, b, zw, zh, mask;

  for ( a = 0; a < 8; a++) //Перебираю 8 байт, составляющих символ
  {
    temp_symbol = pgm_read_byte (&zx_font_8x8[symbol - 32][a]); //zx_font_8x8[symbol - 32][a];
    zw = 0;
    while (zw != zoom_width) //Вывод байта выполняется zw раз
    {
      mask = 0x01;
      switch (rot)
      {
        case 0: case 180: SetArea( x + zw, x + zw, y, y + (zoom_height * 8) - 1 ); break;
        case 90: case 270: SetArea( x, x + (zoom_height * 8) - 1, y + zw, y + zw ); break;
      }
      digitalWrite (LCD_RS, HIGH); //Передаются данные
      for ( b = 0; b < 8; b++ ) //Цикл перебирания 8 бит байта
      {
        zh = zoom_height; //в zoom_height раз увеличится высота символа
        while (zh != 0) //Вывод пикселя выполняется z раз
        {
          if (temp_symbol & mask)
          {
#ifdef _8_BIT_COLOR //(8-ми битовая цветовая палитра (256 цветов))
            Send_to_lcd( DAT, t_color ); //Данные - задаём цвет пикселя
#else             //(16-ти битовая цветовая палитра (65536 цветов))
            Send_to_lcd( DAT, (t_color >> 8) ); Send_to_lcd( DAT, (t_color & 0xFF));
#endif
          }
          else
          {
#ifdef _8_BIT_COLOR //(8-ми битовая цветовая палитра (256 цветов))
            Send_to_lcd( DAT, b_color ); //Данные - задаём цвет пикселя
#else             //(16-ти битовая цветовая палитра (65536 цветов))
            Send_to_lcd( DAT, (b_color >> 8) ); Send_to_lcd( DAT, (b_color & 0xFF));
#endif
          }
          zh--;
        }
        mask <<= 1; //Смещаю содержимое mask на 1 бит влево;
      }
      zw++;
    }
    switch (rot)
    {
      case 0: case 180: x = x + zoom_width;  break; //Получить адрес начального пикселя по оси x для вывода очередного байта
      case 90: case 270: y = y + zoom_width; break; //Получить адрес начального пикселя по оси y для вывода очередного байта
    }
  }
}

//===============================================================
// Функция вывода одного символа ASCII-кода (из файла Symbols.h) V
//===============================================================
void LCD_Putchar(char symbol, uint8_t x, uint8_t y, uint16_t t_color, uint16_t b_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot)
{
  uint8_t m;
  if (zoom_width == 0)   zoom_width = 1;
  if (zoom_height == 0)  zoom_height = 1;
  switch (rot)
  {
    case 0:  //Начальный адрес осей Х и У - левый верхний угол дисплея
      Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
      break;
    //================================
    case 90:
      m = y; y = x; x = m;
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x40); //Начальный адрес осей Х и У - правый верхний угол дисплея
      Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00);
      break;
    //================================
    case 180:
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0xC0); //Начальный адрес осей Х и У - правый нижний угол дисплея
      Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00);
      break;
    //================================
    case 270:
      m = y; y = x; x = m;
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x80); //Начальный адрес осей Х и У - левый нижний угол дисплея
      Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00);
      break;
    //================================
    default:
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00); //Начальный адрес осей Х и У - левый верхний угол дисплея
      Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00);
      //=================================
  };
}

//===============================================================
//          Функция вывода строки, расположенной в ram V
//===============================================================
void LCD_Puts(char *str, uint8_t x, byte y,  uint16_t t_color, uint16_t b_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot)
{
  uint8_t i = 0, j = 0; 

  if (zoom_width == 0)   zoom_width = 1;
  if (zoom_height == 0)  zoom_height = 1;

  while (str[i]) //x и y - адрес пикселя начальной позиции; с увеличением переменной i адрес вывода очередного символа смещается на i*8 (чем организуются столбцы дисплея)
  {
    if ((str[i]==208)||(str[i]==209)) {
        if ((str[i]==208)&&(str[i+1]==129)){
        str[i+1]=208;
      }
      if ((str[i]==209)&&(str[i+1]==145)){
        str[i+1]=209;
      }
      j++;
      i++;
    }
   
    LCD_Putchar(str[i], x + ((i - j) * 8 * zoom_width), y, t_color, b_color, zoom_width, zoom_height, rot);
    i++;
    
  }
}


//===============================================================
//     Функция прорисовки символа на дисплее без цвета фона V
//===============================================================
void Send_Symbol_Shadow (char symbol, uint8_t x, uint8_t y, uint16_t t_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot)
{
  char temp_symbol;
  uint8_t a, b, zw, zh, mask;
  uint8_t m, n;
  m = x;
  n = y;
  
  for ( a = 0; a < 8; a++) //Перебираю 8 байт, составляющих символ
  {
    temp_symbol = pgm_read_byte (&zx_font_8x8[symbol - 32][a]); //temp_symbol = zx_font_8x8[symbol - 32][a];
    zw = 0;
    while (zw != zoom_width) //Вывод байта выполняется zw раз
    {
      switch (rot)
      {
        case 0: case 180: n = y; break;
        case 90: case 270: m = x; break;
      }
      mask = 0x01;
      for ( b = 0; b < 8; b++ ) //Цикл перебирания 8 бит байта
      {
        zh = 0; //в zoom_height раз увеличится высота символа
        while (zh != zoom_height) //Вывод пикселя выполняется z раз
        {
          switch (rot)
          {
            case 0: case 180:
              if (temp_symbol & mask)
              {
                Put_Pixel (m + zw, n + zh, t_color);
              }
              break;
            case 90: case 270:
              if (temp_symbol & mask)
              {
                Put_Pixel (m + zh, n + zw, t_color);
              }
              break; //Получить адрес начального пикселя по оси y для вывода очередного байта
          }
          zh++;
        }
        mask <<= 1; //Смещаю содержимое mask на 1 бит влево;
        switch (rot)
        {
          case 0: case 180: n = n + zoom_height; break;
          case 90: case 270: m = m + zoom_height; break;
        }
      }
      zw++;
    }
    switch (rot)
    {
      case 0: case 180: m = m + zoom_width; break;
      case 90: case 270: n = n + zoom_width; break;
    }
  }
}

//===============================================================
// Функция вывода одного символа ASCII-кода без цвета фона V
//===============================================================
void LCD_Putchar_Shadow (char symbol, uint8_t x, uint8_t y, uint16_t t_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot)
{
  uint8_t m;
  if (zoom_width == 0)   zoom_width = 1;
  if (zoom_height == 0)  zoom_height = 1;
  switch (rot)
  {
    case 0:  //Начальный адрес осей Х и У - левый верхний угол дисплея
      Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
      break;
    //================================
    case 90:
      m = y; y = x; x = m;
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x40); //Начальный адрес осей Х и У - правый верхний угол дисплея
      Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00);
      break;
    //================================
    case 180:
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0xC0); //Начальный адрес осей Х и У - правый нижний угол дисплея
      Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00);
      break;
    //================================
    case 270:
      m = y; y = x; x = m;
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x80); //Начальный адрес осей Х и У - левый нижний угол дисплея
      Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00);
      break;
    //================================
    default:
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00); //Начальный адрес осей Х и У - левый верхний угол дисплея
      Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
      Send_to_lcd(CMD, 0x36);
      Send_to_lcd(DAT, 0x00);
      //=================================
  };
}

//===============================================================
//   Функция вывода строки, расположенной в ram без цвета фона V
//===============================================================
void LCD_Puts_Shadow(char *str, uint8_t x, uint8_t y,  uint16_t t_color, uint8_t zoom_width, uint8_t zoom_height, uint16_t rot)
{
  uint8_t i = 0, j = 0;

  if (zoom_width == 0)   zoom_width = 1;
  if (zoom_height == 0)  zoom_height = 1;

  while (str[i]) //x и y - адрес пикселя начальной позиции; с увеличением переменной i адрес вывода очередного символа смещается на i*8 (чем организуются столбцы дисплея)
  {
    if ((str[i]==208)||(str[i]==209)) {
      if ((str[i]==208)&&(str[i+1]==129)){
        str[i+1]=208;
      }
      if ((str[i]==209)&&(str[i+1]==145)){
        str[i+1]=209;
      }
      j++;
      i++;
    }
    LCD_Putchar_Shadow(str[i], x + ((i-j) * 8 * zoom_width), y, t_color, zoom_width, zoom_height, rot);
    i++;
  }
}


//===============================================================
//                  ЗАЛИВКА ЭКРАНА ЦВЕТОМ 
//===============================================================
void LCD_FillScreen (uint16_t color)
{
  uint16_t x;
  SetArea( 0, 131, 0, 175 );   //Область всего экрана

  digitalWrite(LCD_RS, HIGH);

  //Данные - задаём цвет пикселя
  for (x = 0; x < 23232; x++)  // 23232 - это 132 * 176

  {
#ifdef _8_BIT_COLOR //(8-ми битовая цветовая палитра (256 цветов))
    Send_to_lcd( DAT, color ); //Данные - задаём цвет пикселя
#else     //(16-ти битовая цветовая палитра (65536 цветов))
    Send_to_lcd( DAT, (color >> 8) ); Send_to_lcd( DAT, (color & 0xFF));
	//Send_to_lcd( DAT, (0x00)); Send_to_lcd( DAT, (0x00)); 
#endif
  }
}

//===============================================================
//                 ФУНКЦИЯ ВЫВОДА ИЗОБРАЖЕНИЯ V
//===============================================================

  void LCD_Output_image (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t *img, uint16_t rot)
  {
  uint8_t m;
  switch (rot)
  {
  case 0:
  Send_Image (x, y, width, height, img, rot);
  break;
  //================================
  case 90:
  m=y; y=x; x=m;
  Send_to_lcd(CMD, 0x36);
  Send_to_lcd(DAT, 0x40); //Начальный адрес осей Х и У - правый верхний угол дисплея
  Send_Image (x, y, width, height, img, rot);
  Send_to_lcd(CMD, 0x36);
  Send_to_lcd(DAT, 0x00);
  break;
  //================================
  case 180:
  Send_to_lcd(CMD, 0x36);
  Send_to_lcd(DAT, 0xC0); //Начальный адрес осей Х и У - правый нижний угол дисплея
  Send_Image (x, y, width, height, img, rot);
  Send_to_lcd(CMD, 0x36);
  Send_to_lcd(DAT, 0x00);
  break;
  //================================
  case 270:
  m=y; y=x; x=m;
  Send_to_lcd(CMD, 0x36);
  Send_to_lcd(DAT, 0x80); //Начальный адрес осей Х и У - левый нижний угол дисплея
  Send_Image (x, y, width, height, img, rot);
  Send_to_lcd(CMD, 0x36);
  Send_to_lcd(DAT, 0x00);
  break;
  //================================
  default:
  Send_to_lcd(CMD, 0x36);
  Send_to_lcd(DAT, 0x00); //Начальный адрес осей Х и У - левый верхний угол дисплея
  Send_Image (x, y, width, height, img, rot);
  Send_to_lcd(CMD, 0x36);
  Send_to_lcd(DAT, 0x00);
  //=================================
  };
  }

//===============================================================
//          Функция для обеспечения вывода изображения  V
//===============================================================
//Вывод картинки с Image2Lcd и NokiaImage\reator должен выполняться слева-направо сверху-вниз.
//x, y - начало области вывода изображения; width и height - ширина и высота изображения

  void Send_Image (uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t *img, uint16_t rot)
  {
  uint8_t x1, y1;

  switch (rot)
  {
  case 0: case 180:
  for(y1=y; y1<(y+height); y1++)
  {
   SetArea( x, x+(width-1), y1, y1 );
   for(x1=x; x1<x+width; x1++)
   {
    #ifdef _8_BIT_COLOR //(8-ми битовая цветовая палитра (256 цветов))
    Send_to_lcd( DAT, *img++ ); //Данные - задаём цвет пикселя
    #else     //(16-ти битовая цветовая палитра (65536 цветов))
    Send_to_lcd( DAT, *img++ ); Send_to_lcd( DAT, *img++ );
    #endif
   }
  }
  break;

  case 90: case 270:
  for(x1=x; x1<x+height; x1++)
  {
   SetArea( x1, x1, y, y+(width-1) );
   for(y1=y; y1<y+width; y1++)
   {
    #ifdef _8_BIT_COLOR //(8-ми битовая цветовая палитра (256 цветов))
    Send_to_lcd( DAT, *img++ ); //Данные - задаём цвет пикселя
    #else     //(16-ти битовая цветовая палитра (65536 цветов))
    Send_to_lcd( DAT, *img++ ); Send_to_lcd( DAT, *img++ );
    #endif
   }
  }
  break;
  };
  }

#ifdef _GEOMETRICAL
//===============================================================
//                      НАРИСОВАТЬ ЛИНИЮ V
//===============================================================
void LCD_DrawLine (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color)
{
  uint8_t  x, y, d, dx, dy, i, i1, i2, kx, ky;
  uint8_t flag;

  dx = x2 - x1;
  dy = y2 - y1;
  if (dx == 0 && dy == 0) Put_Pixel(x1, y1, color);  //Точка
  else      //Линия
  {
    kx = 1;
    ky = 1;
    if ( dx < 0 )
    {
      dx = -dx;
      kx = -1;
    }
    else if (dx == 0) kx = 0;
    if (dy < 0)
    {
      dy = -dy;
      ky = -1;
    }
    if (dx < dy)
    {
      flag = 0;
      d = dx;
      dx = dy;
      dy = d;
    }
    else flag = 1;
    i1 = dy + dy;
    d = i1 - dx;
    i2 = d - dx;
    x = x1;
    y = y1;

    for (i = 0; i < dx; i++)
    {
      Put_Pixel(x, y, color);
      if (flag) x += kx;
      else y += ky;
      if ( d < 0 ) d += i1;
      else
      {
        d += i2;
        if (flag) y += ky;
        else x += kx;
      }
    }
    Put_Pixel(x, y, color);
  }
}

//===============================================================
//                  НАРИСОВАТЬ РАМКУ V
//===============================================================
void LCD_DrawRect (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, uint8_t size, uint16_t color)
{
  uint8_t i;
  uint8_t x2 = x1 + (width - 1), y2 = y1 + (height - 1); //Конечные размеры рамки по осям х и у
  for ( i = 1; i <= size; i++) // size - толщина рамки
  {
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    x1++; // Увеличиваю толщину рамки, если это задано
    y1++;
    x2--;
    y2--;
  }
}

//===============================================================
//                  НАРИСОВАТЬ РАМКУ (CВОЯ ВЕРСИЯ) V
//===============================================================
void LCD_DrawRect_my (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, uint8_t size, uint16_t color)
{
  uint8_t i, xx, yy;

  uint8_t x2 = x1 + (width - 1);  //Конечные размеры рамки по осям х и у
  uint8_t y2 = y1 + (height - 1);

  for ( i = 1; i <= size; i++){ // size - толщина рамки
  

    for (yy = y1; yy < y2; yy++){
    Put_Pixel (x1, yy, color);

	
  }

    for (xx = x1; xx < x2; xx++){
    Put_Pixel (xx, y2, color);
  }

    for (yy = y2; yy > y1; yy--){
    Put_Pixel (x2, yy, color);
  }

    for (xx = x2; xx > x1; xx--){
    Put_Pixel (xx, y1, color);
  }
    x1++; // Увеличиваю толщину рамки, если это задано
    y1++;
    x2--;
    y2--;
  }
}
  
//===============================================================
//              ЗАПОЛНИТЬ ПРЯМОУГОЛЬНИК ЦВЕТОМ COLOR V
//===============================================================
void LCD_FillRect (uint8_t x1, uint8_t y1, uint8_t width, uint8_t height, uint16_t color)
{
  uint16_t x, y;

  SetArea( x1, x1 + (width - 1), y1, y1 + (height - 1) );
  digitalWrite(LCD_RS, HIGH);

  y = width * height;         //Количество пикселей в прямоугольнике
  for (x = 0; x < y; x++)
  {
#ifdef _8_BIT_COLOR //(8-ми битовая цветовая палитра (256 цветов))
    Send_to_lcd( DAT, color ); //Данные - задаём цвет пикселя
#else     //(16-ти битовая цветовая палитра (65536 цветов))
    Send_to_lcd( DAT, (color >> 8) ); Send_to_lcd( DAT, (color & 0xFF));
#endif
  }
}

//===============================================================

#endif
