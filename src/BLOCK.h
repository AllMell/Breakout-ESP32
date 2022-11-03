#pragma once

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