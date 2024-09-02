// Puzzle.hpp
#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <vector>
#include <string>
#include <stdexcept>  // For std::invalid_argument

using std::string;

// Templated abstract base class for all puzzles
template<typename MoveType>
class Puzzle {
public:
    virtual ~Puzzle() {}

    // Pure virtual functions to be implemented by derived classes
    virtual string getStateAsString() const = 0;
    virtual void applyMove(MoveType move) = 0;
    virtual bool isSolved() const = 0;
    virtual void printState() const = 0;
    virtual std::vector<MoveType> getValidMoves() const = 0;
};

#endif // PUZZLE_HPP
