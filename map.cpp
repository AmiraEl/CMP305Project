#pragma once

#include <vector>
#include <stack>
#include<queue>
#include <iostream>
#include "location.cpp"

using namespace std;

class map {
public:
    map(const vector<vector<location *>> &maze = {}, int width = 0, int height = 0) : maze(maze), width(width),
                                                                                      height(height) {}
    /*
    map operator=(map & cpy)
    {
        
        for(int i=0;i<cpy.maze.size();++i)
        {
            for(int j=0;j<cpy.maze[i].size();++j)
            {
                this->maze[i][j]->setLeft(cpy.maze[i][j]->isLeft()); 
                this->maze[i][j]->setAbove(cpy.maze[i][j]->isAbove());
                this->maze[i][j]->setRight(cpy.maze[i][j]->isRight());
                this->maze[i][j]->setBelow(cpy.maze[i][j]->isBelow());
                this->maze[i][j]->setX(cpy.maze[i][j]->getX());
                this->maze[i][j]->setY(cpy.maze[i][j]->getY());
                this->maze[i][j]->setPrevX(cpy.maze[i][j]->getPrevX());
                this->maze[i][j]->setPrevY(cpy.maze[i][j]->getPrevY());
                this->maze[i][j]->setName(cpy.maze[i][j]->getName());
                this->maze[i][j]->setCost(cpy.maze[i][j]->getCost());
            }
        }
        this->width = cpy.width;
        this->height = cpy.height;
        return *this;
    }
    */
    vector<vector<location *>> &getMaze()  {
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
        stack<location*> correctOrder;
        while(!p->isStart()){
            p->setName('o');
            p = this->maze[p->getPrevX()][p->getPrevY()];
            correctOrder.push(p);
        }


    }


    void SuccessDA(location *& p) {
        p = this->maze[p->getPrevX()][p->getPrevY()];
        while(!p->isStart()){
            if(p->getName() == '.')
                // This to convert the cost to a char in order to print the costs
                p->setName(std::to_string(p->getCost())[0]); 
            p = this->maze[p->getPrevX()][p->getPrevY()];
        }
    }


    void Failure() {
        cout << "Path doesn't Exist!\n";
    }

    struct Compare   // This for overloading the compare condition for priority queues
    {
        bool operator()(const location* lhs,const location* rhs)
        {
            return lhs->getCost() > rhs->getCost();
        }
    };


    void DFS() {
        int curr_x, curr_y;
        stack<location *> process;

        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                maze[i][j]->setVisited(false);
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

    

    void BFS() {
        int curr_x, curr_y;
        queue<location *> process;

        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                maze[i][j]->setVisited(false);
                if (maze[i][j]->isStart()) {
                    maze[i][j]->setVisited(true);
                    process.push(maze[i][j]);
                    curr_x = i;
                    curr_y = j;
                }
            }
        }

        while (!process.empty()) {
            location *curr = process.front();
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


    void DA() {
        int curr_x, curr_y;
        priority_queue<location *,deque<location*>,Compare> process;

        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                maze[i][j]->setVisited(false);
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

                return this->SuccessDA(curr);
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

