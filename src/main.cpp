#include <Arduino.h>
#include "defines.h"
#include "variables.h"
#include "LPH91572.h"
#include "BLOCK.h"
#include "BALL.h"
#include "ROCKET.h"
#include "ANALOG_STICK.h"
#include "ANALOG_BATTON.h"
#include "DIGITAL_BATTON.h"

//-------------------------------------------------------------------------------

void show_string(uint8_t _str_namber, uint8_t _x, uint8_t _y, uint16_t _color, uint8_t _zoom_width, uint8_t _zoom_height, uint16_t _rot, bool _on_off){
	if (!_on_off) _color = SCR_COLOR;
	strcpy_P(buffer, (char*)(str_table[_str_namber]));
	LCD_Puts_Shadow (buffer, _x, _y, _color, _zoom_width, _zoom_height, _rot);
}

void message(uint8_t _game_mode, bool _on_off){
	switch(_game_mode){
		case START:
			show_string(0, 2, 80, YELLOW, 2, 2, 0, _on_off); //"BREAKOUT"
			show_string(1, 22, 120, WHITE, 1, 1, 0, _on_off); //"press start"
			show_string(2, 38, 128, WHITE, 1, 1, 0, _on_off); //"to play"
		break;
		case GAME:
			show_string(4, 48, 80, GREEN, 2, 2, 0, _on_off); //"GO!"
		break;
		case PAUSE:
			show_string(5, 24, 80, WHITE, 2, 2, 0, _on_off); //"PAUSE"
			show_string(12, 44, 112, WHITE, 1, 1, 0, _on_off);//"press"
			show_string(13, 2, 120, WHITE, 1, 1, 0, _on_off); //"START to restart"
			show_string(14, 6, 128, WHITE, 1, 1, 0, _on_off); //"ESC to continue"
		break;
		case GAME_OVER:
			show_string(6, 34, 72, ZX_RED_BR, 2, 2, 0, _on_off); //"GAME"
			show_string(7, 34, 88, ZX_RED_BR, 2, 2, 0, _on_off); //"OWER"
			show_string(1, 22, 120, WHITE, 1, 1, 0, _on_off); //"press START"
			show_string(11, 19, 159, ZX_MAGENTA_BR, 1, 1, 0, _on_off);//"HI SCORE:"
		break;
		case WIN:
			show_string(8, 6, 80, ORANGE, 2, 2, 0, _on_off); //"YOU WIN!"
			show_string(1, 2, 120, WHITE, 1, 1, 0, _on_off); //"press START"
		break;
		case SHOW_SCORE:
			show_string(10, 43, 167, ZX_GREEN_BR, 1, 1, 0, _on_off); //"SCORE:"
		break;
	}
}

//-------------------------------------------------------------------------------

BLOCK objBlock  [BLOCK_NW][BLOCK_NH];
BALL objBall    [MAX_BALLS];
ROCKET objRocket;
ANALOG_STICK objAnalogStickLeft;
ANALOG_STICK objAnalogStickRight;
ANALOG_BATTON objAnalogBatton;
DIGITAL_BATTON objDigitalBattonA;
DIGITAL_BATTON objDigitalBattonB;

//-------------------------------------------------------------------------------

void show_lives(){
	for(uint8_t _n = lives, _x = 0; _n > 0; _n--, _x = _x + 8){
		LCD_Putchar_Shadow(127, _x , SCR_HEIGHT - 8, ZX_RED_BR, 1, 1, 0);
	}
}

void hide_life(){
	LCD_Putchar(32, lives*8, SCR_HEIGHT - 8, BLACK, BLACK, 1, 1, 0);
}	

void hide_lives(){
	for(uint8_t x = 0; x < LIVES * 8; x = x + 8){
		LCD_Putchar(32, x, SCR_HEIGHT - 8, BLACK, BLACK, 1, 1, 0);
	}
}

