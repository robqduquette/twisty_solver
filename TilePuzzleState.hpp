// TilePuzzleState.hpp
#ifndef TilePuzzleSTATE_HPP
#define TilePuzzleSTATE_HPP

#include "PuzzleState.hpp"
#include <vector>
#include <algorithm>
#include <map>

// Define specific moves for Rubik's Cube
enum class TilePuzzleMove {
    U, U2, U3  // Example moves specific to Rubik's Cube
};

// Specific implementation for Rubik's Cube state
class TilePuzzleState : public PuzzleState<TilePuzzleMove> {
private:
    std::vector<int> state;  // Use vector to represent the cube state

public:
    TilePuzzleState(const std::vector<int>& initialState, const std::vector<TilePuzzleMove>& movesApplied = {})
        : PuzzleState<TilePuzzleMove>(movesApplied), state(initialState) {}

    std::vector<TilePuzzleMove> getValidMoves() const override {
        // Return all possible moves for a Rubik's Cube
        return {TilePuzzleMove::U, TilePuzzleMove::U2, TilePuzzleMove::U3};
    }

    std::unique_ptr<PuzzleState> applyMove(TilePuzzleMove move) override {
        std::vector<int> newState = state;  // Copy current state

        // Apply the move (specific transformations for Rubik's Cube)
        switch (move) {
            case TilePuzzleMove::U:
                std::swap(newState[0], newState[1]);  // Example move
                break;
            case TilePuzzleMove::U2:
                std::swap(newState[1], newState[2]);
                break;
            case TilePuzzleMove::U3:
                std::swap(newState[2], newState[3]);
                break;
        }

        // create new list of moves and add move
        auto newMoves = moves;
        newMoves.push_back(move);

        return std::make_unique<TilePuzzleState>(newState, newMoves);
    }

    int heuristic(const PuzzleState<TilePuzzleMove>& goal) const override {
        // Cast goal to TilePuzzleState and calculate heuristic
        const TilePuzzleState& goalState = dynamic_cast<const TilePuzzleState&>(goal);
        int h = 0;
        for (size_t i = 0; i < state.size(); ++i) {
            if (state[i] != goalState.state[i]) {
                ++h;  // Example heuristic: count of misplaced tiles
            }
        }
        return h;
    }

    bool isGoal(const PuzzleState<TilePuzzleMove>& goal) const override {
        const TilePuzzleState& goalState = dynamic_cast<const TilePuzzleState&>(goal);
        return state == goalState.state;
    }

    void printState() const override {
        for (int val : state) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    // convert a move to a string for printing
    std::string move2str(TilePuzzleMove move) const override {
        static const std::unordered_map<TilePuzzleMove, std::string> moveMap = {
            {TilePuzzleMove::U, "U"},
            {TilePuzzleMove::U2, "U2"},
            {TilePuzzleMove::U3, "U3"},
        };

        auto it = moveMap.find(move);
        if (it != moveMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid move provided to moveToString function");
        }
    }
};

#endif // TilePuzzleSTATE_HPP
