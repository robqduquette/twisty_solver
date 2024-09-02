// test_puzzle.cpp
#include "BoobCube.hpp"
#include "Cube3x3.hpp"
using namespace std;

int main() {
    // BoobCube cube;

    // cube.printState();

    // // Example moves
    // vector<BoobCubeMove> moves = {
    //     BoobCubeMove::U,
    //     BoobCubeMove::U2,
    //     BoobCubeMove::U3,
    //     BoobCubeMove::U3,
    //     BoobCubeMove::U3,
    //     BoobCubeMove::U3
    // };

    // for (const auto& move : moves) {
    //     try {
    //         cube.applyMove(move); // Use enum class Move to apply moves
    //     } catch (const std::invalid_argument& e) {
    //         cerr << "Exception: " << e.what() << endl;
    //     }
    //     cube.printState();

    //     cout << "Is solved? " << cube.isSolved() << "\n";
    // }

    Cube3x3 rcube;
    Cube3x3 rcube2({0,0,0,0,0,0,0,0,1,
                    1,1,1,1,1,1,1,1,0,
                    2,2,2,2,2,2,2,2,2,
                    3,3,3,3,3,3,3,3,3,
                    4,4,4,4,4,4,4,4,4,
                    5,5,5,5,5,5,5,5,5});

    rcube2.printState();
    return 0;
}
