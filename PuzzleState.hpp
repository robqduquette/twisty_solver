// PuzzleState.hpp
#ifndef PUZZLESTATE_HPP
#define PUZZLESTATE_HPP

#include <vector>
#include <memory>  // For std::unique_ptr
#include <iostream>

// Templated abstract base class representing a general puzzle state
template <typename MoveType>
class PuzzleState {
protected:
    // moves performed on the puzzle so far
    std::vector<MoveType> moves;

public:
    // Constructor to initialize the moves vector
    PuzzleState(const std::vector<MoveType>& movesApplied = {}) : moves(movesApplied) {}

    virtual ~PuzzleState() {}

    // Generate all valid moves from the current state
    virtual std::vector<MoveType> getValidMoves() const = 0;

    // Apply a move to the current state and return a new state
    virtual std::unique_ptr<PuzzleState> applyMove(MoveType move) = 0;

    // Heuristic function for calculating the cost to the goal state
    virtual int heuristic(const PuzzleState& goal) const = 0;

    // Check if the current state is the goal state
    virtual bool isGoal(const PuzzleState& goal) const = 0;

    // Display the state (for debugging)
    virtual void printState() const = 0;

    // Display the moves performed to reach the current state
    void printMoves() const {
        std::cout << "Moves: ";
        for (const auto& move : moves) {
            std::cout << move2str(move) << " ";
        }
        std::cout << "\n";
    }

protected:
    // Convert a move to a string (to be implemented by derived classes)
    virtual std::string move2str(MoveType move) const = 0;
};

#endif // PUZZLESTATE_HPP
