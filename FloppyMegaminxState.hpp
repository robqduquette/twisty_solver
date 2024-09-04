// FloppyMegaminxState.hpp
#ifndef FloppyMegaminxSTATE_HPP
#define FloppyMegaminxSTATE_HPP

#include "PuzzleState.hpp"
#include <vector>
#include <algorithm>
#include <map>

// Define specific moves for Rubik's Cube
enum class FloppyMegaminxMove {
    R, U, L, D, H
    // hold the puzzle with the a flat side toward you/on the table (point on top)
    /*
              *
          L *   * U
          *       *
         H *     * R
            * * *
              D
    */
};

// Specific implementation for Rubik's Cube state
class FloppyMegaminxState : public PuzzleState<FloppyMegaminxMove> {
private:
    std::vector<int> state;
     /* Corner positions        orientations
              1                         7
            *   *                    6     8
          0       2               15          9
           *     *                 14       10
            4 * 3                   13 12 11
    */

public:
    FloppyMegaminxState(const std::vector<int>& initialState = {0,1,2,3,4, 1,1,1,1,1,1,1,1,1,1}, const std::vector<FloppyMegaminxMove>& movesApplied = {})
        : PuzzleState<FloppyMegaminxMove>(movesApplied), state(initialState) {}

    std::vector<FloppyMegaminxMove> getValidMoves() const override {
        // Return all possible valid moves given the previous moves
        std::vector<FloppyMegaminxMove> allMoves = {FloppyMegaminxMove::R, FloppyMegaminxMove::U,
                            FloppyMegaminxMove::L, FloppyMegaminxMove::D, FloppyMegaminxMove::H};
        std::vector<FloppyMegaminxMove> possibleMoves;

        // if moves have been done check the last move
        if(! moves.empty()){
            auto lastMove = moves[moves.size()-1];
            for(auto move : allMoves){
                if (move != lastMove) {possibleMoves.push_back(move);}
            }
            return possibleMoves;
        }
        return allMoves;
    }

    std::unique_ptr<PuzzleState> applyMove(FloppyMegaminxMove move) override {
        std::vector<int> newState = state;  // Copy current state

        // Apply the move (specific transformations for Rubik's Cube)
        switch (move) {
            case FloppyMegaminxMove::U:
                std::swap(newState[1], newState[2]);
                std::swap(newState[7], newState[9]);
                newState[7] *= -1;
                newState[8] *= -1;
                newState[9] *= -1;
                break;
            case FloppyMegaminxMove::L:
                std::swap(newState[0],newState[1]);
                std::swap(newState[5], newState[7]);
                newState[5] *= -1;
                newState[6] *= -1;
                newState[7] *= -1;
                break;
            case FloppyMegaminxMove::R:
                std::swap(newState[2],newState[3]);
                std::swap(newState[9],newState[11]);
                newState[9] *= -1;
                newState[10] *= -1;
                newState[11] *= -1;
                break;
            case FloppyMegaminxMove::D:
                std::swap(newState[3],newState[4]);
                std::swap(newState[11],newState[13]);
                newState[11] *= -1;
                newState[12] *= -1;
                newState[13] *= -1;
                break;
            case FloppyMegaminxMove::H:
                std::swap(newState[0],newState[4]);
                std::swap(newState[5],newState[13]);
                newState[5] *= -1;
                newState[14] *= -1;
                newState[13] *= -1;
                break;

            default:
                throw std::invalid_argument("Invalid move provided to floppy megaminx.");
        }

        // create new list of moves and add move
        auto newMoves = moves;
        newMoves.push_back(move);

        return std::make_unique<FloppyMegaminxState>(newState, newMoves);
    }

    int heuristic(const PuzzleState<FloppyMegaminxMove>& goal) const override {
        // Cast goal to FloppyMegaminxState and calculate heuristic
        const FloppyMegaminxState& goalState = dynamic_cast<const FloppyMegaminxState&>(goal);
        int h = 0;
        // TODO: add heuristic (or don't)
        return h;
    }

    bool isGoal(const PuzzleState<FloppyMegaminxMove>& goal) const override {
        const FloppyMegaminxState& goalState = dynamic_cast<const FloppyMegaminxState&>(goal);
        return state == goalState.state;
    }

    void printState() const override {
        std::cout << "Corner Position: \t(";
        for (int i = 0; i < 5; i++) {
            std::cout << " "<< state[i] << " ";
        }
        std::cout << ")\nCorner Orientation: \t(";
        for (int i = 5; i < state.size(); i+=2) {
            if(state[i] > 0){
                std::cout << " ";
            }
            std::cout << state[i] << " ";
        }
        std::cout << ")\nEdge Orientation: \t(";
        for (int i = 6; i < state.size(); i+=2) {
            if(state[i] > 0){
                std::cout << " ";
            }
            std::cout << state[i] << " ";
        }
        std::cout << ")\n";
    }

    // convert a move to a string for printing
    std::string move2str(FloppyMegaminxMove move) const override {
        static const std::unordered_map<FloppyMegaminxMove, std::string> moveMap = {
            {FloppyMegaminxMove::U, "U"},
            {FloppyMegaminxMove::R, "R"},
            {FloppyMegaminxMove::D, "D"},
            {FloppyMegaminxMove::L, "L"},
            {FloppyMegaminxMove::H, "H"},
        };

        auto it = moveMap.find(move);
        if (it != moveMap.end()) {
            return it->second;
        } else {
            throw std::invalid_argument("Invalid move provided to moveToString function");
        }
    }

    // get the solved state
    FloppyMegaminxState getSolvedState(){
        return FloppyMegaminxState();
    }
};

#endif // FloppyMegaminxSTATE_HPP
