//
//  EndGame.cpp
//  WordEngine
//
//  Created by Adam Gressen on 12/6/13.
//
//

#include "EndGame.h"
#include "Letter.h"

USING_NS_CC;
USING_NS_CC_EXT;

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
    scoreLabel->setPosition(screenSize.width/2, screenSize.height - scoreLabel->getContentSize().height/2 - Letter::PADDING);
    
    // clear the stream
    stream.str("");
    
    // display the number of words
    stream << "# of words: " << words.size();
    MenuItemLabel* numWordsLabel = MainMenu::createLabel(stream.str().c_str());
    numWordsLabel->setPosition(screenSize.width/2, scoreLabel->getPositionY() - numWordsLabel->getContentSize().height/2 - Letter::PADDING);
    
    // create listview to display the words
    UIListView *listView = UIListView::create();
    // set the size of the list for the listview
    listView->initChildWithDataLength(words.size());
    // set the listview's physical size
    listView->setSize(Size(screenSize.width, screenSize.height));
    // set the z-order of the listview
    //listView->setZOrder(100);
    // set the listview bg color
    //listView->setBackGroundColor(cocos2d::Color3B(50, 50, 50));
    
    // set initial label position
    Point labPosn = Point(screenSize.width/2, numWordsLabel->getPositionY() - numWordsLabel->getContentSize().height - Letter::PADDING);
    for (int i = 0; i < words.size(); i++) {
        UILabel* lab = UILabel::create();
        lab->setFontSize(28);
        lab->setText(words[i].c_str());
        lab->setColor(cocos2d::Color3B(255, 255, 255));
        lab->setZOrder(100);
        lab->setPosition(labPosn);
        listView->addChild(lab);
        
        // update label position for the next label
        labPosn = Point(labPosn.x, labPosn.y - lab->getContentSize().height);
    }
    
    // create UILayer to hold the listview
    UILayer* labelLayer = UILayer::create();
    labelLayer->init();
    labelLayer->addWidget(listView);
    this->addChild(labelLayer, 100);
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(scoreLabel, numWordsLabel, restartItem, menuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void EndGame::restartGameCallback(Object* pSender) {
    Director::getInstance()->replaceScene(Game::createScene());
}

void EndGame::menuCallback(Object* pSender) {
    Director::getInstance()->replaceScene(MainMenu::createScene());
}
