#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main() {

    string input;

    ifstream File("input2.txt");

    vector<long> things;

    while(getline(File, input)) {
        size_t d = input.find("-");
        string a = input.substr(0, d);
        string b = input.substr(d+1);

        auto begin = stol(a);
        auto end = stol(b);

        for (long i = begin; i <= end; i++) {
            string x = to_string(i);

            int length = x.length();

            // Even
            if (length%2 == 0) {
                int half = length/2;

                string first = x.substr(0, half);
                string second = x.substr(half);

                // Halves equal
                if (first == second) {
                    cout << "Found " << x << endl;
                    things.push_back(stol(x));
                    continue;
                }

                // Check multiples of 3
                if (length%3 == 0) {

                    int step = length / 3;

                    string one = x.substr(0, step);
                    string two = x.substr(step, step);
                    string three = x.substr(2*step);

                    if (one == two && two == three) {
                        cout << "Found " << x << endl;
                        things.push_back(stol(x));
                    }

                // Check multiples of 5
                } else if (length%5 == 0) {

                    int step = length / 5;

                    string one = x.substr(0, step);
                    string two = x.substr(step, step);
                    string three = x.substr(2*step, step);
                    string four = x.substr(3*step, step);
                    string five = x.substr(4*step);

                    if (one == two && two == three && three == four && four == five) {
                        cout << "Found " << x << endl;
                        things.push_back(stol(x));
                    }
                }
            
            // Odd
            } else {

                // Check repeats of single digit
                bool found = true;
                for (int j = 0; j < length-1 ; j ++) {
                    if (x[j] != x[j+1]) {
                        found = false;
                        break;
                    }
                }
                if (length < 2)
                    found = false;

                if (found) {
                    cout << "Found " << x << endl;
                    things.push_back(stol(x));
                    continue;
                }

                // Check multiples of 3 and 5
                if (length%3 == 0) {

                    int step = length / 3;

                    string one = x.substr(0, step);
                    string two = x.substr(step, step);
                    string three = x.substr(2*step);

                    if (one == two && two == three) {
                        cout << "Found " << x << endl;
                        things.push_back(stol(x));
                    }

                } else if (length%5 == 0) {

                    int step = length / 5;

                    string one = x.substr(0, step);
                    string two = x.substr(step, step);
                    string three = x.substr(2*step, step);
                    string four = x.substr(3*step, step);
                    string five = x.substr(4*step);

                    if (one == two && two == three && three == four && four == five) {
                        cout << "Found " << x << endl;
                        things.push_back(stol(x));
                    }

                }

            }
        }
    }

    long answer = 0;
    for (auto thing : things) {
        answer += thing;
    }
    cout << answer << endl;

    return 0;
}