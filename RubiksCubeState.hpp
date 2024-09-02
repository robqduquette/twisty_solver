// RubiksCubeState.hpp
#ifndef RUBIKSCUBESTATE_HPP
#define RUBIKSCUBESTATE_HPP

#include "PuzzleState.hpp"
#include <vector>
#include <algorithm>
#include <map>

// Define specific moves for Rubik's Cube
enum class RubiksCubeMove {
    U, U2, U3  // Example moves specific to Rubik's Cube
};

// Specific implementation for Rubik's Cube state
class RubiksCubeState : public PuzzleState<RubiksCubeMove> {
private:
    std::vector<int> state;  // Use vector to represent the cube state

public:
    RubiksCubeState(const std::vector<int>& initialState, const std::vector<RubiksCubeMove>& movesApplied = {})
        : PuzzleState<RubiksCubeMove>(movesApplied), state(initialState) {}

    std::vector<RubiksCubeMove> getValidMoves() const override {
        // Return all possible moves for a Rubik's Cube
        return {RubiksCubeMove::U, RubiksCubeMove::U2, RubiksCubeMove::U3};
    }

    std::unique_ptr<PuzzleState> applyMove(RubiksCubeMove move) override {
        std::vector<int> newState = state;  // Copy current state

        // Apply the move (specific transformations for Rubik's Cube)
        switch (move) {
            case RubiksCubeMove::U:
                std::swap(newState[0], newState[1]);  // Example move
                break;
            case RubiksCubeMove::U2:
                std::swap(newState[1], newState[2]);
                break;
            case RubiksCubeMove::U3:
                std::swap(newState[2], newState[3]);
                break;
        }

        // create new list of moves and add move
        auto newMoves = moves;
        newMoves.push_back(move);

        return std::make_unique<RubiksCubeState>(newState, newMoves);
    }

    int heuristic(const PuzzleState<RubiksCubeMove>& goal) const override {
        // Cast goal to RubiksCubeState and calculate heuristic
        const RubiksCubeState& goalState = dynamic_cast<const RubiksCubeState&>(goal);
        int h = 0;
        for (size_t i = 0; i < state.size(); ++i) {
            if (state[i] != goalState.state[i]) {
                ++h;  // Example heuristic: count of misplaced tiles
            }
        }
        return h;
    }

    bool isGoal(const PuzzleState<RubiksCubeMove>& goal) const override {
        const RubiksCubeState& goalState = dynamic_cast<const RubiksCubeState&>(goal);
        return state == goalState.state;
    }

    void printState() const override {
        for (int val : state) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    // convert a move to a string for printing
    std::string move2str(RubiksCubeMove move) const override {
        static const std::unordered_map<RubiksCubeMove, std::string> moveMap = {
            {RubiksCubeMove::U, "U"},
            {RubiksCubeMove::U2, "U2"},
            {RubiksCubeMove::U3, "U3"},
        };

        auto it = moveMap.find(move);
        if (it != moveMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid move provided to moveToString function");
        }
    }
};

#endif // RUBIKSCUBESTATE_HPP
