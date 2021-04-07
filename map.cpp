#pragma once
#include <vector>
#include <stack>
#include <iostream>
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

    void Success(location*& p )
    {

    }

    void Failure()
    {
        cout<<"Path doesn't Exist!";
    }
    

    void DFS(char startpoint,char endpoint)
    {
        bool check = false;
        int curr_x,curr_y;
        stack<location*> process;
        if(startpoint == ' ' || endpoint == ' ')
        {
            cout<<"Points Are Invalid!";
            return;
        }
        for(int i=0;i<maze.size();++i)
        {
            for(int j=0;j<maze[i].size();++j)
            {
                maze[i][j]->setVisited(false);
                if(maze[i][j]->getName() == startpoint)
                {
                    maze[i][j]->setVisited(true);
                    process.push(maze[i][j]);
                    curr_x = i;
                    curr_y = j;
                    check = true;
                }
            }
        }
            if(!check)
            {
                cout<<"The Start Point is Not On The Map";
                return;
            }
                                
            
            while(!process.empty())
            {
                location* curr = process.top();
                curr_x = curr->getX();
                curr_y = curr->getY();
                process.pop();

                if(curr->getName() == endpoint)
                {
                    return Success(curr);
                }

                if(curr->isRight() == true && !(maze[curr_x][curr_y+1]->Visited()))
                {
                   
                        maze[curr_x][curr_y+1]->setVisited(true);
                        maze[curr_x][curr_y+1]->Parent(curr_x,curr_y);
                        process.push(maze[curr_x][curr_y+1]);
                    
                }

                if(curr->isLeft() == true && !(maze[curr_x][curr_y-1]->Visited()))
                {
                    
                        maze[curr_x][curr_y-1]->setVisited(true);
                        maze[curr_x][curr_y-1]->Parent(curr_x,curr_y);
                        process.push(maze[curr_x][curr_y-1]);

                    
                }

                if(curr->isAbove() == true && !(maze[curr_x-1][curr_y-1]->Visited()))
                {
                    
                        maze[curr_x-1][curr_y-1]->setVisited(true);
                        maze[curr_x-1][curr_y-1]->Parent(curr_x,curr_y);
                        process.push(maze[curr_x-1][curr_y-1]);

                    
                }

                if(curr->isBelow() == true && !(maze[curr_x+1][curr_y]->Visited()))
                {
                    
                        maze[curr_x+1][curr_y+1]->setVisited(true);
                        maze[curr_x+1][curr_y+1]->Parent(curr_x,curr_y);
                        process.push(maze[curr_x+1][curr_y+1]);

                    
                }

            }
            return Failure();


        
    }


    ~map() {
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

