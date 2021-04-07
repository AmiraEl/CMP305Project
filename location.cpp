
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

    void setVisited(bool visit = false)
    {
        visited = visit;
    }

    bool isLeft() const {
        return left;
    }

    void setLeft(bool left) {
        location::left = left;
    }

    bool isRight() const {
        return right;
    }

    void setRight(bool right) {
        location::right = right;
    }

    bool isAbove() const {
        return above;
    }

    void setAbove(bool above) {
        location::above = above;
    }

    bool isBelow() const {
        return below;
    }

    void setBelow(bool below) {
        location::below = below;
    }

    int getPrevX() const {
        return prevX;
    }

    void setPrevX(int prevX) {
        location::prevX = prevX;
    }

    int getPrevY() const {
        return prevY;
    }

    void setPrevY(int prevY) {
        location::prevY = prevY;
    }

    bool isVisited() const {
        return visited;
    }

    char getName() const {
        return name;
    }

    void setName(char name) {
        location::name = name;
    }

    int getCost() const {
        return cost;
    }

    void setCost(int cost) {
        location::cost = cost;
    }


private:
    bool left, right, above, below;
    int prevX,prevY;
    bool visited;
    char name;
    int cost;

};
