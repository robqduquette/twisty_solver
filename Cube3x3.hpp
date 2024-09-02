// Cube3x3.hpp
#ifndef Cube3x3_HPP
#define Cube3x3_HPP

#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <cassert>
#include "Puzzle.hpp"

using std::vector;
using std::cout;
using std::string;


// valid moves for the 3x3 cube
enum class Cube3x3Move {
    R, R2, R3,
    U, U2, U3,
    F, F2, F3,
    L, L2, L3,
    D, D2, D3,
    B, B2, B3
};

// Define the BoobCube class and use `BoobCubeMove` directly
class Cube3x3 : public Puzzle<Cube3x3Move> {
private:
    #define DIM 3
    vector<int> state;
    vector<Cube3x3Move> moves;

/*
      U
    L F R B
      D
*/
public:

    // Constructor
    Cube3x3() : state(DIM*DIM*6,0), moves(){
        // initialize the state as a solved cube
        for(int i = 0; i < state.size(); i++){
            state[i] = i / 9;
        }

    } // Initialize solved state

    Cube3x3(vector<int> state_in) : state(state_in), moves() {
        if (state.size() != 54){
            throw std::invalid_argument("Incorrect number of stickers provided to 3x3x3 constructor");
        }

        // check and count stickers
        int numStickers[6] = {0,0,0,0,0,0};
        for(int i = 0; i < state.size(); i++){
            // check valid sticker
            int sticker = state[i];
            if ( sticker < 0 || sticker > 5) {
                throw std::invalid_argument("Invalid state provided to 3x3x3 constructor.");
            }
            // count stickers
            numStickers[sticker]++;
        }

        // check sticker amounts
        for (int i = 0; i < 6; i++){
            if (numStickers[i] != 9){
                throw std::invalid_argument("Invalid state provided to 3x3x3 constructor. Too few/many stickers.");
            }
        }
    }

    // Helper to convert enum to string for display
    static std::string moveToString(Cube3x3Move m) {
        static const std::unordered_map<Cube3x3Move, std::string> moveMap = {
            {Cube3x3Move::U, "U"},
            {Cube3x3Move::U2, "U2"},
            {Cube3x3Move::U3, "U3"},
            {Cube3x3Move::U, "F"},
            {Cube3x3Move::U, "F2"},
            {Cube3x3Move::U, "F3"},
            {Cube3x3Move::U, "R"},
            {Cube3x3Move::U, "R2"},
            {Cube3x3Move::U, "R3"},
            {Cube3x3Move::U, "D"},
            {Cube3x3Move::U, "D2"},
            {Cube3x3Move::U, "D3"},
            {Cube3x3Move::U, "B"},
            {Cube3x3Move::U, "B2"},
            {Cube3x3Move::U, "B3"},
            {Cube3x3Move::U, "L"},
            {Cube3x3Move::U, "L2"},
            {Cube3x3Move::U, "L3"},
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
        std::string ststr = "ee";

        return ststr;
    }

    std::vector<Cube3x3Move> getValidMoves() const override {
        //TODO
        return {Cube3x3Move::U};
    }

    void applyMove(Cube3x3Move move) override {
        std::cout << "Applying move: " << moveToString(move) << std::endl;

        switch (move){
            case Cube3x3Move::U:

                break;
            default:
                throw std::invalid_argument("Invalid move provided to applyMove function");
        }

    }

    bool isSolved() const override {
        return true;//state == 0;
    }

    void printState() const override {
        std::cout << "3x3 Cube state: " << getStateAsString() << std::endl;
    }
};

#endif // Cube3x3_HPP
