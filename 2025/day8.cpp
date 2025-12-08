// day8.cpp
// Jenae Matson
// 2025-12-08
// Solution for Advent of Code 2025 Day 8

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// Calculate Euclidian distance between 3 dimensional points
size_t distance(vector<int> a, vector<int> b) {
    size_t x = a[0] - b[0];
    size_t y = a[1] - b[1];
    size_t z = a[2] - b[2];
    return sqrt( (x*x) + (y*y) + (z*z) );
}

struct BoxDistance {
    size_t distance;
    size_t point1;
    size_t point2;

    BoxDistance(size_t d, size_t a, size_t b) : distance(d), point1(a), point2(b) {}
};

bool distanceCompare(const BoxDistance& a, const BoxDistance& b) {
    return a.distance < b.distance;
}

bool circuitCompare(const vector<int>& a, const vector<int>& b) {
    return a.size() > b.size();
}

void part1() {

    string input;
    ifstream File("input8.txt");

    // Each box defined by a vector of ints:
    // x, y, z, circuit number
    vector<vector<int>> boxes;
    size_t index = 0;
    while(getline(File, input)) {
        vector<int> coordinate; 

        string curr = "";
        for (char c : input) {
            if (c == ',') {
                coordinate.push_back(stoi(curr));
                curr = "";
            } else {
                curr.push_back(c);
            }
        }
        coordinate.push_back(stoi(curr));
        coordinate.push_back(index);
        index++;
        boxes.push_back(coordinate);
    }
    
    // Calculate distances between all boxes
    vector<BoxDistance> distances;
    for (int i=0; i<boxes.size(); i++) {
        for (int j=0; j<boxes.size(); j++) {

            // Don't repeat pairs and
            // don't check a boxes distance to itself
            if( i <= j) 
                continue;

            size_t d = distance(boxes[i], boxes[j]);
            BoxDistance b = BoxDistance(d, i, j);
            distances.push_back(b);
        }
    }

    // Sort distances
    sort(distances.begin(), distances.end(), distanceCompare);

    // Make 1000 shortest connections into circuits
    size_t CONNECTIONS = 1000;
    vector<vector<int>> circuits;
    size_t distance_index = 0;

    // Put all boxes in their own individual circuit
    for (int i = 0; i < boxes.size(); i++) {
        circuits.push_back({ i });
        boxes[i][3] = i;
    }

    for(int i = 0; i < CONNECTIONS; i++) {

        BoxDistance b = distances[distance_index];

        size_t circuit1 = boxes[b.point1][3];
        size_t circuit2 = boxes[b.point2][3];

        // If boxes not in same circuit, combine
        if (circuit1 != circuit2) {
            
            // Combine to lower index circuit
            size_t new_circuit = circuit1 < circuit2 ? circuit1 : circuit2;
            size_t old_circuit = circuit1 < circuit2 ? circuit2 : circuit1;

            for (auto box : circuits[old_circuit]) {
                // Assign new circuit number to box
                boxes[box][3] = new_circuit;
                circuits[new_circuit].push_back(box);
            }
            circuits[old_circuit] = {};
        }
        distance_index++;
    }

    // Sort list of circuits by size (number of boxes)
    sort(circuits.begin(), circuits.end(), circuitCompare);

    auto answer = circuits[0].size()*circuits[1].size()*circuits[2].size();

    cout << "Part 1 Answer: " << answer << endl;

}

void part2() {
    string input;
    ifstream File("input8.txt");

    // Each box defined by a vector of ints:
    // x, y, z, circuit number
    vector<vector<int>> boxes;
    size_t index = 0;
    while(getline(File, input)) {
        vector<int> coordinate; 

        string curr = "";
        for (char c : input) {
            if (c == ',') {
                coordinate.push_back(stoi(curr));
                curr = "";
            } else {
                curr.push_back(c);
            }
        }
        coordinate.push_back(stoi(curr));
        coordinate.push_back(index);
        index++;
        boxes.push_back(coordinate);
    }
    
    // Calculate distances between all boxes
    vector<BoxDistance> distances;
    for (int i=0; i<boxes.size(); i++) {
        for (int j=0; j<boxes.size(); j++) {

            // Don't repeat pairs and
            // don't check a boxes distance to itself
            if( i <= j) 
                continue;

            size_t d = distance(boxes[i], boxes[j]);
            BoxDistance b = BoxDistance(d, i, j);
            distances.push_back(b);
        }
    }

    // Sort distances
    sort(distances.begin(), distances.end(), distanceCompare);

    // Make 1000 shortest connections into circuits
    size_t totalBoxes = boxes.size();
    vector<vector<int>> circuits;
    size_t distance_index = 0;
    BoxDistance last_connection(0,0,0);

    // Put all boxes in their own individual circuit
    for (int i = 0; i < boxes.size(); i++) {
        circuits.push_back({ i });
        boxes[i][3] = i;
    }
    
    while(circuits[0].size() < totalBoxes) {

        BoxDistance b = distances[distance_index];
        last_connection = b;

        size_t circuit1 = boxes[b.point1][3];
        size_t circuit2 = boxes[b.point2][3];

        // If boxes not in same circuit, combine
        if (circuit1 != circuit2) {
            
            // Combine to lower index circuit
            size_t new_circuit = circuit1 < circuit2 ? circuit1 : circuit2;
            size_t old_circuit = circuit1 < circuit2 ? circuit2 : circuit1;

            for (auto box : circuits[old_circuit]) {
                // Assign new circuit number to box
                boxes[box][3] = new_circuit;
                circuits[new_circuit].push_back(box);
            }
            circuits[old_circuit] = {};
        }
        distance_index++;
    }

    // Sort list of circuits by size (number of boxes)
    sort(circuits.begin(), circuits.end(), circuitCompare);

    for (auto c : circuits) {
        cout << c.size() << endl;
    }

    cout << "Last connection: " << boxes[last_connection.point1][0] << " to " << boxes[last_connection.point2][0] << endl;

    long long answer = static_cast<long long>(boxes[last_connection.point1][0]) * boxes[last_connection.point2][0];

    cout << "Part 2 Answer: " << answer << endl;
}

int main() {

    part1();
    part2();

    return 0;
}