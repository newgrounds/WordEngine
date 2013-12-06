#include "Game.h"
#include "Board.h"
#include "EndGame.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Game::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// overloaded == operator for the Letter class
inline bool operator== (const Letter &l1, const Letter &l2) {
    return l1.letter == l2.letter && l1.row == l2.row && l1.col == l2.col;
};

// overloaded != operator for the Letter class
inline bool operator!= (const Letter &l1, const Letter &l2) {
    return !operator==(l1, l2);
}

void Game::UpdateScore() {
    stringstream stream;
    stream << "Score: " << score;
    scoreLabel->setString(stream.str().c_str());
    scoreLabel->setPositionX(Letter::PADDING + scoreLabel->getContentSize().width/2);
}

void Game::UpdateMoves() {
    // decrement moves
    moves--;
    // update moves label
    stringstream stream;
    stream << "Moves: " << moves;
    movesLabel->setString(stream.str().c_str());
    movesLabel->setPositionX(Director::getInstance()->getVisibleSize().width - movesLabel->getContentSize().width/2 - Letter::PADDING);
    // check for game over
    GameOverCheck();
}

void Game::GameOverCheck() {
    // this should never go below 0, but just in case let's use <=
    if (moves <= 0) {
        Director::getInstance()->replaceScene(EndGame::createScene());
    }
}

// on "init" you need to initialize your instance
bool Game::init() {
    if ( !LayerColor::initWithColor(Color4B(255, 0, 0, 255)) ) {
        return false;
    }
    
    // add background music
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("action.mp3", true);
    
    // enable touch events
    setTouchEnabled(true);
    
    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();

    // add menu button
    MenuItemLabel* menuItem = MainMenu::createButton("End Game", CC_CALLBACK_1(Game::menuCallback, this));
	menuItem->setPosition(Point(screenSize.width - menuItem->getContentSize().width/2 - Letter::PADDING,
                                menuItem->getContentSize().height/2 + Letter::PADDING));
    // create menu, it's an autorelease object
    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    // display score on the screen
    scoreLabel = LabelTTF::create("Score: 0", "Arial", 35);
    scoreLabel->setColor(Color3B(255, 255, 255));
    scoreLabel->setPosition(Point(Letter::PADDING + scoreLabel->getContentSize().width/2, screenSize.height-scoreLabel->getContentSize().height/2 - Letter::PADDING));
    this->addChild(scoreLabel, 1);
    
    // display moves on the screen
    movesLabel = LabelTTF::create("Moves: 20", "Arial", 35);
    movesLabel->setColor(Color3B(255, 255, 255));
    movesLabel->setPosition(Point(screenSize.width - movesLabel->getContentSize().width/2 - Letter::PADDING, screenSize.height - movesLabel->getContentSize().height/2 - Letter::PADDING));
    this->addChild(movesLabel, 1);
    
    // set number of moves
    moves = STARTING_MOVES;
    
    // create board
    Board board = Board(this);
    // whether a letter has been selected
    bool letterSelected = false;
    
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(false);
    listener->onTouchBegan = [=](Touch* touch, Event* event) mutable {
        //log("touch began");
        Point location = touch->getLocation();//->getLocationInView();
        // TODO: Detect touches on labels
        for (int i = 0; i < Board::BOARD_SIZE; i++) {
            vector<Letter> row = board.letters[i];
            for (int j = 0; j < Board::BOARD_SIZE; j++) {
                Letter l = row[j];
                if (location.getDistance(l.posn) < 30) {
                    //log("touched %c", l.letter);
                    
                    l.label->setColor(cocos2d::Color3B(0, 255, 0));
                    
                    //cocos2d::log("letter selected %s, %c", letterSelected ? "true" : "false", board.selected.letter);
                    if (!letterSelected) {
                        // first letter selected
                        board.selected = l;
                        letterSelected = true;
                        //cocos2d::log("set selected to %c, %s", board.selected.letter, letterSelected ? "true" : "false");
                    } else if (board.selected != l) {
                        // second selected letter is not the same as first
                        board.letterSwap(l);
                        letterSelected = false;
                        UpdateScore();
                        UpdateMoves();
                    } else {
                        // same letter was selected
                        //cocos2d::log("you selected the same letter %c", board.selected.letter);
                        // set letterSelected to false
                        letterSelected = false;
                        // reset selected color
                        board.selected.label->setColor(cocos2d::Color3B(255, 255, 255));
                        // set selected letter to empty Letter
                        board.selected = Letter();
                    }
                    
                    return true;
                }
            }
        }
        return false;
    };
    
    // unused listeners
    //listener->onTouchMoved = [](Touch* touch, Event* event) { log("touch moved"); };
    //listener->onTouchEnded = [](Touch* touch, Event* event) { log("touch ended"); };
    //listener->onTouchCancelled = [](Touch* touch, Event* event) { log("touch canceled"); };
    
    // The priority of the touch listener is based on the draw order of sprite
    //EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, sprite);
    // Or the priority of the touch listener is a fixed value
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 100);
    
    return true;
}

void Game::menuCallback(Object* pSender) {
    Director::getInstance()->replaceScene(EndGame::createScene());
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
