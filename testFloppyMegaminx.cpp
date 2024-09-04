// main.cpp
#include "IDAStar.hpp"
#include "FloppyMegaminxState.hpp"
#include <iostream>

using namespace std;

// #define TEST

int main() {
    // Floppy Megaminx test
    unique_ptr<PuzzleState<FloppyMegaminxMove>> start = make_unique<FloppyMegaminxState>();
    start->printState();


    FloppyMegaminxState goal({0,1,2,3,4, 1,-1,1,1,1,-1,1,1,1,1});

    cout << "\nGoal state:\n";
    goal.printState();

    int maxDepth = 14;

    //start->printState();

    // TEST MOVES
    #ifdef TEST
    vector<FloppyMegaminxMove> moves = {FloppyMegaminxMove::L,
                                        FloppyMegaminxMove::U,
                                        FloppyMegaminxMove::R,
                                        FloppyMegaminxMove::D,
                                        FloppyMegaminxMove::H};

    cout << "\nApplying each move as test:\n\n";
    start->printState();
    cout << endl;
    for(auto move : moves) {
        start = start->applyMove(move);
        start->printMoves();

        cout << "Valid Moves: ";
        for(auto m : start->getValidMoves()){
            cout << start->move2str(m) <<", ";
        }
        cout << endl;

        start->printState();
        cout << endl;
    }
    #endif

    cout << "Starting Floppy Megaminx IDA* search with maximum depth " << maxDepth << "...\n";
    idaStar(move(start), goal, maxDepth);  // Start the IDA* search


    return 0;
}
