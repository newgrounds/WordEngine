//
//  EndGame.cpp
//  WordEngine
//
//  Created by Adam Gressen on 12/6/13.
//
//

#include "EndGame.h"
#include "cocos-ext.h"

USING_NS_CC;
using cocos2d::extension::UIListView;

float EndGame::score = 0;
vector<string> EndGame::words = vector<string>();

Scene* EndGame::createScene(float s, vector<string> w) {
    score = s;
    words = w;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndGame::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndGame::init() {
    if ( !Layer::init() ) {
        return false;
    }
    
    // get screen size
    Size screenSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // add a button to start the game
    MenuItemLabel* restartItem = MainMenu::createButton("New Game", CC_CALLBACK_1(EndGame::restartGameCallback, this));
    
    // add a button to exit the app
    MenuItemLabel* menuItem = MainMenu::createButton("Main Menu", CC_CALLBACK_1(EndGame::menuCallback, this));
    
    // position menu items
    restartItem->setPosition(Point(origin.x + (screenSize.width/2) - restartItem->getContentSize().width,
                                 origin.y + restartItem->getContentSize().height));
    menuItem->setPosition(Point(origin.x + (screenSize.width/2) + menuItem->getContentSize().width,
                                origin.y + menuItem->getContentSize().height));
    
    // stringstream to create labels
    stringstream stream;
    
    // display the final score
    stream << "Score: " << score;
    MenuItemLabel* scoreLabel = MainMenu::createLabel(stream.str().c_str());
    stream.str("");
    
    // display the number of words
    stream << "# of words: " << words.size();
    MenuItemLabel* numWordsLabel = MainMenu::createLabel(stream.str().c_str());
    
    // display the words
    //UIListView *listView = UIListView::create();
    //listView->initChildWithDataLength(10);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(scoreLabel, numWordsLabel, restartItem, menuItem, NULL);
    //menu->setPosition(Point::ZERO);
    menu->alignItemsVertically();
    this->addChild(menu, 1);
    
    return true;
}

void EndGame::restartGameCallback(Object* pSender) {
    Director::getInstance()->replaceScene(Game::createScene());
}

void EndGame::menuCallback(Object* pSender) {
    Director::getInstance()->replaceScene(MainMenu::createScene());
}
