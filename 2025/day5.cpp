#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

void part1() {

    string input;
    ifstream File("input.txt");

    bool check = false;

    vector<vector<long>> ranges;
    vector<long> ids;

    while(getline(File, input)) {

        if (input == "") {
            check = true;
        // Read ranges
        } else if (!check) {
            long d = input.find("-");
            string a = input.substr(0, d);
            string b = input.substr(d+1);
            ranges.push_back( { stol(a), stol(b) }  );

        // Read ids
        } else {
            ids.push_back(stol(input));
        }
    }

    auto total = 0;

    for (auto id : ids) {
        for (auto range : ranges) {
            if (id >= range[0] && id <= range[1]) {
                total++;
                break;
            }
        }
    }

    cout << "Part 1 Answer: " << total << endl;

    File.close();

}

bool tupleCompare(const tuple<long, char>& a, const tuple<long, char>& b) {
    return get<long>(a) < get<long>(b);
}

void part2() {

    string input;
    ifstream File("input.txt");

    vector<tuple<long, char>> nums;

    while(getline(File, input)) {

        long d = input.find("-");

        string a = input.substr(0, d);
        string b = input.substr(d+1);
        
        // Mark numbers as a range start or end
        nums.push_back( make_tuple(stol(a), 's') );
        nums.push_back( make_tuple(stol(b), 'e') );
    }

    // Sort the range markers
    sort(nums.begin(), nums.end(), tupleCompare);

    auto numStarts = 0;
    auto numEnds = 0;
    long start = -1;
    long total = 0;

    auto num_s = 0;
    auto num_e = 0;

    for(int i = 0; i < nums.size(); i++) {
        auto num = nums[i];

        // Reset range start
        if (start == -1) 
            start = get<long>(num);

        if (get<char>(num) == 's') {
            numStarts++;
            num_s++;
        }
        else if (get<char>(num) == 'e') {
            numEnds++;
            num_e++;
        }

        if (i < nums.size()-1) {
            if (numStarts > 0 &&
                numStarts == numEnds &&
                get<long>(num) != get<long>(nums[i+1])) {
    
                numStarts = 0;
                numEnds = 0;
                total += ((get<long>(num) - start) + 1);
                start = -1;
            }
        } else {
            total += ((get<long>(num) - start) + 1);
        }
    }

    cout << "Part 2 Answer: " << total << endl;

    File.close();
}

int main() {

    part1();
    part2();

    return 0;
}