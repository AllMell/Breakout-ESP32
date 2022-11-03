#include <Arduino.h>
#include "LPH91572.h" //132x176
#include "pgmspace.h"
//#include <avr/eeprom.h>
//uint16_t EEMEM hi_score_adr;	// eeprom hi score adress

#define SCR_WIDTH 	 131	  // display width
#define SCR_HEIGHT 	 175	  // display height
#define SCR_COLOR 0x0000    // back screen color
#define SCR_DOWN     167	//bottom of the screen. used in the game so as not to overwrite points and lives
#define BALL_D 		   3	  // ball dimmension DxD
#define BALL_VX			1		// start X vector
#define BALL_VY			1	// start Y vector
#define BALL_X_DIR		0	// 1 - _x++; 0 - _x--
#define BALL_Y_DIR		0	// 1 - _y++; 0 - _y--
#define LEFT			0	// for LEFT
#define RIGHT			1	// for RIGHT
#define UP				0	// for UP
#define DOWN			1	// for DOWN
#define MAX_BALLS      1    // maximum number of balls
#define BLOCK_W 	   7	  // block width
#define BLOCK_H		   3	  // block height
#define BLOCK_NW	  16  // number of blocks wide
#define BLOCK_NH       10	  // number of blocks in height
#define BLOCK_SHIFT    2	// blocks horisontal shift
#define BLOCK_STEP_W	1 // step between blocks (widht?)
#define BLOCK_STEP_H	1 // step between blocks (height?)
#define ROCKET_W      16    // rocket widht
#define ROCKET_H       4    // rocket height 
#define ROCKET_VX      2    // rocket speed
#define ROCKET_ALT    160    // rocket altitude
#define BTN_LEFT	   25	// pin for btn left (pull up)
#define BTN_RIGHT	   26	// pin for btn right (pull up)
#define BTN_1
#define BTN_2
#define BTN_3
#define RES_LEFT_VER
#define RES_LEFT_HOR
#define RES_RIGHT_VER
#define RES_RIGHT_HOR
#define BAT_PIN			35	// pin for ADC read voltage from BAT
#define PRESSED_NO_ONE	0	// no pressed btns
#define PRESSED_START	1	// btn start pressed
#define PRESSED_LEFT	2	// btn left pressed
#define PRESSED_RIGHT	3	// btn right pressed
#define ON             1    // for ON
#define OFF            0    // for OFF
#define GAME_MODES_Q	6   // game modes quantity
#define START			0	// game modes:
#define GAME			1	// --//--
#define PAUSE			2	// --//--
#define GAME_OVER		3	// --//--
#define WIN 			4	// --//--
#define NEW				5	// --//--
#define SHOW_SCORE		6	// --//--
#define LIVES			5	// max lives(lifes?)
#define SCORE_STEP		50	//scoring step
#define DIGITS			5	//digits of score
#define DELAY			5	  // game speed

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
const char str_1[] = "press any button";
const char str_2[] = "to start";
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
const char str_13[] = "< to restart";
const char str_14[] = "> to continue";
const char* const str_table[] = {str_0, str_1, str_2, str_3, str_4, str_5, str_6, str_7, str_8, str_9, str_10, str_11, str_12, str_13, str_14};

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
			show_string(1, 2, 120, WHITE, 1, 1, 0, _on_off); //"press any batton"
			show_string(2, 34, 128, WHITE, 1, 1, 0, _on_off); //"to start"
		break;
		case GAME:
			show_string(4, 48, 80, GREEN, 2, 2, 0, _on_off); //"GO!"
		break;
		case PAUSE:
			show_string(5, 24, 80, WHITE, 2, 2, 0, _on_off); //"PAUSE"
			show_string(12, 44, 112, WHITE, 1, 1, 0, _on_off);//"press"
			show_string(13, 12, 120, WHITE, 1, 1, 0, _on_off); //"< to restart"
			show_string(14, 12, 128, WHITE, 1, 1, 0, _on_off); //"> to continue"
		break;
		case GAME_OVER:
			show_string(6, 34, 72, ZX_RED_BR, 2, 2, 0, _on_off); //"GAME"
			show_string(7, 34, 88, ZX_RED_BR, 2, 2, 0, _on_off); //"OWER"
			show_string(1, 2, 120, WHITE, 1, 1, 0, _on_off); //"press any batton"
			show_string(11, 19, 159, ZX_MAGENTA_BR, 1, 1, 0, _on_off);//"HI SCORE:"
		break;
		case WIN:
			show_string(8, 6, 80, ORANGE, 2, 2, 0, _on_off); //"YOU WIN!"
			show_string(1, 2, 120, WHITE, 1, 1, 0, _on_off); //"press any batton"
		break;
		case SHOW_SCORE:
			show_string(10, 43, 167, ZX_GREEN_BR, 1, 1, 0, _on_off); //"SCORE:"
		break;
	}
}

