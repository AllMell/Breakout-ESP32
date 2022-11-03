#pragma once

class DIGITAL_BATTON{
    public:
        void Set (uint8_t pin){
            _pin = pin;
        }
        bool Get_state(){
            _refresh();
            return _state;
        }
    private:
        void _refresh(){
            _state = digitalRead(_pin);
        }
        bool _state;
        uint8_t _pin;
};