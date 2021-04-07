
#pragma once

class location{
public:
    location(bool left, bool right, bool above, bool below, char name, int cost) : left(left),
                                                                                                 right(right),
                                                                                                 above(above),
                                                                                                 below(below),
                                                                                                 name(name), cost(cost){}

    location(location* & copy){
        this->left = copy->left;
        this->right = copy->right;
        this->above = copy->above;
        this->below = copy->below;
        this->name = copy->name;
        this->cost = copy->cost;

    }



private:
    bool left, right, above, below;
    char name;
    int cost;

};
