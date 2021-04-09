#include <iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cctype>
#include "map.cpp"

using namespace std;

pair<char, int> inputError(char x, int line){
    return pair<char, int> (x, line);
}

//reads map and loads it into an appropriate data structure
void readFile(map & grid){
    ifstream in("C:\\Users\\amira\\CLionProjects\\CMP305Project\\map.txt");
    if (in.fail()){
        cout << "Error: Couldn't open map.txt!\n";
    }else {
        vector<location*> rows;
        char str1[100], str2[100], str3[100];
        in.getline(str1, 100);
        in.getline(str2, 100);
        in.getline(str3, 100);
        int line = 1, cell = 1;

        while (!in.eof()) {
            int i = 0, j = 0, k = 1, cost = -1, cell = 0, row = 0, col = 0;
            char name = ' ';
            bool above, below, right, left;
            //cout << "line " << line << endl;

            if (line != 1){
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

                location *temp  = new location (left, right, above, below, name, cost);
                rows.push_back(temp);

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
        }
    }
}

void displayMap(const map & grid) {
    if(grid.getWidth() == 0 or grid.getHeight() == 0) throw grid.getWidth();
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
            if(!grid.getMaze()[i][j]->isBelow()){
                cout << "+---";
            }else{
                cout << "+   ";
            }
        }
        cout << "+\n";


    }

}

pair<int, int> findLocation(map grid, char n) {
    for (int i = 0; i < grid.getMaze().size(); i++){
        for (int j = 0; j < grid.getMaze()[i].size(); j++){
            if (grid.getMaze()[i][j]->getName() == n){
                return pair<int, int> (i, j);
            }
        }
    }
    return pair<int, int> (-1, -1);
}


void menu (map & grid){
    while(true) {
        location* start;
        location* end;
        cout << "Please choose an option:\n"
                "1) Load map\n"
                "2) Display map\n"
                "3) Set start\n"  //done
                "4) Set goal\n"  //done
                "5) Find path using DFS\n"
                "6) Find path using BFS\n"
                "7) Find path using DA\n"
                "8) Display path\n"
                "9) Quit\n";
        int input;

        cin >> input;
        switch (input) {
            case 1:
                try {
                    readFile(grid);
                   // grid.setHeight (grid.getMaze().size());
                   // grid.setWidth (grid.getMaze()[0].size());
                } catch (pair<char, int> x) {
                    cout << "Error: input " << x.first << " from line " << x.second << " in map file is invalid/n";
                }catch(...){
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
                char in;
                try {
                    char in;
                    cout << "Enter a starting point: ";
                    cin >> in;
                    //pair<int, int> index = findLocation(grid, in);
                   // if (index.first != -1)
                    //grid.getMaze()[index.first][index.second]->setStart(true);
                    //else throw (index.first);
                    grid.getMaze()[0][0]->setStart(true);

                }catch(...){
                    cout << "Error: " << in << " is not a valid point on the map!\n" ;
                }
                break;
            case 4:
                try {
                    char in;
                    cout << "Enter an ending point: ";
                    cin >> in;
                    //pair<int, int> index = findLocation(grid, in);
                    //if (index.first != -1)
                    //    grid.getMaze()[index.first][index.second]->setGoal(true);
                   // else throw (index.first);

                }catch(...){
                    cout << "Error: " << in << " is not a valid point on the map!\n" ;
                }

                break;

            case 5:
                grid.DFS();

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:

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


int main(){
    map grid;
        menu(grid);
}

