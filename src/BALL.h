#pragma once

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