//-------------------------------------------------------------------------------

class BLOCK {
	public:
		void Set(uint8_t x, uint8_t y){_x=x;_y=y;}
		bool Get_State(){return _state;}
		uint8_t Get_X(){return _x;}
		uint8_t Get_Y(){return _y;}
		void Put(){LCD_FillRect (_x + BLOCK_SHIFT, _y, BLOCK_W, BLOCK_H, random(1, WHITE));_state = ON;}
		void Break(){LCD_FillRect (_x + BLOCK_SHIFT, _y, BLOCK_W, BLOCK_H, SCR_COLOR);_state = OFF;}
	private:
      	bool _state;
		uint8_t _x;
		uint8_t _y;
};

class BALL {
	public:
		void Set(uint8_t x, uint8_t y, uint8_t vx, uint8_t vy, bool x_dir, bool y_dir, uint8_t dimm, uint16_t color){
			_x = x;
			_y = y;
			_vx = vx;
			_vy = vy;
			_x_dir = x_dir;
			_y_dir = y_dir;		
			_dimm = dimm;
			_color = color;
			_x_temp = 0;
			_y_temp = 0;
			_x_old = _x;
			_y_old = _y;
			_new = 0;
		}
		
		void Set_X(uint8_t x){_x = x;}
		void Set_Y(uint8_t y){_y = y;}
		void Set_VX(uint8_t vx){_vx = vx;}
		void Set_VY(uint8_t vy){_vy = vy;}
		void Set_X_DIR(bool x_dir){_x_dir = x_dir;}
		void Set_Y_DIR(bool y_dir){_y_dir = y_dir;}
		void Set_X_TEMP(uint8_t x_temp){_x_temp = x_temp;}
		void Set_Y_TEMP(uint8_t y_temp){_y_temp = y_temp;}
		void Set_COLOR(uint16_t color){_color = color;}
		void Reset_NEW(){_new = false;}
		uint8_t Get_X(){return _x;}
		uint8_t Get_Y(){return _y;}
		uint8_t Get_VX(){return _vx;}
		uint8_t Get_VY(){return _vy;}
		bool Get_X_DIR(){return _x_dir;}
		bool Get_Y_DIR(){return _y_dir;}
		uint8_t Get_DIMM(){return _dimm;}
		uint16_t Get_Color(){return _color;}
		void Show(){LCD_FillRect (_x, _y, _dimm, _dimm, _color); _x_old = _x; _y_old = _y; _new = false;}
		void Hide(){LCD_FillRect (_x, _y, _dimm, _dimm, SCR_COLOR);}
		void Hide_old(){LCD_FillRect (_x_old, _y_old, _dimm, _dimm, SCR_COLOR);}
		bool Get_NEW(){return _new;}

		void Moove(){
			if (!_new){
				if (_x_temp == _vx){if(_x_dir){_x++; _new = true;} else {_x--; _new = true;}}
				if (_y_temp == _vy){if(_y_dir){_y++; _new = true;} else {_y--; _new = true;}}
				if (_x_temp == _vx){_x_temp = 0;} 
				if (_y_temp == _vy){_y_temp = 0;} 
				_x_temp ++;
				_y_temp ++;
			}
		}	

		private:
			bool _new;
			uint8_t _x_old;
			uint8_t _y_old;
			uint8_t _x_temp;
			uint8_t _y_temp;
			uint8_t _x;
			uint8_t _y;
			uint8_t _vx;
			uint8_t _vy;
			bool _x_dir;
			bool _y_dir;
			uint8_t _dimm;
			uint16_t _color;
};

class ROCKET {
	
	public:
		
