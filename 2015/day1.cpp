#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void part1() {
    string input;

    ifstream File("input.txt");

    int floor = 0;

    while(getline(File, input)) {

        for (char c : input) {

            if (c == '(') {
                floor++;
            } else if (c == ')') {
                floor--;
            }
        }
    }

    cout << "Part 1 Answer: " << floor << endl;
}

void part2() {
    string input;

    ifstream File("input.txt");

    int floor = 0;

    while(getline(File, input)) {

        for (auto i=0; i < input.length(); i++) {
            
            if (input[i] == '(') {
                floor++;
            } else if (input[i] == ')') {
                floor--;
            }

            if (floor == -1) {
                cout << "Part 2 Answer: " << i+1 << endl;
                break;
            }
        }
    }
}


int main() {
    part1();
    part2();

    return 0;
}