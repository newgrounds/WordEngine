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
    
    // generate list of words from board
    void generateWordList(vector<string> &words);
    
    // return list of words found in given direction
    void findWords(int row, int col, int d_row, int d_col, vector<string> &words);
    
    // sort words by length, descending
    void sortWords(vector<string> &words);
    
    // check words against dictionary
    void checkAgainstDictionary(vector<string> &words);
    
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
