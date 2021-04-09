
#pragma once

class location{
public:
    location(bool left = false, bool right = false, bool above = false, bool below = false, char name = ' ',
             int cost = 0, bool start = 0
            , bool goal = 0, int x = 0, int y = 0, int prevX = 0, int prevY = 0,
             bool visited = false) : left(left), right(right), above(above), below(below), start(start),
                                                  goal(goal), x(x), y(y), prevX(prevX), prevY(prevY), visited(visited),
                                                  name(name), cost(cost) {}

    location(location* & copy){
        this->left = copy->left;
        this->right = copy->right;
        this->above = copy->above;
        this->below = copy->below;
        this->name = copy->name;
        this->cost = copy->cost;
        this->visited = copy->visited;
        this->x = copy->x;
        this->y = copy->y;
        this->prevX = copy->prevX;
        this->prevY = copy->prevY;
        this->start = copy->start;
        this->goal = copy->goal;
    }

    void setVisited(bool visit = false)
    {
        visited = visit;
        this->name = '.';
    }

    bool isVisited()
    {
        return visited;
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

    bool Visited() const {
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

    bool isStart() const {
        return start;
    }

    void setStart(bool start) {
        location::start = start;
    }

    bool isGoal() const {
        return goal;
    }

    void setGoal(bool goal) {
        location::goal = goal;
    }


private:
    bool left, right, above, below, start, goal;
    int x,y;
    int prevX,prevY;
    bool visited;
    char name;
    int cost;

};
