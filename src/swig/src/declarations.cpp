#include "declarations.h"

Caller* caller = new Caller();

void moveServos() {
    if (caller) {
        caller->moveServos();
    }
}

void toAngle(float x, float y) {
    if (caller) {
        caller->toAngle(x, y);
    }
}
