#pragma once

class location{
public:
    location(location *left, location *right, location *above, location *below, char name, int cost = 0) : left(left),
    right(right), above(above),
    below(below), name(name), cost(cost){}

    location(location* & copy){
        this->left = copy->left;
        this->right = copy->right;
        this->above = copy->above;
        this->below = copy->below;
        this->name = copy->name;
        this->cost = copy->cost;

    }

private:
    location *left, *right, *above, *below;
    char name;
    int cost;

};
