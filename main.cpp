// main.cpp
#include "IDAStar.hpp"
#include "TilePuzzleState.hpp"
#include "Cuboid2x2x3State.hpp"
#include <iostream>

using namespace std;

int main() {
    // 2x2x3 test
    unique_ptr<PuzzleState<Cuboid2x2x3Move>> start = make_unique<Cuboid2x2x3State>(vector<int>{0,1,3,2, 4,5,6,7, 10,9,8,11});
    Cuboid2x2x3State goal({0,1,2,3,4,5,6,7,8,9,10,11});
    int maxDepth = 10;

    cout << "Starting 2x2x3 IDA* search with maximum depth " << maxDepth << "...\n";
    idaStar(move(start), goal, maxDepth);  // Start the IDA* search


    // Create initial and goal states for the Rubik's Cube
    // unique_ptr<PuzzleState<TilePuzzleMove>> start = make_unique<TilePuzzleState>(vector<int>{0, 1, 2, 3});
    // TilePuzzleState goal({1, 2, 3, 0});
    // int maxDepth = 5;  // Set maximum depth for search

    // cout << "Starting IDA* search with maximum depth " << maxDepth << "...\n";
    // idaStar(move(start), goal, maxDepth);  // Start the IDA* search

    // testing the rubiks cube state
    // start->printState();
    // start->printMoves();

    // auto next = start->applyMove(TilePuzzleMove::U);

    // cout << "start:\n";
    // start->printState();
    // start->printMoves();

    // cout << "next:\n";
    // next->printState();
    // next->printMoves();


    return 0;
}
