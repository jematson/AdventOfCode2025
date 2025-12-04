#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void part1() {
    string input;

    map<vector<int>, int> houses = { {{0,0} , 1} };

    ifstream File("input.txt");

    auto x = 0;
    auto y = 0;
    while(getline(File, input)) {

        for (char c : input) {

            // North
            if (c == '^') {
                y++;
                houses.insert_or_assign({x, y}, 1);

            // East
            } else if (c == '>') {
                x++;
                houses.insert_or_assign({x, y}, 1);

            // South
            } else if (c == 'v') {
                y--;
                houses.insert_or_assign({x, y}, 1);

            // West
            } else if (c == '<') {
                x--;
                houses.insert_or_assign({x, y}, 1);

            }
        }
    }

    cout << "Part 1 Answer: " << houses.size() << endl;
}

void part2() {
    string input;

    map<vector<int>, int> houses = { {{0,0} , 1} };

    ifstream File("input.txt");

    // Santa coords
    auto xS = 0;
    auto yS = 0;

    // Robo-Santa coords
    auto xR = 0;
    auto yR = 0;

    while(getline(File, input)) {
        bool santa = true;

        for (char c : input) {

            if (santa) {
                // North
                if (c == '^') {
                    yS++;
                    houses.insert_or_assign({xS, yS}, 1);
                // East
                } else if (c == '>') {
                    xS++;
                    houses.insert_or_assign({xS, yS}, 1);
                // South
                } else if (c == 'v') {
                    yS--;
                    houses.insert_or_assign({xS, yS}, 1);
                // West
                } else if (c == '<') {
                    xS--;
                    houses.insert_or_assign({xS, yS}, 1);
                }
            } else {
                // North
                if (c == '^') {
                    yR++;
                    houses.insert_or_assign({xR, yR}, 1);
                // East
                } else if (c == '>') {
                    xR++;
                    houses.insert_or_assign({xR, yR}, 1);
                // South
                } else if (c == 'v') {
                    yR--;
                    houses.insert_or_assign({xR, yR}, 1);
                // West
                } else if (c == '<') {
                    xR--;
                    houses.insert_or_assign({xR, yR}, 1);
                }
            }

            santa = !santa;
        }
    }

    cout << "Part 2 Answer: " << houses.size() << endl;
}


int main() {
    part1();
    part2();

    return 0;
}