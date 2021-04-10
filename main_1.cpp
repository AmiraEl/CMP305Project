#include <iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

class location{
public:
    location(bool left = false, bool right = false, bool above = false, bool below = false, char name = ' ',
             int cost = 0, int x = 0, int y = 0, bool start = false
            , bool goal = 0, int prevX = 0, int prevY = 0,
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
        if(visited)
            if(this->getName() == ' ') this->setName('.');
        if(!visited)
            if(this->getName() == '.' || this->getName()== 'o') this->setName(' ');



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

    void Parent(int x, int y)
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

    void setX(int X)
    {
       this->x = X ;
    }

    void setY(int Y)
    {
        this->y = Y;
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
        cout<<"Path:";
        while(!correctOrder.empty())
        {
            cout<<"("<<correctOrder.top()->getX()<<","<<correctOrder.top()->getY()<<") ";
            correctOrder.pop();
        }
        cout<<endl;


    }


    void SuccessDA(location *& p) {
        p = this->maze[p->getPrevX()][p->getPrevY()];
        stack<location*> correctOrder;
        while(!p->isStart()){
            if(p->getName() == '.')
                // This to convert the cost to a char in order to print the costs
                p->setName(std::to_string(p->getCost())[0]); 
            p = this->maze[p->getPrevX()][p->getPrevY()];
            correctOrder.push(p);
        }

        cout<<"Path:";
        while(!correctOrder.empty())
        {
            cout<<"("<<correctOrder.top()->getX()<<","<<correctOrder.top()->getY()<<")  ";
            correctOrder.pop();
        }
        cout<<endl;

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

int inputError(char x, int line) {
    cout << "Error: input " << x << " from line " << line << " in map file is invalid\n";
    return -1;
}

//reads map and loads it into an appropriate data structure
void readFile(map &grid) {
    
    string filename;
    cout<<"\nEnter The Name Of The Map You Want To Open:";
    cin>>filename;
    ifstream in(filename);
    if (in.fail()) {
        cout << "Error: Couldn't open the map!\n";
    } else {
        
        vector<location *> rows;
        char str1[100], str2[100], str3[100];
        in.getline(str1, 100);
        in.getline(str2, 100);
        in.getline(str3, 100);
        int line = 1, cell = 1, x = 0;

        while (!in.eof()) {
            int i = 0, j = 0, k = 1, cost = -1, cell = 0, y = 0;
            char name = ' ';
            bool above, below, right, left;
            //cout << "line " << line << endl;

            if (line != 1) {
                strcpy(str1, str3);
                in.getline(str2, 100);
                in.getline(str3, 100);
            }

            while (i < strlen(str1) - 1) {
                above = below = right = left = true;
                name = ' ';
                if (str1[i] == '+') i++; // new path
                if (str1[i] == '-') above = false;
                else if (str1[i] == ' ') above = true;
                else throw inputError(str1[i], line);
                i = i + 3; // skips over dashes/spaces


                if (str2[j] == '|') left = false;
                else if (str2[j] == ' ') left = true;
                else throw inputError(str2[j], line);
                j = j + 2; // cost
                if (str2[j] != ' ')
                    if (isdigit(str2[j])) cost = (str2[j] - '0');
                    else {
                        cost = 0;
                        name = str2[j];
                    }
                else cost = 0;
                j = j + 2; //path right
                if (str2[j] == '|') right = false;
                else if (str2[j] == ' ') right = true;
                else throw inputError(str2[j], line);
                //path below


                if (str3[k] == ' ') below = true;
                else if (str3[k] == '-') below = false;
                else throw inputError(str3[k], line);
                k = k + 4; // wall below

                location *temp = new location(left, right, above, below, name, cost, x, y);
                rows.push_back(temp);
                y++;
                /*cout << "cell = " << cell++ << endl;
                cout << "above: " << above << "\t";
                cout << "below: " << below << endl;
                cout << "right: " << right << "\t";
                cout << "left: " << left << endl;
                cout << "cost: " << cost << endl;
                cout << "name: " << name << endl;
                cout << endl << endl;*/


            }
            grid.push_row(rows);
            rows.clear();
            /*
            cout << str1 << endl;
            cout << str2 << endl;
            cout << str3 << endl;
*/
            line++;
            x++;
        }
    }
}

void displayMap(map &grid) {
    if (grid.getWidth() == 0 || grid.getHeight() == 0) throw grid.getWidth();
    for (int i = 0; i < grid.getWidth(); i++) {
        cout << "+---";
    }
    cout << "+";

    cout << endl;
    //Middle rows:
    for (int i = 0; i < grid.getHeight(); i++) {
        cout << '|';
        for (int j = 0; j < grid.getWidth(); j++) {

            if (grid.getMaze()[i][j]->isStart() == true) {
                cout << "(" << grid.getMaze()[i][j]->getName() << ")";
            } else if (grid.getMaze()[i][j]->isGoal()) {
                cout << "{" << grid.getMaze()[i][j]->getName() << "}";
            } else {
                cout << " " << grid.getMaze()[i][j]->getName() << " ";
            }

            if (!grid.getMaze()[i][j]->isRight()) {
                cout << '|';
            } else { cout << ' '; }
        }
        cout << endl;


        for (int j = 0; j < grid.getWidth(); j++) {
            if (!grid.getMaze()[i][j]->isBelow()) {
                cout << "+---";
            } else {
                cout << "+   ";
            }
        }
        cout << "+\n";


    }

}

void setStart(map &grid, char n) {
    for (int i = 0; i < grid.getMaze().size(); i++) {
        for (int j = 0; j < grid.getMaze()[i].size(); j++) {
            if (grid.getMaze()[i][j]->getName() == n) {
                grid.getMaze()[i][j]->setStart(true);
                return;
            }

        }
    }
    cout << "Couldn't Find The Position.\n";

}

void setEnd(map &grid, char n) {
    for (int i = 0; i < grid.getMaze().size(); i++) {
        for (int j = 0; j < grid.getMaze()[i].size(); j++) {
            if (grid.getMaze()[i][j]->getName() == n) {
                grid.getMaze()[i][j]->setGoal(true);
                return;
            }

        }
    }
    cout << "Couldn't Find The Position.\n";

}


void menu(map &grid) {
    char in;
    map temp; //map after file is loaded
    while (true) {

        cout << "Please choose an option:\n"
                "1) Load map\n" // Done 
                "2) Display map\n"
                "3) Set start\n"  //Done
                "4) Set goal\n"  //Done
                "5) Find path using DFS\n" // Done
                "6) Find path using BFS\n" //Done
                "7) Find path using DA\n"  // Done
                "8) Display path\n"// Done 
                "9) Quit\n";// Done 
        int input;

        cin >> input;
        switch (input) {
            case 1:
                try {
                    readFile(grid);
                    // temp = grid;
                    // grid.setHeight (grid.getMaze().size());
                    // grid.setWidth (grid.getMaze()[0].size());

                } catch (int x) {

                } catch (...) {
                    cout << "Error: Cannot load Map!/n";
                }

                break;
            case 2:
                try {
                    displayMap(grid);
                } catch (...) {
                    cout << "Error: cannot display map!\n";
                }

                break;
            case 3:
                cout << "Enter a starting point: ";
                cin >> in;
                setStart(grid, in);
                break;

            case 4:
                cout << "Enter a End point: ";
                cin >> in;
                setEnd(grid, in);
                break;

            case 5:

                grid.DFS();
                break;
            case 6:
                grid.BFS();
                break;
            case 7:
                grid.DA();
                break;
            case 8:
                cout << "Displaying path:\n";
                displayMap(grid);
                break;
            case 9:
                cout << "Goodbye!\n";
                exit(0);
            default:
                cout << "Invalid Choice!";
                break;

        }
    }

}


int main() {
    map grid;
    menu(grid);
}


