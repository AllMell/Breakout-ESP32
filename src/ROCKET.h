#pragma once

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
		void Moove_At(uint8_t x){
			if(x != _x){
				Hide();
				_x = x;
			}
		}
	private:
		uint8_t _x;
		uint8_t _x_old;
		uint8_t _width;
		uint8_t _height;
		uint16_t _color;
};