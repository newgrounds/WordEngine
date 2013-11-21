//
//  Board.cpp
//  HelloCpp
//
//  Created by Adam Gressen on 11/18/13.
//
//

#include "Board.h"

Board::Board(Game* g) {
    // randomize the seed
    srand(time(0));
    
    game = g;
    
    generateBoard();
}

void Board::generateBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        vector<Letter> row;
        for (int j = 0; j < BOARD_SIZE; j++) {
            Letter l = Letter(i, j);
            row.push_back(l);
            game->addChild(l.label, 1);
        }
        letters.push_back(row);
    }
}

void Board::wordCheck() {
    // generate list of all possible words
    
    // sort list by length of each word
    
    // check words against dictionary
}

void Board::removeWord() {
    
}

void Board::dropLetters() {
    
}

void Board::addLetters() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        vector<Letter> row;
        for (int j = 0; j < BOARD_SIZE; j++) {
            // check if pointer to letter is null
            if (&letters[i][j] == NULL) {
                //letters[i][j] = Letter(i, j);
            }
        }
    }
}
