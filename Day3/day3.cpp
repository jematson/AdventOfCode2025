#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {

    string input;

    ifstream File("input3.txt");

    long sum = 0;

    while(getline(File, input)) {

        string best = "";
        int index = 0;

        for(int i=11; i >= 0; i--) {

            string digit = "0";

            for(int j=index; j<(input.length()-i); j++) {
                if(stoi(input.substr(j, 1)) > stoi(digit)) {
                    digit = input.substr(j, 1);
                    index = j+1;
                }
            }

            best += digit;
        }

        sum += stol(best);
    }

    cout << "Answer: " << sum << endl;

    return 0;
}