void show_score(uint16_t _score){
	digits_array[4] = _score / 10000;
	digits_array[3] = _score % 10000 / 1000;
	digits_array[2] = _score % 1000 / 100;
	digits_array[1] = _score % 100 / 10;
    digits_array[0] = _score % 10;
	for(uint8_t d = 0, x = SCR_WIDTH - 8; d < DIGITS; d++, x = x - 8){
		LCD_Putchar(digits_array[d] + 48, x, SCR_HEIGHT - 8, ZX_GREEN_BR, BLACK, 1, 1, 0);
	}
}

void hide_score(){
	for(uint8_t d = 0, x = SCR_WIDTH - 8; d < DIGITS; d++, x = x - 8){
		LCD_Putchar(32, x, SCR_HEIGHT - 8, BLACK, BLACK, 1, 1, 0);
	}
}

void show_hi_score(uint16_t _score){
	digits_array[4] = _score / 10000;
	digits_array[3] = _score % 10000 / 1000;
	digits_array[2] = _score % 1000 / 100;
	digits_array[1] = _score % 100 / 10;
    digits_array[0] = _score % 10;
	for(uint8_t d = 0, x = SCR_WIDTH - 8; d < DIGITS; d++, x = x - 8){
		LCD_Putchar(digits_array[d] + 48, x, SCR_HEIGHT - 16, ZX_MAGENTA_BR, BLACK, 1, 1, 0);
	}
}

void hide_hi_score(){
	for(uint8_t d = 0, x = SCR_WIDTH - 8; d < DIGITS; d++, x = x - 8){
		LCD_Putchar(32, x, SCR_HEIGHT - 16, BLACK, BLACK, 1, 1, 0);
	}
}

void show_bat(){
	uint16_t _voltage = objAnalogBatton.Get_value();
	digits_array[3] = _voltage / 1000;
	digits_array[2] = _voltage % 1000 / 100;
	digits_array[1] = _voltage % 100 / 10;
	digits_array[0] = _voltage % 10;
	for(uint8_t d = 0, x = 24; d < 4; d++, x = x - 8){
		LCD_Putchar(digits_array[d] + 48, x, SCR_HEIGHT - 8, ORANGE, BLACK, 1, 1, 0);
	}
}

void hide_bat(){
for(uint8_t d = 0, x = 24; d < 4; d++, x = x - 8){
		LCD_Putchar(digits_array[d] + 48, x, SCR_HEIGHT - 8, BLACK, BLACK, 1, 1, 0);
	}
}

//-------------------------------------------------------------------------------

void collision_rocket(BALL& _objBall, ROCKET& _objRocket){
	uint8_t _val = 48;
	if(((_objBall.Get_Y() + BALL_D + 1) == ROCKET_ALT)&&(_objBall.Get_X() <= (_objRocket.Get_X() + ROCKET_W/2))&&((_objBall.Get_X() >= _objRocket.Get_X() - ROCKET_W/2 -1))&&(_objBall.Get_Y_DIR())) {
		_objBall.Set_Y_DIR(0);
		//_val = ((_objBall.Get_X()) - _objRocket.Get_X());
		if(_objBall.Get_X() < _objRocket.Get_X()){
			_objBall.Set_X_DIR(0);
		}else{
			_objBall.Set_X_DIR(1);
		}
		_val = (((_objBall.Get_X() + 9)) - (_objRocket.Get_X()));
		_objBall.Set_VX(angle_arr[_val][0]);
		_objBall.Set_VY(angle_arr[_val][1]);
		_objBall.Set_X_TEMP(_objBall.Get_VX());
		_objBall.Set_Y_TEMP(_objBall.Get_VY());
	}	
}

