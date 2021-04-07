
#pragma once

class location{
public:
    location(bool left, bool right, bool above, bool below, int cost , char name = ' ') : left(left),
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

    void setVisited(bool visit = false)
    {
        visited = visit;
    }

    bool Visited()
    {
        return visited;
    }

    bool getleft()
    {
        return left;
    }
    bool getright()
    {
        return right;
    }
    bool getabove()
    {
        return above;
    }
    bool getbelow()
    {
        return below;
    }
    char getname()
    {
        return name;
    }

    void Parent(char x, char y)
    {
        prevX = x;
        prevY = y;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }








private:
    bool left, right, above, below;
    int x,y;
    int prevX,prevY;
    bool visited;
    char name;
    int cost;

};
