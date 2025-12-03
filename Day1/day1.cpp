#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<int> rotate(char dir, int step, int curr_index) {
    int zero_count = 0;

    if (dir == 'R') {

        curr_index += step;

        if (curr_index > 99) {

            while(curr_index > 99) {
                curr_index -= 100;
                zero_count++;
            }
            return {curr_index, zero_count};

        } else {
            if (curr_index == 0 )
                zero_count++;
            return {curr_index, zero_count};
        }

    } else if (dir == 'L') {

        curr_index -= step;

        if (curr_index < 0) {

            while(curr_index < 0) {
                curr_index += 100;
                zero_count++;
            }
            return {curr_index, zero_count};

        } else {
            if (curr_index == 0 )
                zero_count++;
            return {curr_index, zero_count};
        }
    } else {
        return {curr_index, zero_count};
    }
}

int main() {

    int curr_index = 50;
    int answer = 0;

    string input;

    ifstream MyReadFile("input_1.txt");

    while(getline(MyReadFile, input)) {
        char dir = input[0];
        int step = stoi(input.substr(1));

        int new_index = curr_index;

        for (int i = 0; i < step ; i++) {
            if (dir == 'R') {
                new_index++;

                if (new_index == 100) {
                    new_index = 0;
                    answer++;
                }

            } else if (dir == 'L') {
                new_index--;

                if (new_index == 0)
                    answer++;

                if (new_index == -1) {
                    new_index = 99;
                }
            }
        }

        // For part one

        // vector<int> newv = rotate(dir, step, curr_index);
        // int new_index = newv[0];

        // cout << dir << " from " << curr_index << " to " << new_index << endl;

        // answer += newv[1];

        curr_index = new_index;
        
    }

    cout << answer << endl;

    MyReadFile.close();

    return 0;
}