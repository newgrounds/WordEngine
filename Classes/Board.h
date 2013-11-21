//
//  Board.h
//  HelloCpp
//
//  Created by Adam Gressen on 11/18/13.
//
//

#ifndef HelloCpp_Board_h
#define HelloCpp_Board_h

using namespace std;
#include "Game.h"
#include "cocos2d.h"
#include "Letter.h"
#include <vector>

class Board
{
public:
    // number of letters in row/column
    const static int BOARD_SIZE = 8;
    
    // pointer to scene
    Game* game;
    
    // list of letters
    vector<vector<Letter>> letters;
    
    // constructor that takes the game class
    Board(Game* g);
    
    // generate randomized board
    void generateBoard();
    
    // check if any words exist
    void wordCheck();
    
    // remove complete words
    void removeWord();
    
    // drop letters down
    void dropLetters();
    
    // add random letters to empty positions
    void addLetters();
};

#endif
