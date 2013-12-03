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
#include <fstream>

class Board
{
public:
    // number of letters in row/column
    const static int BOARD_SIZE = 8;
    
    // min word size
    const static int MIN_WORD_SIZE = 4;
    
    // pointer to scene
    Game* game;
    
    // selected letter
    Letter selected;
    
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
    void checkAgainstDictionary(vector<string> words, vector<string> &validWords);
    
    // main word loop, check for valid and unique words, add to score
    void wordCheck();
    
    // check if any of the words have been found previously
    // add unique words to the uniqueWords vector
    void uniqueCheck(vector<string> words, vector<string> &uniqueWords);
    
    // score words based on 2^(n-4)
    void scoreWords(vector<string> &uniqueWords);
    
    void letterSwap(Letter &l2);
};

#endif
