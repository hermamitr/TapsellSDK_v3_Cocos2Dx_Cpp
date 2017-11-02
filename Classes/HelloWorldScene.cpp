#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const std::string APP_KEY =
        "rashssjnjiaeqqeihgjdsihajkbkqgeqqdoftpafmlcoofdflejgmttlercbsdfbnjnjqs";
const std::string ZONE_ID = "586e4ed1bc5c28712bd8d50c";
std::string AD_ID = "";

Scene *HelloWorld::createScene() {
    return HelloWorld::create();
}


bool HelloWorld::init() {

    if (!Scene::init()) {
        return false;
    }


#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    TSTapsell::setDebugMode(false);
    TSTapsell::initialize(APP_KEY);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    Tapsell::initialize(APP_KEY);
    Tapsell::setDebugMode(true);
#endif


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vector<MenuItem *> items;
    auto requestAdBtn = MenuItemFont::create(
            "RequestAd", CC_CALLBACK_1(HelloWorld::requestAdCallback, this));
    auto showAdBtn = MenuItemFont::create(
            "ShowAd", CC_CALLBACK_1(HelloWorld::showAdCallback, this));

    requestAdBtn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                   visibleSize.height * 2 / 3 + origin.y));
    showAdBtn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                visibleSize.height / 3 + origin.y));

    items.pushBack(requestAdBtn);
    items.pushBack(showAdBtn);

    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2(origin.x, origin.y));
    this->addChild(menu, 1);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    TSTapsell::setRewardListener(
                                 [](std::string zoneId, std::string adId, bool completed) {
                                     CCLOG("Reward! %d", completed);
                                 });
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
                                 Tapsell::setRewardListener(
            [](std::string zoneId, std::string adId, bool completed, bool rewarded) {
                CCLOG("Reward! %d, %d", completed, rewarded);
            });
#endif

    return true;
}


void HelloWorld::requestAdCallback(Ref *pSender) {
    CCLOG("RequestAd Clicked");
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    TSTapsell::requestAd(
                         ZONE_ID, true,
                         [](std::string adId) {
                             CCLOG("onAdAvailable");
                             AD_ID = adId;
                         },
                         []() { CCLOG("onNoAdAvailable"); },
                         [](std::string error) { CCLOG("onError: %s", error.c_str()); },
                         [](std::string adId) { CCLOG("onExpiring"); });
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    Tapsell::requestAd(ZONE_ID, true, [](std::string adId) {
        CCLOG("onAdAvailable");
        AD_ID = adId;
    }, []() {
        CCLOG("onNoAdAvailable");
    }, []() {
        CCLOG("onNoNetwork");
    }, [](std::string error) {
        CCLOG("onError: %s", error.c_str());
    }, [](std::string adId) {
        CCLOG("onExpiring");
    });
#endif

}

void HelloWorld::showAdCallback(Ref *pSender) {
    CCLOG("ShowAd Clicked");
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    TSTapsell::showAd(ZONE_ID, AD_ID, false, false, ROTATION_UNLOCKED, true,
                      [](std::string adId) { CCLOG("onOpened"); },
                      [](std::string adId) { CCLOG("onClosed"); });
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    Tapsell::showAd(ZONE_ID, AD_ID, false, false, ROTATION_UNLOCKED, true,
        [](std::string adId) {
            CCLOG("onOpened");
        },
        [](std::string adId) {
            CCLOG("onClosed");
        });
#endif

}
