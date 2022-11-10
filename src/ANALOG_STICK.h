#pragma once

class ANALOG_STICK {
    public:
        ANALOG_STICK(){
            _pin_x = PIN_RES_LEFT_X; 
            _pin_y = PIN_RES_LEFT_Y; 
            _min = RES_MAP_MIN; 
            _max = RES_MAP_MAX;
            _center_zone = RES_CENTRE_ZONE/2;
        }
        ANALOG_STICK(uint8_t pin_x, uint8_t pin_y, int16_t min, int16_t max, int16_t center_zone){
            _pin_x = pin_x; 
            _pin_y = pin_y; 
            _min = min; 
            _max = max;
            _center_zone = center_zone/2;
        }
        void Set (uint8_t pin_x, uint8_t pin_y, int16_t min, int16_t max, int16_t center_zone){ 
            _pin_x = pin_x; 
            _pin_y = pin_y; 
            _min = min; 
            _max = max;
            _center_zone = center_zone/2;
        }
        void Calibrate (){
            _refresh_x(); 
            _refresh_y(); 
            _center_x = _value_x; 
            _center_y = _value_y;
        }
        void Map_set (int16_t min, int16_t max){ _min = min; max = max;}
        int16_t Get_value_x (){_refresh_x(); return _value_x;}
        int16_t Get_value_y (){_refresh_y(); return _value_y;}
        int8_t Get_dir_x (){
            _refresh_x();
            if (_value_x < _center_x - _center_zone){return -1;}
            if (_value_x > _center_x + _center_zone){return 1;}
            return 0;
        }
        int8_t Get_dir_y (){
            _refresh_y();
            if (_value_y < _center_y - _center_zone){return -1;}
            if (_value_y > _center_y + _center_zone){return 1;}
            return 0;
        }
    private:
        void _refresh_x (){
            _value_x = map(analogRead(_pin_x), 0, 4095, _min, _max); 
        }
        void _refresh_y (){
            _value_y = map(analogRead(_pin_y), 0, 4095, _min, _max);
        }
        uint8_t _pin_x;
        uint8_t _pin_y;
        int16_t _min;
        int16_t _max;
        int16_t _value_x;
        int16_t _value_y;
        int16_t _center_x = (_max + _min)/2;
        int16_t _center_y = (_max + _min)/2;
        int16_t _center_zone;
};