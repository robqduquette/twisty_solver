// main.cpp
#include "IDAStar.hpp"
#include "RubiksCubeState.hpp"
#include <iostream>

using namespace std;

int main() {
    // Create initial and goal states for the Rubik's Cube
    unique_ptr<PuzzleState<RubiksCubeMove>> start = make_unique<RubiksCubeState>(vector<int>{0, 1, 2, 3});
    RubiksCubeState goal({1, 2, 3, 0});
    int maxDepth = 5;  // Set maximum depth for search

    cout << "Starting IDA* search with maximum depth " << maxDepth << "...\n";
    idaStar(move(start), goal, maxDepth);  // Start the IDA* search

    // testing the rubiks cube state
    // start->printState();
    // start->printMoves();

    // auto next = start->applyMove(RubiksCubeMove::U);

    // cout << "start:\n";
    // start->printState();
    // start->printMoves();

    // cout << "next:\n";
    // next->printState();
    // next->printMoves();


    return 0;
}
