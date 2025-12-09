// day7.cpp
// Jenae Matson
// 2025-12-08
// Solution for Advent of Code 2025 Day 7

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void part1() {

    string input;
    ifstream File("input.txt");

    // Store file input;
    vector<vector<char>> graph;
    int index = 0;
    while(getline(File, input)) {
        graph.push_back({});
        for(int i=0; i<input.length(); i++) {
            char c = input[i];
            graph[index].push_back(c);
        }
        index++;
    }

    vector<int> beams(graph[0].size(), 0);

    size_t splits = 0;

    for(int line=0; line < graph.size(); line++) {
        for(int col=0; col < graph[0].size(); col++) {

            char c = graph[line][col];

            // Start of tachyon beam
            if (c == 'S') {
                beams[col] = 1;
            }

            // Beam split
            if (c == '^' && beams[col] == 1) {
                splits++;
                beams[col] = 0;
                beams[col+1] = 1;
                beams[col-1] = 1;
            }
        }
    }

    cout << "Part 1 Answer: " << splits << endl;

}

// Follow paths through the graph starting at a split at the given line and col
size_t beam_recurse(const vector<vector<char>> & graph, vector<vector<size_t>>& values, size_t start_line, size_t start_col) {

    size_t total = 0;

    // Follow left down
    size_t left_start[2] = { start_line, start_col-1 };
    while( left_start[0] < graph.size() ) {

        // Reached bottom of graph
        if (left_start[0] == graph.size()-1) {
            total++;
            break;
        }

        char next_char = graph[left_start[0]][left_start[1]];

        if (next_char == '^') {
            // Traverse subtree if unvisited
            if (values[left_start[0]][left_start[1]] == 0 ) {
                size_t subtotal = beam_recurse(graph, values, left_start[0], left_start[1]);
                total += beam_recurse(graph, values, left_start[0], left_start[1]);
                values[left_start[0]][left_start[1]] = subtotal;
            } else
                total += values[left_start[0]][left_start[1]];
            
            break;
        }

        left_start[0] += 1;
    }

    // Follow right down
    size_t right_start[2] = { start_line, start_col+1 };
    while( right_start[0] < graph.size() ) {

        // Reached bottom of graph
        if (right_start[0] == graph.size()-1) {
            total++;
            break;
        }

        char next_char = graph[right_start[0]][right_start[1]];

        if (next_char == '^') {
            // Traverse subtree is unvisited
            if (values[right_start[0]][right_start[1]] == 0 ) {
                size_t subtotal = beam_recurse(graph, values, right_start[0], right_start[1]);
                total += subtotal;
                values[right_start[0]][right_start[1]] = subtotal;
            } else 
                total += values[right_start[0]][right_start[1]];
            break;
        }

        right_start[0] += 1;
    }

    return total;
}

void part2() {

    string input;
    ifstream File("input.txt");

    // Store file input;
    vector<vector<char>> graph;
    int index = 0;
    while(getline(File, input)) {
        graph.push_back({});
        for(int i=0; i<input.length(); i++) {
            char c = input[i];
            graph[index].push_back(c);
        }
        index++;
    }

    size_t start[2] = {0,0};

    for(int line=0; line < graph.size(); line++) {
        for(int col=0; col < graph[0].size(); col++) {

            char c = graph[line][col];

            // Start of tachyon beam
            if (c == 'S') {
                start[0] = col;
                start[1] = line;
                graph[line+1][col] = '|';
                continue;
            }

            if (line > 0) {
                // Beam split
                if (c == '^' && graph[line-1][col] == '|') {
                    graph[line][col-1] = '|';
                    graph[line][col+1] = '|';
                    continue;
                } else {
                    if (graph[line-1][col] == '|') {
                        graph[line][col] = '|';
                    }
                }
            }
        }
    }

    char curr = ' ';
    while(curr != '^') {
        start[1] += 1;
        curr = graph[start[1]][start[0]];
    }

    vector<vector<size_t>> values(graph.size(), vector<size_t>(graph[0].size()));

    size_t answer = beam_recurse(graph, values, start[1], start[0]);

    cout << "Part 2 Answer: " << answer << endl;
}

int main() {

    part1();
    part2();

    return 0;
}