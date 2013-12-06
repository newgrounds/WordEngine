#ifndef __GAME_H__
#define __GAME_H__

using namespace std;
#include "cocos2d.h"
#include <vector>

class Game : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // the score
    float score;
    
    // score label
    cocos2d::LabelTTF* scoreLabel;
    
    // update the score
    void UpdateScore();
    
    // number of starting moves
    const static int STARTING_MOVES = 20;
    
    // number of moves
    int moves;
    
    // list of found words
    vector<string> finalWords;
    
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};

#endif
