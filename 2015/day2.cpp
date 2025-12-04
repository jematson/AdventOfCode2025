#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void part1() {
    string input;

    ifstream File("input.txt");

    auto total = 0;

    while(getline(File, input)) {

        // Split up input into ints
        int l, w, h;
        bool first = true;
        string curr = "";
        for (char c : input) {
            if (c == 'x') {
                if (first) {
                    l = stoi(curr);
                    curr = "";
                    first = false;
                } else {
                    w = stoi(curr);
                    curr = "";
                }
            } else {
                curr += c;
            }
        }
        h = stoi(curr);

        // Calculate square feet
        auto wrap1 = (2*l*w) + (2*w*h) + (2*h*l);

        auto wrap2 = (l >= w && l >= h) ? (w*h) :
                     (w >= l && w >= h) ? (l*h) :
                     (l*w);

        total += (wrap1 + wrap2);

    }

    cout << "Part 1 Answer: " << total << endl;
}

void part2() {
    string input;

    ifstream File("input.txt");

    auto total = 0;

    while(getline(File, input)) {

        // Split up input into ints
        int l, w, h;
        bool first = true;
        string curr = "";
        for (char c : input) {
            if (c == 'x') {
                if (first) {
                    l = stoi(curr);
                    curr = "";
                    first = false;
                } else {
                    w = stoi(curr);
                    curr = "";
                }
            } else {
                curr += c;
            }
        }
        h = stoi(curr);

        // Calculate square feet
        auto wrap1 = l*w*h;

        auto wrap2 = (l >= w && l >= h) ? (2*w + 2*h) :
                     (w >= l && w >= h) ? (2*l + 2*h) :
                     (2*l + 2*w);

        total += (wrap1 + wrap2);

    }

    cout << "Part 2 Answer: " << total << endl;
}


int main() {
    part1();
    part2();

    return 0;
}