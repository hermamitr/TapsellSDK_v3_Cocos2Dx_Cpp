#include "HelloWorldScene.h"

USING_NS_CC;

const std::string APP_KEY =
        "qjmospqbfarbhodregqecbbnfhcjllkflpbpsmdrtpqkapdeptftldfiapfgbamkhalbij";
const std::string ZONE_ID = "59b4d07d468465281b792cb7";
const std::string NATIVE_BANNER_ZONEID = "59c8a9334684656c504f0e19";
const std::string NATIVE_VIDEO_ZONEID = "59c8ae514684656c504fce40";
const std::string STANDARD_BANNER_ZONEID = "5a44aa6565a77100013d5fb3";
std::string AD_ID = "";
std::string NATIVE_BANNER_AD_ID = "";
std::string NATIVE_VIDEO_AD_ID = "";
std::string nativeMode = "banner";
Label* nativeLabelG;

Scene *HelloWorld::createScene() { return HelloWorld::create(); }

bool HelloWorld::init() {
    if (!Scene::init()) {
        return false;
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Tapsell::initialize(APP_KEY);
    Tapsell::setDebugMode(true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TSTapsell::initialize(APP_KEY);
    TSTapsell::setDebugMode(true);
#endif
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vector<MenuItem *> items;
    MenuItemFont::setFontSize(16);
    auto requestAdBtn = MenuItemFont::create(
            "RequestAd", CC_CALLBACK_1(HelloWorld::requestAdCallback, this));
    auto showAdBtn = MenuItemFont::create(
            "ShowAd", CC_CALLBACK_1(HelloWorld::showAdCallback, this));
    auto requestNativeBannerAd = MenuItemFont::create(
            "RequestNativeBannerAd", CC_CALLBACK_1(HelloWorld::requestNativeBannerCallback, this));
    auto requestNativeVideoAd = MenuItemFont::create(
            "RequestNativeVideoAd", CC_CALLBACK_1(HelloWorld::requestNativeVideoCallback, this));

    requestAdBtn->setFontSize(16);
    showAdBtn->setFontSize(16);
    requestNativeBannerAd->setFontSize(16);
    requestNativeVideoAd->setFontSize(16);
    requestAdBtn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                   visibleSize.height * 6 / 7 + origin.y));
    showAdBtn->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                visibleSize.height * 5 / 7 + origin.y));
    requestNativeBannerAd->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                            visibleSize.height * 4 / 7 + origin.y));
    requestNativeVideoAd->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                            visibleSize.height * 3 / 7 + origin.y));
    items.pushBack(requestAdBtn);
    items.pushBack(showAdBtn);
    items.pushBack(requestNativeBannerAd);
    items.pushBack(requestNativeVideoAd);

    auto menu = Menu::createWithArray(items);
    menu->setPosition(Vec2(origin.x, origin.y));
    this->addChild(menu, 1);

    auto nativeLabel = Label::createWithSystemFont("Native Ad Title", "Arial", 18);
    nativeLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 2 / 7));
    nativeLabelG = nativeLabel;
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        bool touchedTarget = event->getCurrentTarget()->getBoundingBox().containsPoint(this->convertTouchToNodeSpace(touch));
        if (touchedTarget)
            event->getCurrentTarget()->setOpacity(180);
        return touchedTarget;
    };
    listener->onTouchEnded = [&](Touch* touch, Event* event){
        CCLOG("Call To Action Clicked");
        event->getCurrentTarget()->setOpacity(255);
        if (nativeMode == "banner") {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            Tapsell::onNativeBannerAdClicked(NATIVE_BANNER_AD_ID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            TSTapsell::onNativeBannerAdClicked(NATIVE_BANNER_AD_ID);
#endif
        }
        else if (nativeMode == "video") {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            Tapsell::onNativeVideoAdClicked(NATIVE_VIDEO_AD_ID);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            TSTapsell::onNativeVideoAdClicked(NATIVE_VIDEO_AD_ID);
#endif
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, nativeLabel);

    this->addChild(nativeLabel);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Tapsell::setRewardListener(
                               [](std::string zoneId, std::string adId, bool completed, bool rewarded) {
                                   CCLOG("Reward! %d, %d", completed, rewarded);
                               });
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TSTapsell::setRewardListener(
                               [](std::string zoneId, std::string adId, bool rewarded) {
                                   CCLOG("Reward! %d", rewarded);
                               });
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Tapsell::requestStandardBannerAd(STANDARD_BANNER_ZONEID, BANNER_320x50, BOTTOM, CENTER);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TSTapsell::requestStandardBannerAd(STANDARD_BANNER_ZONEID, TSBANNER_320x50, BOTTOM, CENTER);
#endif
    
    return true;
}

void HelloWorld::requestAdCallback(Ref *pSender) {
    CCLOG("RequestAd Clicked");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
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
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TSTapsell::requestAd(ZONE_ID, true, [](std::string adId) {
        CCLOG("onAdAvailable");
        AD_ID = adId;
    }, []() {
        CCLOG("onNoAdAvailable");
    }, [](std::string error) {
        CCLOG("onError: %s", error.c_str());
    }, [](std::string adId) {
        CCLOG("onExpiring");
    });
#endif
    
}

void HelloWorld::showAdCallback(Ref *pSender) {
    CCLOG("ShowAd Clicked");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Tapsell::showAd(ZONE_ID, AD_ID, false, false, ROTATION_UNLOCKED, true,
                    [](std::string adId) {
                        CCLOG("onOpened");
                    },
                    [](std::string adId) {
                        CCLOG("onClosed");
                    });
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TSTapsell::showAd(ZONE_ID, AD_ID, false, false, ROTATION_UNLOCKED, true,
                    [](std::string adId) {
                        CCLOG("onOpened");
                    },
                    [](std::string adId) {
                        CCLOG("onClosed");
                    });
#endif
    
}

void HelloWorld::requestNativeBannerCallback(Ref *pSender) {
    CCLOG("RequestNativeBannerAd Clicked");
    nativeMode = "banner";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Tapsell::requestNativeBannerAd(NATIVE_BANNER_ZONEID, [](std::string adId,std::string title, std::string description, std::string iconUrl,
                                                            std::string ctaText, std::string portraitUrl, std::string landscapeUrl){
        CCLOG("onNativeBannerAdAvailable: adId: %s title: %s description: %s iconUrl: %s ctaText: %s portraitUrl: %s landscape: %s", adId.c_str(), title.c_str(), description.c_str(), iconUrl.c_str(),
              ctaText.c_str(), portraitUrl.c_str(), landscapeUrl.c_str());
        nativeLabelG->setString(title.c_str());
        NATIVE_BANNER_AD_ID = adId;
        Tapsell::onNativeBannerAdShown(adId);
    }, [](){
        CCLOG("onNoNativeBannerAdAvailable");
    }, [](){
        CCLOG("onNoNetwork");
    }, [](std::string error) {
        CCLOG("onError: %s", error.c_str());
    });
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TSTapsell::requestNativeBannerAd(NATIVE_BANNER_ZONEID, [](std::string adId,std::string title, std::string description, std::string iconUrl,
                                                            std::string ctaText, std::string portraitUrl, std::string landscapeUrl){
        CCLOG("onNativeBannerAdAvailable: adId: %s title: %s description: %s iconUrl: %s ctaText: %s portraitUrl: %s landscape: %s", adId.c_str(), title.c_str(), description.c_str(), iconUrl.c_str(),
              ctaText.c_str(), portraitUrl.c_str(), landscapeUrl.c_str());
        nativeLabelG->setString(title.c_str());
        NATIVE_BANNER_AD_ID = adId;
        TSTapsell::onNativeBannerAdShown(adId);
    }, [](){
        CCLOG("onNoNativeBannerAdAvailable");
    }, [](std::string error) {
        CCLOG("onError: %s", error.c_str());
    });
#endif
}

void HelloWorld::requestNativeVideoCallback(Ref *pSender) {
    CCLOG("RequestNativeVideoAd Clicked");
    nativeMode = "video";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Tapsell::requestNativeVideoAd(NATIVE_VIDEO_ZONEID, [](std::string adId,std::string title, std::string description, std::string iconUrl,
                                                          std::string ctaText, std::string videoUrl){
        CCLOG("onNativeVideoAdAvailable: adId: %s title: %s description: %s iconUrl: %s ctaText: %s videoUrl: %s", adId.c_str(), title.c_str(), description.c_str(), iconUrl.c_str(),
              ctaText.c_str(), videoUrl.c_str());
        nativeLabelG->setString(title.c_str());
        NATIVE_VIDEO_AD_ID = adId;
        Tapsell::onNativeVideoAdShown(adId);
    }, [](){
        CCLOG("onNoNativeVideoAdAvailable");
    }, [](){
        CCLOG("onNoNetwork");
    }, [](std::string error) {
        CCLOG("onError: %s", error.c_str());
    });
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    TSTapsell::requestNativeVideoAd(NATIVE_VIDEO_ZONEID, [](std::string adId,std::string title, std::string description, std::string iconUrl,
                                                          std::string ctaText, std::string videoUrl){
        CCLOG("onNativeVideoAdAvailable: adId: %s title: %s description: %s iconUrl: %s ctaText: %s videoUrl: %s", adId.c_str(), title.c_str(), description.c_str(), iconUrl.c_str(),
              ctaText.c_str(), videoUrl.c_str());
        nativeLabelG->setString(title.c_str());
        NATIVE_VIDEO_AD_ID = adId;
        TSTapsell::onNativeVideoAdShown(adId);
    }, [](){
        CCLOG("onNoNativeVideoAdAvailable");
    }, [](std::string error) {
        CCLOG("onError: %s", error.c_str());
    });
#endif
}
