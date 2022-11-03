#pragma once

#define SCR_WIDTH   131 // display width
#define SCR_HEIGHT  175 // display height
#define SCR_COLOR   0x0000  // back screen color
#define SCR_DOWN    167 //bottom of the screen. used in the game so as not to overwrite points and lives
#define BALL_D      3   // ball dimmension DxD
#define BALL_VX     1   // start X vector
#define BALL_VY     1	// start Y vector
#define BALL_X_DIR  0	// 1 - _x++; 0 - _x--
#define BALL_Y_DIR  0	// 1 - _y++; 0 - _y--
#define LEFT        0	// for LEFT
#define RIGHT       1	// for RIGHT
#define UP          0	// for UP
#define DOWN        1	// for DOWN
#define MAX_BALLS   1   // maximum number of balls
#define BLOCK_W     7   // block width
#define BLOCK_H     3   // block height
#define BLOCK_NW    16  // number of blocks wide
#define BLOCK_NH    10  // number of blocks in height
#define BLOCK_SHIFT 2	// blocks horisontal shift
#define BLOCK_STEP_W    1   // step between blocks (widht?)
#define BLOCK_STEP_H    1   // step between blocks (height?)
#define ROCKET_W    16  // rocket widht
#define ROCKET_H    4   // rocket height 
#define ROCKET_VX   2   // rocket speed
#define ROCKET_ALT  160 // rocket altitude

#define PIN_BAT     35  // pin for ADC read voltage from BAT
#define PIN_BTN_A   25  // pin for btn left (pull up)
#define PIN_BTN_B   26  // pin for btn right (pull up)
#define PIN_BTN_ANALOG  12  // pin for 3 analog btns (1-4095, 2-2700, 3-2000, NC-0)

#define PIN_RES_LEFT_X  32  // pin for left horisontal resistor
#define PIN_RES_LEFT_Y  34  // pin for left vertical resistor
#define PIN_RES_RIGHT_X 27  // pin for right horisontal resistor
#define PIN_RES_RIGHT_Y 33  // pin for right vertical resistor

#define RES_MAP_MIN     0
#define RES_MAP_MAX     131 // == display width
#define RES_CENTRE_ZONE 10

#define BTN_ANALOG_0_1_BORDER   1000    // 0-2000
#define BTN_ANALOG_1_2_BORDER   2350    // 2000-2700
#define BTN_ANALOG_2_3_BORDER   3400    // 2700-4095

#define BTN_ANALOG_PRESSED_NO_ONE   0   //no analog btn pressed
#define BTN_ANALOG_PRESSED_ESCAPE   1   //escape analog btn pressed
#define BTN_ANALOG_PRESSED_SELECT   2   //select analog btn pressed
#define BTN_ANALOG_PRESSED_START    3   //start analog btn pressed

#define BTN_DIGITAL_PRESSED_NO_ONE  0   // no pressed btns
//#define BTN_DIGITAL_PRESSED_A       1   // btn start pressed
//#define BTN_DIGITAL_PRESSED_B       2   // btn left pressed

#define ON          1   // for ON
#define OFF         0   // for OFF
#define START       0   // game modes:
#define GAME        1   // --//--
#define PAUSE       2   // --//--
#define GAME_OVER   3   // --//--
#define WIN         4   // --//--
#define NEW         5   // --//--
#define SHOW_SCORE  6   // --//--
#define LIVES       5   // max lives(lifes?)
#define SCORE_STEP  50  //scoring step
#define DIGITS      5   //digits of score
#define DELAY       5   // game speed