void collision_block(BALL& _objBall, BLOCK& _objBlock)
{
	if((_objBall.Get_X() + BALL_D >= _objBlock.Get_X()) && 
		(_objBlock.Get_X() + BLOCK_W >= _objBall.Get_X()) && 
		(_objBall.Get_Y() + BALL_D >= _objBlock.Get_Y()) && 
		(_objBlock.Get_Y() + BLOCK_H >= _objBall.Get_Y()))
		{
		_objBlock.Break();
		score = score + SCORE_STEP;
		show_score(score);
		if (score > hi_score){
			hi_score = score; //eeprom_write_word(&hi_score_adr, hi_score);
		}
		if (score == (BLOCK_NW * BLOCK_NH * SCORE_STEP)){ game_mode = WIN;}

		if (_objBall.Get_X() == (_objBlock.Get_X() + BLOCK_W)){
			coll_right++;
		}
		if ((_objBall.Get_X() + BALL_D) == _objBlock.Get_X()){
			coll_left++;
		}
		if (_objBall.Get_Y() == (_objBlock.Get_Y() + BLOCK_H)){
			coll_down++;
		}
		if ((_objBall.Get_Y() + BALL_D) == _objBlock.Get_Y()){
			coll_up++;
		}
	}
}

void collision_blocks(){
	coll_left = 0;
	coll_right = 0;
	coll_up = 0;
	coll_down = 0;
	for(uint8_t h = 0; h < BLOCK_NH; h++){
		for(uint8_t w = 0; w < BLOCK_NW; w++){
			if(!objBlock[w][h].Get_State())continue;
			collision_block(objBall[0], objBlock[w][h]);
		}
	}
	if(coll_left > coll_right) {
		objBall[0].Set_X_DIR(LEFT);
		objBall[0].Set_X_TEMP(BALL_VX);
	}
	if(coll_right > coll_left) {
		objBall[0].Set_X_DIR(RIGHT);
		objBall[0].Set_X_TEMP(BALL_VX);
	}
	if(coll_up > coll_down) {
		objBall[0].Set_Y_DIR(UP);
		objBall[0].Set_Y_TEMP(BALL_VY);
	}
	if(coll_down > coll_up) {
		objBall[0].Set_Y_DIR(DOWN);
		objBall[0].Set_Y_TEMP(BALL_VY);
	}
}

void collision_walls(BALL& _objBall){
	uint8_t _alt;
	uint8_t _down;
	if(game_mode == START){
		_alt = (BLOCK_H + BLOCK_STEP_H) * BLOCK_NH - BLOCK_STEP_H;
	} else{
		_alt = 0;
	}
	if(game_mode == GAME){
		_down = SCR_DOWN;
	} else{
		_down = SCR_HEIGHT;
	}
	if((_objBall.Get_X() == 0)||((_objBall.Get_X() + _objBall.Get_DIMM()) == SCR_WIDTH)){
		_objBall.Set_X_DIR(!_objBall.Get_X_DIR());
		_objBall.Set_X_TEMP(_objBall.Get_VX());
	}
	if(_objBall.Get_Y() == _alt){
		_objBall.Set_Y_DIR(!_objBall.Get_Y_DIR());
		_objBall.Set_Y_TEMP(_objBall.Get_VY());
	}
	if((_objBall.Get_Y() + _objBall.Get_DIMM()) == _down){
		_objBall.Set_Y_DIR(!_objBall.Get_Y_DIR());
		_objBall.Set_Y_TEMP(_objBall.Get_VY());
		if (game_mode == GAME){
			if(lives != 0){
				lives--;
				hide_life();
			}else {
				game_mode = GAME_OVER;
			}
		}
	}
}

//-------------------------------------------------------------------------------

void mode_start(){
	message(game_mode,ON);
	objRocket.Set (SCR_WIDTH/2, ROCKET_W, ORANGE);
	objBall [0].Set (SCR_WIDTH/2, SCR_HEIGHT/2, BALL_VX, BALL_VY, BALL_X_DIR, BALL_Y_DIR, BALL_D, GREEN);
	objBall [0].Show ();
	for(uint8_t h = 0; h < BLOCK_NH; h++){
		for(uint8_t w = 0; w < BLOCK_NW; w++){
			objBlock[w][h].Set(w*(BLOCK_W+BLOCK_STEP_W), h*(BLOCK_H+BLOCK_STEP_H));
			objBlock[w][h].Put();
		}
	}
	while(true){
		objBall[0].Moove();
		collision_walls(objBall[0]);
		if(objBall[0].Get_NEW()){
		objBall[0].Hide_old();
		objBall[0].Show();
		show_bat();
		}
		message(game_mode,ON);
		if(objAnalogBatton.Get_state() == BTN_ANALOG_PRESSED_START){
			message(game_mode,OFF);
			hide_bat();
			game_mode = GAME;
			return;
		}
	}	
}	

