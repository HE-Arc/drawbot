#pragma once
#include "callback.h"

class Caller {
    private:
        Callback* _callback;
    public:
        Caller(): _callback(0) {}
        ~Caller() { delCallback(); }
        void delCallback() { delete _callback; _callback = 0; }
        void setCallback(Callback* cb) { delCallback(); _callback = cb; }
        void moveServos() { if(_callback) { _callback->moveServos(); } }
        void toAngle(float x, float y) { if(_callback) { _callback->toAngle(x, y); } }
};
