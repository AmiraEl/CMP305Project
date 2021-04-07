#pragma once
#include <vector>
#include<stack>
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

    void push_row(vector<location*> & p)
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

    

    void DFS(location* & startCell,char endpoint)
    {
        for(int i=0;i<maze.size();++i)
        {
            for(int j=0;j<maze[i].size();++j)
            {
                maze[i][j]->setVisited(false);
            }

            startCell->setVisited(true);
            stack<location*> process;
            process.push(startCell);
            while(!process.empty())
            {
                location* curr = process.top();
                process.pop();
                if()
            }


        }
    }


    virtual ~map() {
        for (int i = 0; i < maze.size(); i++){
            for (int j = 0; j < maze[i].size(); j++){
                delete maze[i][j];

            }
        }
    }

private:
    vector<vector<location*>> maze;
    int width, height;
};

