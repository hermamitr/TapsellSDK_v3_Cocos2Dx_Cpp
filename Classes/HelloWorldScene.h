#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Tapsell.h"

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