		void Set(uint8_t x, uint8_t width, uint16_t color){
			_x=x; _width=width; _color=color; _x_old = _x;
		}
		uint8_t Get_X(){return _x;}
		void Show(){
			if(_x < _width/2){
				LCD_FillRect (0, ROCKET_ALT, ROCKET_W - (ROCKET_W/2 - _x), ROCKET_H, _color);
			}else if(_x > (SCR_WIDTH - _width/2)){
				LCD_FillRect (_x - _width/2, ROCKET_ALT, SCR_WIDTH - _x + _width/2, ROCKET_H, _color);
			}else{
				LCD_FillRect (_x - _width/2, ROCKET_ALT, _width, ROCKET_H, _color);
			}
		}	
		void Hide(){
			if(_x < _width/2){
				LCD_FillRect (0, ROCKET_ALT, ROCKET_W - (ROCKET_W/2 - _x), ROCKET_H, SCR_COLOR);
			}else if(_x > (SCR_WIDTH - _width/2)){
				LCD_FillRect (_x - _width/2, ROCKET_ALT, SCR_WIDTH - _x + _width/2, ROCKET_H, SCR_COLOR);
			}else{
				LCD_FillRect (_x - _width/2, ROCKET_ALT, _width, ROCKET_H, SCR_COLOR);
			}
		}	
		
		void Moove_Left(){
			Hide();
			if(_x != 0){_x--;}	
		}	
		
		void Moove_Right(){
			Hide();
			if(_x != SCR_WIDTH){_x++;}
		}	

	private:
	
		uint8_t _x;
		uint8_t _x_old;
		uint8_t _width;
		uint8_t _height;
		uint16_t _color;
	
};

//-------------------------------------------------------------------------------

BLOCK objBlock  [BLOCK_NW][BLOCK_NH];
BALL objBall    [MAX_BALLS];
ROCKET objRocket;

//-------------------------------------------------------------------------------

uint8_t btn_state(){
	if(!digitalRead(BTN_LEFT)&&!digitalRead(BTN_RIGHT)){
		return PRESSED_START;} //btn start
	else if(!digitalRead(BTN_LEFT)){
		return PRESSED_LEFT;} //btn left
	else if(!digitalRead(BTN_RIGHT)){
		return PRESSED_RIGHT;} //btn right
	else {
		return PRESSED_NO_ONE;} //no press btn
}

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
	uint16_t _voltage = analogRead(BAT_PIN);
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
		
		if(btn_state() != PRESSED_NO_ONE){
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

	switch(btn_state()){
		case PRESSED_NO_ONE: //no press btn
			//objRocket.Show();
		break;
		case PRESSED_START: //press btn start
			game_mode = PAUSE;
			return;
			//delay(DELAY);
		break;
		case PRESSED_LEFT: //press btn left
			objRocket.Moove_Left();
		break;
		case PRESSED_RIGHT: //press btn right
			objRocket.Moove_Right();
		break;
	}

	objRocket.Show();
	objBall[0].Moove();

	if(objBall[0].Get_NEW()){
		collision_rocket(objBall[0], objRocket);
		collision_walls(objBall[0]);
		collision_blocks();
		objBall[0].Hide_old();
		objBall[0].Show();
		//objBall[0].Reset_NEW();
	}
	if (game_mode == GAME_OVER) return;
	delay(DELAY);
	}
}

void mode_pause(){
	message(PAUSE, ON);
	delay(1000);
	while(true){
		if(btn_state() == PRESSED_LEFT){
			message(PAUSE, OFF);
			objBall[0].Hide();
			objRocket.Hide();
			game_mode = NEW;
			return;
		}
		if(btn_state() == PRESSED_RIGHT){
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
		if(btn_state() != PRESSED_NO_ONE){
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
		if(btn_state() != PRESSED_NO_ONE){
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
	//Serial.begin(115200);
	//Serial.println("RUN");
	pinMode(BTN_LEFT, INPUT_PULLUP);
	pinMode(BTN_RIGHT, INPUT_PULLUP);
	LCD_init();
	LCD_FillScreen (SCR_COLOR);
	//hi_score = eeprom_read_word(&hi_score_adr);	
	
	//game_mode = START;
	
	//while(true){
	//	LCD_FillScreen(WHITE);
	//	LCD_FillScreen(BLACK);
	//}
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