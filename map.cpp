#pragma once
#include <vector>
#include "location.cpp"
using namespace std;

class map{
public:
    map(const vector<vector<location*>> &maze = {}, int width = 0, int height = 0) : maze(maze), width(width),
                                                                          height(height) {}

    const vector<vector<location *>> &getMaze() const {
        return maze;
    }

    void setMaze(const vector<vector<location *>> &maze) {
        map::maze = maze;
    }

    void insert(const location* & p)
    {
        maze.push_back(p);
    }

    int getWidth() const {
        return width;
    }

    void setWidth(int width) {
        map::width = width;
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        map::height = height;
    }

private:
    vector<vector<location*>> maze;
    int width, height;
};

