#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Tapsell.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "TSTapsell.h"
#endif


class HelloWorld : public cocos2d::Scene {
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    void requestAdCallback(cocos2d::Ref *pSender);
    void showAdCallback(cocos2d::Ref *pSender);
    void requestNativeBannerCallback(cocos2d::Ref *pSender);
    void requestNativeVideoCallback(cocos2d::Ref *pSender);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
