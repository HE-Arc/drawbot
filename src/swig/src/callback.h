#pragma once

#include <iostream>

class Callback {
public:
    virtual ~Callback() { std::cout << "Callback::Callback" << std::endl; }
    virtual void moveServos() { std::cout << "Callback::moveServos()" << std::endl; }
    virtual void toAngle(float x, float y) { std::cout << "Callback::toAngle(" << x << "," << y << ")" << std::endl; }
};
