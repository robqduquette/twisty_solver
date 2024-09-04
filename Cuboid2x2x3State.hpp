// Cuboid2x2x3State.hpp
#ifndef Cuboid2x2x3STATE_HPP
#define Cuboid2x2x3STATE_HPP

#include "PuzzleState.hpp"
#include <vector>
#include <algorithm>
#include <map>

// Define specific moves for Rubik's Cube
enum class Cuboid2x2x3Move {
    U, U2, U3,  // Example moves specific to Rubik's Cube
    D, D2, D3,
    F2, R2
};

// Specific implementation for Rubik's Cube state
class Cuboid2x2x3State : public PuzzleState<Cuboid2x2x3Move> {
private:
    std::vector<int> state;  // Use vector to represent the cube state
    /*
        top down view:

        0  1    top layer
        2  3
        ----
        4  5    middle layer
        6  7
        ----
        8  9    bottom layer
        10 11
    */


public:
    Cuboid2x2x3State(const std::vector<int>& initialState, const std::vector<Cuboid2x2x3Move>& movesApplied = {})
        : PuzzleState<Cuboid2x2x3Move>(movesApplied), state(initialState) {}

    std::vector<Cuboid2x2x3Move> getValidMoves() const override {
        // Return all possible moves for a Rubik's Cube
        std::vector<Cuboid2x2x3Move> possibleMoves;
        // if moves have been done check the last move
        if(! moves.empty()){
            auto lastMove = moves[moves.size()-1];
            if (lastMove != Cuboid2x2x3Move::F2) {
                possibleMoves.push_back(Cuboid2x2x3Move::F2);
            }
            if (lastMove != Cuboid2x2x3Move::R2) {
                possibleMoves.push_back(Cuboid2x2x3Move::R2);
            }
            if (lastMove != Cuboid2x2x3Move::U && lastMove != Cuboid2x2x3Move::U2 && lastMove != Cuboid2x2x3Move::U3) {
                possibleMoves.push_back(Cuboid2x2x3Move::U);
                possibleMoves.push_back(Cuboid2x2x3Move::U2);
                possibleMoves.push_back(Cuboid2x2x3Move::U3);
            }
            if (lastMove != Cuboid2x2x3Move::D && lastMove != Cuboid2x2x3Move::D2 && lastMove != Cuboid2x2x3Move::D3) {
                possibleMoves.push_back(Cuboid2x2x3Move::D);
                possibleMoves.push_back(Cuboid2x2x3Move::D2);
                possibleMoves.push_back(Cuboid2x2x3Move::D3);
            }
        } else {
            possibleMoves = {Cuboid2x2x3Move::F2, Cuboid2x2x3Move::R2,
                            Cuboid2x2x3Move::U, Cuboid2x2x3Move::U2, Cuboid2x2x3Move::U3,
                            Cuboid2x2x3Move::D, Cuboid2x2x3Move::D2, Cuboid2x2x3Move::D3};
        }

        return possibleMoves;
    }

    std::unique_ptr<PuzzleState> applyMove(Cuboid2x2x3Move move) override {
        std::vector<int> newState = state;  // Copy current state

        // Apply the move (specific transformations for Rubik's Cube)
        switch (move) {
            case Cuboid2x2x3Move::U:
                std::swap(newState[0], newState[1]);  // Example move
                std::swap(newState[0], newState[3]);
                std::swap(newState[0], newState[2]);
                break;
            case Cuboid2x2x3Move::U2:
                std::swap(newState[0], newState[3]);
                std::swap(newState[1], newState[2]);
                break;
            case Cuboid2x2x3Move::U3:
                std::swap(newState[0], newState[2]);
                std::swap(newState[0], newState[3]);
                std::swap(newState[0], newState[1]);
                break;
            case Cuboid2x2x3Move::D:
                std::swap(newState[8], newState[10]);
                std::swap(newState[8], newState[11]);
                std::swap(newState[8], newState[9]);
                break;
            case Cuboid2x2x3Move::D2:
                std::swap(newState[8], newState[11]);
                std::swap(newState[9], newState[10]);
                break;
            case Cuboid2x2x3Move::D3:
                std::swap(newState[8], newState[9]);
                std::swap(newState[8], newState[11]);
                std::swap(newState[8], newState[10]);
                break;
            case Cuboid2x2x3Move::F2:
                std::swap(newState[2], newState[11]);
                std::swap(newState[3], newState[10]);
                std::swap(newState[6], newState[7]);
                break;
            case Cuboid2x2x3Move::R2:
                std::swap(newState[1], newState[11]);
                std::swap(newState[3], newState[9]);
                std::swap(newState[5], newState[7]);
                break;
            default:
                throw std::invalid_argument("Invalid move provided to 2x2x3.");
        }

        // create new list of moves and add move
        auto newMoves = moves;
        newMoves.push_back(move);

        return std::make_unique<Cuboid2x2x3State>(newState, newMoves);
    }

    int heuristic(const PuzzleState<Cuboid2x2x3Move>& goal) const override {
        // Cast goal to Cuboid2x2x3State and calculate heuristic
        const Cuboid2x2x3State& goalState = dynamic_cast<const Cuboid2x2x3State&>(goal);
        int h = std::max(centerHeuristic(), cornerHeuristic());
        // TODO: add heuristic (or don't)
        return h;
    }

    bool isGoal(const PuzzleState<Cuboid2x2x3Move>& goal) const override {
        const Cuboid2x2x3State& goalState = dynamic_cast<const Cuboid2x2x3State&>(goal);
        return state == goalState.state;
    }

    void printState() const override {
        std::cout << "-----\n";
        for (int i = 0; i < state.size(); i++) {
            std::cout << state[i] << " ";
            if(i%2 == 1) {std::cout << std::endl;}
            if(i%4 == 3)  {std::cout << "-----\n";}
        }
        std::cout << "\n";
    }

    // convert a move to a string for printing
    std::string move2str(Cuboid2x2x3Move move) const override {
        static const std::unordered_map<Cuboid2x2x3Move, std::string> moveMap = {
            {Cuboid2x2x3Move::U, "U"},
            {Cuboid2x2x3Move::U2, "U2"},
            {Cuboid2x2x3Move::U3, "U3"},
            {Cuboid2x2x3Move::D, "D"},
            {Cuboid2x2x3Move::D2, "D2"},
            {Cuboid2x2x3Move::D3, "D3"},
            {Cuboid2x2x3Move::F2, "F2"},
            {Cuboid2x2x3Move::R2, "R2"},
        };

        auto it = moveMap.find(move);
        if (it != moveMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid move provided to moveToString function");
        }
    }

    int centerHeuristic() const {
        int h = 0;
        for (int i = 4; i < 8; i++){
            if(i != state[i]) h++;
        }
        return h/2;
    }

    int cornerHeuristic() const {
        int h = 0;
        for(int i = 0; i < state.size(); i++){
            //skip the centers
            if (i > 3 && i < 8) continue;
            if (i != state[i]) h++;
        }
        return h/4;
    }
};

#endif // Cuboid2x2x3STATE_HPP
