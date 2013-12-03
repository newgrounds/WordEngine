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
    
    // list of valid words in the board
    vector<string> validWords;
    
    // check words against dictionary
    checkAgainstDictionary(wordsFound, validWords);
    
    // list of unique words to count towards the score
    vector<string> uniqueWords;
    
    // check words against previously found words
    uniqueCheck(validWords, uniqueWords);
    
    // score words
    scoreWords(uniqueWords);
    
    // add all unique words to finalWords
    for (int j = 0; j < uniqueWords.size(); j++) {
        game->finalWords.push_back(uniqueWords[j]);
    }
    
    // print finalWords
    for (int i = 0; i < game->finalWords.size(); i++) {
        cocos2d::log("final word: %s", game->finalWords[i].c_str());
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

void Board::uniqueCheck(vector<string> words, vector<string> &uniqueWords) {
    // loop through the valid words
    for (int i = 0; i < words.size(); i++) {
        string word = words[i];
        if(find(game->finalWords.begin(), game->finalWords.end(), word) != game->finalWords.end()) {
            // the word is in the list
            cocos2d::log("'%s' is already in the list", word.c_str());
        } else {
            cocos2d::log("added '%s' to the unique words list", word.c_str());
            // add to uniqueWords
            uniqueWords.push_back(word);
        }
    }
}

void Board::scoreWords(vector<string> &uniqueWords) {
    // loop through all the unique words
    for (int i = 0; i < uniqueWords.size(); i++) {
        float s = pow(2, uniqueWords[i].size() - 4);
        game->score += s;
        cocos2d::log("size of the word %lu, score %f, total score %f", uniqueWords[i].size(), s, game->score);
    }
}

void Board::letterSwap(Letter &l2) {
    cocos2d::log("swap %c and %c", selected.letter, l2.letter);
    
    int row1 = selected.row;
    int col1 = selected.col;
    int row2 = l2.row;
    int col2 = l2.col;
    
    // actually swap the letters
    Letter temp = letters[row1][col1];
    letters[row1][col1] = letters[row2][col2];
    letters[row2][col2] = temp;
    
    // store new positions
    letters[row1][col1].row = row1;
    letters[row1][col1].col = col1;
    letters[row2][col2].row = row2;
    letters[row2][col2].col = col2;
    
    // reposition the labels
    letters[row1][col1].posn = cocos2d::Point(240+(row1*Letter::PADDING), 240+(col1*Letter::PADDING));
    letters[row1][col1].label->setPosition(letters[row1][col1].posn);
    letters[row2][col2].posn = cocos2d::Point(240+(row2*Letter::PADDING), 240+(col2*Letter::PADDING));
    letters[row2][col2].label->setPosition(letters[row2][col2].posn);
    
    selected.label->setColor(cocos2d::Color3B(255, 255, 255));
    l2.label->setColor(cocos2d::Color3B(255, 255, 255));
    
    // reset the selected letter to an empty letter
    selected = Letter();
    
    wordCheck();
}
