#include <iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cctype>
using namespace std;

void readFile(){
    ifstream in("map.txt");
    if (in.fail()){
        cout << "Couldn't open map.txt!\n";
    }
    char str1[100], str2[100], str3[100];
    in.getline(str1, 100);
    in.getline(str2, 100);
    in.getline(str3, 100);
    int line = 1, cell = 1;

    while (!in.eof()) {
        int i = 0, j = 0, k = 1,cost=-1,cell =0;
        char name=' ';
        bool above, below, right, left;
        cout << "line " << line << endl;

        while (i < strlen(str1) - 1) {
            above = below = right = left = true;
            name =' ';
            if (str1[i] == '+') i++; // new path
            if (str1[i] == '-') above = false;
            else if (str1[i] == ' ') above = true;
            // else error
            i = i + 3; // path left
            if (str2[j] == '|') left = false;
            else if (str2[j] == ' ') left = true;
            // else error
            j = j + 2; // cost
            if (str2[j]!=' ')
                if (isdigit(str2[j])) cost= (str2[j] - '0');
                else { cost = 0; name = str2[j]; }
            else cost = 0;
            j = j +2; //path right
            if (str2[j] == '|') right = false;
            else if (str2[j] == ' ') right = true;
            // else error
            //path below
            if (str3[k] == ' ') below = true;
            else if (str3[k] == '-') below = false;
            // else error
            k = k + 4; // wall below
            cout << "cell = " << cell++ << endl;
            cout << "above: " << above << "\t";
            cout << "below: " << below << endl;
            cout << "right: " << right << "\t";
            cout << "left: "  << left << endl;
            cout << "cost: "  << cost << endl;
            cout<<"name: "<<name<<endl;
            cout << endl << endl;
        }

        strcpy(str1, str3);
        cout << str1 << endl;
        in.getline(str2, 100);
        in.getline(str3, 100);
        cout << str2 << endl;
        cout << str3 << endl;
        line++;
    }
}

void menu (){
    cout << "Please choose an option:\n"
            "1) Load map\n"
            "2) Display map\n"
            "3) Set start\n"
            "4) Set goal\n"
            "5) Find path using DFS\n"
            "6) Find path using BFS\n"
            "7) Find path using DA\n"
            "8) Display path"
            "9) Quit";
    int input;
    cin >> input;

    switch (input){
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        default:
            cout << "Invalid Choice!";
            break;

    }
}

int main() {


}

