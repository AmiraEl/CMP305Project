#pragma once

#include <vector>
#include <stack>
#include <iostream>
#include "location.cpp"

using namespace std;

class map {
public:
    map(const vector<vector<location *>> &maze = {}, int width = 0, int height = 0) : maze(maze), width(width),
                                                                                      height(height) {}

    map (map & cpy){
        
        for(int i=0;i<cpy.maze.size();++i)
        {
            for(int j=0;j<cpy.maze[i].size();++i)
            {
                this->maze[i][j] = cpy.maze[i][j];
            }
        }
        this->width = cpy.width;
        this->height = cpy.height;
    }
    const vector<vector<location *>> &getMaze() const {
        return maze;
    }

    void setMaze(const vector<vector<location *>> &maze) {
        map::maze = maze;
    }

    void push_row(vector<location *> &p) {
        maze.push_back(p);
        height ++;
        width = p.size();
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

    void Success(location *& p) {
        p = this->maze[p->getPrevX()][p->getPrevY()];
        while(!p->isStart()){
            p->setName('o');
            p = this->maze[p->getPrevX()][p->getPrevY()];
        }
    }

    void Failure() {
        cout << "Path doesn't Exist!\n";
    }


    void DFS() {
        int curr_x, curr_y;
        stack<location *> process;

        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                if (maze[i][j]->isStart()) {
                    maze[i][j]->setVisited(true);
                    process.push(maze[i][j]);
                    curr_x = i;
                    curr_y = j;
                }
            }
        }

        while (!process.empty()) {
            location *curr = process.top();
            curr_x = curr->getX();
            curr_y = curr->getY();
            process.pop();

            if (curr->isGoal()) {

                return this->Success(curr);
            }

            if (curr->isRight() && !(maze[curr_x][curr_y + 1]->Visited())) {

                maze[curr_x][curr_y + 1]->setVisited(true);
                maze[curr_x][curr_y + 1]->Parent(curr_x, curr_y);
                process.push(maze[curr_x][curr_y + 1]);

            }

            if (curr->isLeft()  && !(maze[curr_x][curr_y - 1]->Visited())) {

                maze[curr_x][curr_y - 1]->setVisited(true);
                maze[curr_x][curr_y - 1]->Parent(curr_x, curr_y);
                process.push(maze[curr_x][curr_y - 1]);


            }

            if (curr->isAbove() && !(maze[curr_x - 1][curr_y]->Visited())) {

                maze[curr_x - 1][curr_y]->setVisited(true);
                maze[curr_x - 1][curr_y]->Parent(curr_x, curr_y);
                process.push(maze[curr_x - 1][curr_y]);


            }

            if (curr->isBelow() && !(maze[curr_x + 1][curr_y]->Visited())) {

                maze[curr_x + 1][curr_y ]->setVisited(true);
                maze[curr_x + 1][curr_y ]->Parent(curr_x, curr_y);
                process.push(maze[curr_x + 1][curr_y ]);


            }

        }
        return Failure();


    }


    ~map() {
        for (int i = 0; i < maze.size(); i++) {
            for (int j = 0; j < maze[i].size(); j++) {
                delete maze[i][j];

            }
        }
    }

private:
    vector<vector<location *>> maze;
    int width, height;
};

