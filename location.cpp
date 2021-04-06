#pragma once

class location{
public:
    location(bool left = false, bool right = false, bool above = false,
             bool bottom = false, char name = ' ', int x = 0, int y = 0) :
             left(left), right(right), above(above), bottom(bottom), name(name), x(x), y(y) {

    }

private:
    bool left, right, above, bottom;
    char name;
    int x, y;

};