void mode_game(){
	for(uint8_t n = 0; n < 3; n++){
		delay(250);
		message(GAME,ON);
		delay(250);
		message(GAME,OFF);
	}
	message(SHOW_SCORE,ON);
	show_score(score);
	show_lives();
	while(true){
		if(objAnalogBatton.Get_state() == BTN_ANALOG_PRESSED_START){
			game_mode = PAUSE;
			return;
		}
		objRocket.Moove_At(objAnalogStickRight.Get_value_x());
		objRocket.Show();
		objBall[0].Moove();
		if(objBall[0].Get_NEW()){
			collision_rocket(objBall[0], objRocket);
			collision_walls(objBall[0]);
			collision_blocks();
			objBall[0].Hide_old();
			objBall[0].Show();
		}
		if (game_mode == GAME_OVER) return;
		delay(DELAY);
	}
}

void mode_pause(){
	message(PAUSE, ON);
	delay(1000);
	while(true){
		if(objAnalogBatton.Get_state() == BTN_ANALOG_PRESSED_ESCAPE){
			message(PAUSE, OFF);
			objBall[0].Hide();
			objRocket.Hide();
			game_mode = NEW;
			return;
		}
		if(objAnalogBatton.Get_state() == BTN_ANALOG_PRESSED_START){
			message(PAUSE, OFF);
			game_mode = GAME;
			return;
		}
	}
}

void mode_game_over(){
	objRocket.Hide();
	objBall[0].Hide();
	message(GAME_OVER, ON);
	show_hi_score(hi_score);
	delay(500);
	while(true){
		if(objAnalogBatton.Get_state() == BTN_ANALOG_PRESSED_START){
			message(GAME_OVER, OFF);
			game_mode = NEW;
			return;
		}
	}	
	
}

void mode_win(){
	objRocket.Hide();
	objBall[0].Hide();
	message(WIN, ON);
	show_hi_score(hi_score);
	delay(500);
	while(true){
		if(objAnalogBatton.Get_state() == BTN_ANALOG_PRESSED_START){
			message(WIN, OFF);
			game_mode = NEW;
			return;
		}
	}
}

void mode_new(){
	lives = LIVES;
	score = 0;
	game_mode = START;
	message(SHOW_SCORE,OFF);
	hide_score();
	hide_hi_score();
	hide_lives();
	objBall[0].Hide();
	objBall[0].Hide_old();
	objRocket.Hide();
}

void yield(){
	objBall[0].Moove();
}

//-------------------------------------------------------------------------------

void setup() {
	Serial.begin(115200);
	Serial.println("RUN");
	pinMode(PIN_BTN_A, INPUT_PULLUP);
	pinMode(PIN_BTN_B, INPUT_PULLUP);
	LCD_init();
	LCD_FillScreen (SCR_COLOR);
	objAnalogStickLeft.Set(PIN_RES_LEFT_X, PIN_RES_LEFT_Y, RES_MAP_MIN, RES_MAP_MAX, RES_CENTRE_ZONE);
	objAnalogStickRight.Set(PIN_RES_RIGHT_X, PIN_RES_RIGHT_Y, RES_MAP_MIN, RES_MAP_MAX, RES_CENTRE_ZONE);
	objAnalogBatton.Set(PIN_BTN_ANALOG);
	objDigitalBattonA.Set(PIN_BTN_A);
	objDigitalBattonB.Set(PIN_BTN_B);
}

void loop() {
  	switch(game_mode){// game mode selector
		case START: 
			mode_start();
		break;
		case GAME: 
			mode_game();
		break;
		case PAUSE: 
			mode_pause();
		break;
		case GAME_OVER: 
			mode_game_over();
		break;
		case WIN:
			mode_win();
		break;
		case NEW: 
			mode_new();
		break;
	}
}