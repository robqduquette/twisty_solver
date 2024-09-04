// IDAStar.hpp
#ifndef IDASTAR_HPP
#define IDASTAR_HPP

#include "PuzzleState.hpp"
#include <limits>
#include <vector>
#include <unordered_set>
#include <iostream>

// Forward declaration of search function
template <typename MoveType>
int search(PuzzleState<MoveType>& current, const PuzzleState<MoveType>& goal, int g, int threshold, int maxDepth, int& nodesSearched, int& numSolns);

// Templated function to implement the modified IDA* search
template <typename MoveType>
void idaStar(std::unique_ptr<PuzzleState<MoveType>> start, const PuzzleState<MoveType>& goal, int maxDepth) {
    int numNodesSearched = 0;
    int numSolutions = 0;

    int threshold = start->heuristic(goal);  // Initial threshold based on heuristic
    while (threshold <= maxDepth) {  // Continue only within the maximum depth
        int temp = search(*start, goal, 0, threshold, maxDepth, numNodesSearched, numSolutions);
        if (temp == -1) {
            // Continue searching even after finding a solution
            threshold += 1;  // Increment threshold for the next iteration
            numSolutions++;
        } else if (temp == std::numeric_limits<int>::max()) {
            std::cout << "No more solutions found within the maximum depth.\n";
            return;  // No more solutions within max depth
        } else {
            threshold = temp;  // Update threshold for the next iteration
        }
    }
    std::cout << "Search completed up to maximum depth: " << maxDepth << ".\n";
}

// Recursive templated function for IDA* search with max depth and solution output
template <typename MoveType>
int search(PuzzleState<MoveType>& current, const PuzzleState<MoveType>& goal, int g, int threshold, int maxDepth, int& nodesSearched, int& numSolns) {
    nodesSearched++;
    if(nodesSearched % 1000000 == 0) {std::cout << "Searched " << nodesSearched << " nodes\n";}

    int f = g + current.heuristic(goal);  // f = g + h
    if (f > threshold) return f;  // Return if f exceeds the current threshold
    if (current.isGoal(goal)) {
        //current.printState();
        std::cout << "Solution (" << ++numSolns << "/" <<nodesSearched;
        std::cout << ") found with " << g << " moves:\n";
        current.printMoves();
        std::cout << std::endl;

        return -1;  // Solution found
    }
    if (g == maxDepth) return std::numeric_limits<int>::max();  // Reached max depth

    int min = std::numeric_limits<int>::max();
    for (MoveType move : current.getValidMoves()) {
        auto next = current.applyMove(move);
        int temp = search(*next, goal, g + 1, threshold, maxDepth, nodesSearched, numSolns);
        if (temp == -1) {
            // Solution found; continue searching for more solutions
            continue;
        }
        if (temp < min) min = temp;
    }
    return min;
}

#endif // IDASTAR_HPP
