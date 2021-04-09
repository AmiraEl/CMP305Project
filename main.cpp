#include <iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cctype>
#include "map.cpp"

using namespace std;

int inputError(char x, int line) {
    cout << "Error: input " << x << " from line " << line << " in map file is invalid/n";
    return -1;
}

//reads map and loads it into an appropriate data structure
void readFile(map &grid) {
    ifstream in("C:\\Users\\amira\\CLionProjects\\CMP305Project\\map.txt");
    if (in.fail()) {
        cout << "Error: Couldn't open map.txt!\n";
    } else {
        vector<location *> rows;
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

                location *temp = new location(left, right, above, below, name, cost);
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

void displayMap(const map &grid) {
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
                    temp = grid;
                    // grid.setHeight (grid.getMaze().size());
                    // grid.setWidth (grid.getMaze()[0].size());

                } catch (int x) {

                } catch (...) {
                    cout << "Error: Cannot load Map!/n";
                }

                break;
            case 2:
                try {
                    displayMap(temp);
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

                break;
            case 7:

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

