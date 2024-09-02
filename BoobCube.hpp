// BoobCube.hpp
#ifndef BOOBCUBE_HPP
#define BOOBCUBE_HPP

#include <vector>
#include <iostream>
#include <unordered_map>
#include "Puzzle.hpp"

// valid moves for the boob cube
enum class BoobCubeMove {
    U, U2, U3
};

// Define the BoobCube class and use `BoobCubeMove` directly
class BoobCube : public Puzzle<BoobCubeMove> {
private:
    int state;  // Internal state representation

public:

    // Constructor
    BoobCube() : state(0) {} // Initialize solved state

    // Helper to convert enum to string for display
    static std::string moveToString(BoobCubeMove m) {
        static const std::unordered_map<BoobCubeMove, std::string> moveMap = {
            {BoobCubeMove::U, "U"},
            {BoobCubeMove::U2, "U2"},
            {BoobCubeMove::U3, "U3"}
        };

        auto it = moveMap.find(m);
        if (it != moveMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid move provided to moveToString function");
        }
    }

    // Implement pure virtual functions from Puzzle
    std::string getStateAsString() const override {
        return std::to_string(state);
    }

    std::vector<BoobCubeMove> getValidMoves() const override {
        return {BoobCubeMove::U, BoobCubeMove::U2, BoobCubeMove::U3};
    }

    void applyMove(BoobCubeMove move) override {
        std::cout << "Applying move: " << moveToString(move) << std::endl;

        switch (move){
            case BoobCubeMove::U:
                state += 1;
                break;
            case BoobCubeMove::U2:
                state += 2;
                break;
            case BoobCubeMove::U3:
                state += 3;
                break;
            default:
                throw std::invalid_argument("Invalid move provided to applyMove function");
        }

        state = state % 4;  // Wraparound logic
    }

    bool isSolved() const override {
        return state == 0;
    }

    void printState() const override {
        std::cout << "Boob Cube state: " << getStateAsString() << std::endl;
    }
};

#endif // BOOBCUBE_HPP
