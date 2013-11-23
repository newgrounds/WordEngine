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
    
    wordCheck();
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
    vector<string> wordsFound;
    // generate list of all possible words
    generateWordList(wordsFound);
    
    cocos2d::log("Found %lu words", wordsFound.size());
    
    // sort list by length of each word
    sortWords(wordsFound);
    
    vector<string> validWords;
    
    // check words against dictionary
    checkAgainstDictionary(wordsFound, validWords);
    
    for (int i = 0; i < validWords.size(); i++) {
        cocos2d::log("valid word: %s", validWords[i].c_str());
    }
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
    string word = "";
    
    // finding largest word in given direction within bounds of board
    while (row < BOARD_SIZE && row >= 0 && col < BOARD_SIZE && col >= 0) {
        Letter l = letters[row][col];
        //cocos2d::log("%c", l.letter);
        word += l.letter;
        row += d_row;
        col += d_col;
    }
    
    // find all shorter words within the word
    while (word.size() >= MIN_WORD_SIZE) {
        //cocos2d::log("%lu, %s", word.size(), word.c_str());
        words.push_back(word);
        word = word.substr(0, word.size() - 1);
    }
}

// sort by length of string, descending by length
struct compare {
    bool operator()(const string& first, const string& second) {
        return first.size() > second.size();
    }
};

void Board::sortWords(vector<string> &words) {
    compare c;
    sort(words.begin(), words.end(), c);
}

void Board::checkAgainstDictionary(vector<string> words, vector<string> &validWords) {
    for (int i = 0; i < words.size(); i++) {
        string word = words[i];
        
        // get length of word
        int len = word.length();
        // get first letter of word
        char firstLetter = word[0];
        //cocos2d::log("(%d, %c)", len, firstLetter);
        
        // generate path name based on length and first letter of word
        string path = "dict/" + to_string(len) + "/" + firstLetter + ".txt";
        
        // get file utils instance
        cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance();
        
        // check if file exists
        if (fileUtils->isFileExist(path)) {
            //cocos2d::log("file exists");
            
            // open file using full path
            ifstream file(fileUtils->fullPathForFilename(path).c_str());
            string line;
            while (getline(file, line)) {
                //cocos2d::log("%s", line.c_str());
                if (line.compare(word) == 0) {
                    validWords.push_back(word);
                }
            }
            
            // close file
            file.close();
        } else {
            cocos2d::log("no file bro");
        }
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
