//
//  Board.cpp
//  HelloCpp
//
//  Created by Adam Gressen on 11/18/13.
//
//

#include "Board.h"

using namespace std;

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
    vector<string> words;
    // generate list of all possible words
    generateWordList(words);
    
    // sort list by length of each word
    sortWords(words);
    
    // check words against dictionary
    checkAgainstDictionary(words);
}

void Board::generateWordList(vector<string> &words) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // check up
            findWords(i, j, 0, -1, words);
            // check down
            findWords(i, j, 0, 1, words);
            // check left
            findWords(i, j, -1, 0, words);
            // check right
            findWords(i, j, 1, 0, words);
            // check diagonal, up, left
            findWords(i, j, -1, -1, words);
            // check diagonal, up, right
            findWords(i, j, 1, -1, words);
            // check diagonal, down, left
            findWords(i, j, -1, 1, words);
            // check diagonal, down, right
            findWords(i, j, 1, 1, words);
        }
    }
}

void Board::findWords(int row, int col, int d_row, int d_col, vector<string> &words) {
    int pos = row * col;
    //words.push_back(FOUND_WORD);
    //could also use list: words.insert(words.end(), found.begin(), found.end());
}

// sort by length of string
// larger strings first
struct compare {
    bool operator()(const string& first, const string& second) {
        return first.size() > second.size();
    }
};

void Board::sortWords(vector<string> &words) {
    compare c;
    std::sort(words.begin(), words.end(), c);
}

void Board::checkAgainstDictionary(vector<string> &words) {
    for (int i = 0; i < words.size(); i++) {
        
    }
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
