#pragma once

uint8_t coll_left = 0;	//for counting hits in blocks
uint8_t coll_right = 0;	
uint8_t coll_up = 0;	
uint8_t coll_down = 0;	

uint8_t game_mode = START; 	//initial game mode
uint8_t lives = LIVES;		//lifes?
uint16_t score = 0;			//for score
uint16_t hi_score = 0;		//for record score
uint8_t digits_array[DIGITS];//for indicate score

//rebound angles from the racket
const uint8_t angle_arr[19][2] = {{2,3},{1,1},{3,2},{2,1},{5,2},{3,1},{4,1},{5,1},{6,1},{0,1},{6,1},{5,1},{4,1},{3,1},{5,2},{2,1},{3,2},{1,1},{2,3}};

char buffer[16];//for messages
const char str_0[] = "BREAKOUT";
const char str_1[] = "press START";
const char str_2[] = "to play";
const char str_3[] = "to continue";
const char str_4[] = "GO!";
const char str_5[] = "PAUSE";
const char str_6[] = "GAME";
const char str_7[] = "OVER";
const char str_8[] = "YOU WIN!";
const char str_9[] = "LEVEL:";
const char str_10[] = "SCORE:";
const char str_11[] = "HI SCORE:";
const char str_12[] = "press";
const char str_13[] = "START to restart";
const char str_14[] = "ESC to continue";
const char* const str_table[] = {str_0, str_1, str_2, str_3, str_4, str_5, str_6, str_7, str_8, str_9, str_10, str_11, str_12, str_13, str_14};


