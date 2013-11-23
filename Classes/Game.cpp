#include "Game.h"
#include "Board.h"

USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // enable touch events
    setTouchEnabled(true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Game::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    Board board = Board(this);
    
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        log("touch began");
        Point location = touch->getLocation();//->getLocationInView();
        // TODO: Detect touches on labels
        for (int i = 0; i < Board::BOARD_SIZE; i++) {
            vector<Letter> row = board.letters[i];
            for (int j = 0; j < Board::BOARD_SIZE; j++) {
                Letter l = row[j];
                if (location.getDistance(l.posn) < 30) {
                    log("touched %c", l.letter);
                    
                    l.label->setColor(cocos2d::Color3B(0, 255, 0));
                    
                    return true;
                }
            }
        }
        return true;
    };
    listener->onTouchMoved = [](Touch* touch, Event* event) { log("touch moved"); };
    listener->onTouchEnded = [](Touch* touch, Event* event) { log("touch ended"); };
    listener->onTouchCancelled = [](Touch* touch, Event* event) { log("touch canceled"); };
    // The priority of the touch listener is based on the draw order of sprite
    //EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, sprite);
    // Or the priority of the touch listener is a fixed value
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 100);
    
    return true;
}


void Game::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
