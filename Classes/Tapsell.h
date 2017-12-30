#ifndef PROJ_ANDROID_STUDIO_TAPSELL_H
#define PROJ_ANDROID_STUDIO_TAPSELL_H

#include <functional>
#include <map>
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#define ON_AD_SHOW_FINISHED std::function<void(std::string, std::string, bool, bool)>
#define ON_AD_AVAILABLE_CB std::function<void(std::string)>
#define ON_ERROR_CB std::function<void(std::string)>
#define ON_NO_AD_AVAILABLE_CB std::function<void()>
#define ON_NO_NETWORK_CB std::function<void()>
#define ON_EXPIRING_CB std::function<void(std::string)>
#define ON_OPENED_CB std::function<void(std::string)>
#define ON_CLOSED_CB std::function<void(std::string)>

#define ON_NATIVE_BANNER_AD_AVAILABLE_CB std::function<void(std::string, std::string, std::string, std::string, std::string, std::string, std::string)>
#define ON_NATIVE_BANNER_ERROR_CB std::function<void(std::string)>
#define ON_NATIVE_BANNER_NO_AD_AVAILABLE_CB std::function<void()>
#define ON_NATIVE_BANNER_NO_NETWORK_CB std::function<void()>

#define ON_NATIVE_VIDEO_AD_AVAILABLE_CB std::function<void(std::string, std::string, std::string, std::string, std::string, std::string)>
#define ON_NATIVE_VIDEO_ERROR_CB std::function<void(std::string)>
#define ON_NATIVE_VIDEO_NO_AD_AVAILABLE_CB std::function<void()>
#define ON_NATIVE_VIDEO_NO_NETWORK_CB std::function<void()>

#define ROTATION_LOCKED_PORTRAIT 1
#define ROTATION_LOCKED_LANDSCAPE 2
#define ROTATION_UNLOCKED 3
#define ROTATION_LOCKED_REVERSED_LANDSCAPE 4
#define ROTATION_LOCKED_REVERSED_PORTRAIT 5

#define BANNER_320x50 1
#define BANNER_320x100 2
#define BANNER_250x250 3
#define BANNER_300x250 4

#define TOP 1
#define BOTTOM 2
#define LEFT 3
#define RIGHT 4
#define CENTER 5

class Tapsell {
public:
    static void initialize(std::string appKey) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "initialize", "(Ljava/lang/String;)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jAppKey = methodInfo.env->NewStringUTF(appKey.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jAppKey);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    static void setRewardListener(ON_AD_SHOW_FINISHED onAdShowFinished) {
        onAdShowFinishedCb = onAdShowFinished;
    }

    static void requestAd(std:: string zoneId, bool isCached, ON_AD_AVAILABLE_CB onAdAvailable,
                          ON_NO_AD_AVAILABLE_CB onNoAdAvailable, ON_NO_NETWORK_CB onNoNetwork,
                          ON_ERROR_CB onError, ON_EXPIRING_CB onExpiring) {
        onAdAvailableCbs[zoneId] = onAdAvailable;
        onErrorCbs[zoneId] = onError;
        onNoAdAvailableCbs[zoneId] = onNoAdAvailable;
        onNoNetworkCbs[zoneId] = onNoNetwork;
        onExpiringCbs[zoneId] = onExpiring;

        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "requestAd", "(Ljava/lang/String;Z)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jZoneId = methodInfo.env->NewStringUTF(zoneId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jZoneId,
                                             isCached);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    static void showAd(std::string zoneId, std::string adId, bool back_disabled,
                       bool immersive_mode, int rotation_mode, bool showExitDialog){
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "showAd", "(Ljava/lang/String;ZZIZ)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jAdId = methodInfo.env->NewStringUTF(adId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,
                                             jAdId, back_disabled, immersive_mode, rotation_mode,
                                             showExitDialog);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    static void showAd(std::string zoneId, std::string adId, bool back_disabled,
                       bool immersive_mode, int rotation_mode, bool showExitDialog,
                       ON_OPENED_CB onOpened, ON_CLOSED_CB onClosed){
        onOpenedCbs[zoneId] = onOpened;
        onClosedCbs[zoneId] = onClosed;
        Tapsell::showAd(zoneId, adId, back_disabled, immersive_mode, rotation_mode, showExitDialog);
    }

    static void requestNativeBannerAd(std::string zoneId, ON_NATIVE_BANNER_AD_AVAILABLE_CB onAdAvailable,
                                      ON_NATIVE_BANNER_NO_AD_AVAILABLE_CB onNoAdAvailable, ON_NATIVE_BANNER_NO_NETWORK_CB onNoNetwork,
                                      ON_NATIVE_BANNER_ERROR_CB onError) {
        onNativeBannerAdAvailableCbs[zoneId] = onAdAvailable;
        onNativeBannerErrorCbs[zoneId] = onError;
        onNativeBannerNoAdAvailableCbs[zoneId] = onNoAdAvailable;
        onNativeBannerNoNetworkCbs[zoneId] = onNoNetwork;

        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "requestNativeBannerAd", "(Ljava/lang/String;)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jZoneId = methodInfo.env->NewStringUTF(zoneId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jZoneId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    static void onNativeBannerAdShown(std::string adId) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "nativeBannerAdShown", "(Ljava/lang/String;)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jAdId = methodInfo.env->NewStringUTF(adId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jAdId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }



    static void onNativeBannerAdClicked(std::string adId) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "nativeBannerAdClicked", "(Ljava/lang/String;)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jAdId = methodInfo.env->NewStringUTF(adId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jAdId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    static void requestNativeVideoAd(std::string zoneId, ON_NATIVE_VIDEO_AD_AVAILABLE_CB onAdAvailable,
                                      ON_NATIVE_VIDEO_NO_AD_AVAILABLE_CB onNoAdAvailable, ON_NATIVE_VIDEO_NO_NETWORK_CB onNoNetwork,
                                      ON_NATIVE_VIDEO_ERROR_CB onError) {
        onNativeVideoAdAvailableCbs[zoneId] = onAdAvailable;
        onNativeVideoErrorCbs[zoneId] = onError;
        onNativeVideoNoAdAvailableCbs[zoneId] = onNoAdAvailable;
        onNativeVideoNoNetworkCbs[zoneId] = onNoNetwork;

        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "requestNativeVideoAd", "(Ljava/lang/String;)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jZoneId = methodInfo.env->NewStringUTF(zoneId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jZoneId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    static void onNativeVideoAdShown(std::string adId) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "nativeVideoAdShown", "(Ljava/lang/String;)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jAdId = methodInfo.env->NewStringUTF(adId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jAdId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }



    static void onNativeVideoAdClicked(std::string adId) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "nativeVideoAdClicked", "(Ljava/lang/String;)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jAdId = methodInfo.env->NewStringUTF(adId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jAdId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    static void requestStandardBannerAd(std::string zoneId, int bannerType,
                                        int horizontalGravity, int verticalGravity) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "requestStandardBannerAd", "(Ljava/lang/String;III)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jAdId = methodInfo.env->NewStringUTF(zoneId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jAdId,
                                             bannerType, horizontalGravity, verticalGravity);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    static void setDebugMode(bool debug) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "setDebugMode", "(Z)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,
                                             debug);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);

    }

    static bool isDebugMode() {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "isDebugMode", "()Z")) {
            CCLOG("METHOD NOT FOUND");
            return false;
        }
        bool mode = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        return mode;
    }
    static void setAppUserId(std::string appUserId) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "setAppUserId", "(Ljava/lang/String;)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        jstring jAppUserId = methodInfo.env->NewStringUTF(appUserId.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,
                                             jAppUserId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    static std::string getAppUserId() {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "getAppUserId", "()Ljava/lang/String;")) {
            CCLOG("METHOD NOT FOUND");
            return "";
        }
        jstring appUserId = (jstring) methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        return cocos2d::JniHelper::jstring2string(appUserId);
    }
    static std::string getVersion() {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "getVersion", "()Ljava/lang/String;")) {
            CCLOG("METHOD NOT FOUND");
            return "";
        }
        jstring version = (jstring) methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        return cocos2d::JniHelper::jstring2string(version);
    }
    static void setPermissionHandlerConfig(int permissionHandlerConfig) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "setPermissionHandlerConfig", "(I)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,
                                             permissionHandlerConfig);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    static void setMaxAllowedBandwidthUsage(int maxBpsSpeed) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "setMaxAllowedBandwidthUsage", "(I)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,
                                             maxBpsSpeed);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    static void setMaxAllowedBandwidthUsagePercentage(int maxPercentage) {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "setMaxAllowedBandwidthUsagePercentage", "(I)V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,
                                             maxPercentage);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    static void clearBandwidthUsageConstrains() {
        cocos2d::JniMethodInfo methodInfo;
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/Tapsell",
                                                     "clearBandwidthUsageConstrains", "()V")) {
            CCLOG("METHOD NOT FOUND");
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }

    static ON_AD_SHOW_FINISHED onAdShowFinishedCb;
    static std::map<std::string, ON_AD_AVAILABLE_CB> onAdAvailableCbs;
    static std::map<std::string, ON_ERROR_CB> onErrorCbs;
    static std::map<std::string, ON_NO_AD_AVAILABLE_CB> onNoAdAvailableCbs;
    static std::map<std::string, ON_NO_NETWORK_CB> onNoNetworkCbs;
    static std::map<std::string, ON_EXPIRING_CB> onExpiringCbs;
    static std::map<std::string, ON_OPENED_CB> onOpenedCbs;
    static std::map<std::string, ON_CLOSED_CB> onClosedCbs;

    static std::map<std::string, ON_NATIVE_BANNER_AD_AVAILABLE_CB> onNativeBannerAdAvailableCbs;
    static std::map<std::string, ON_NATIVE_BANNER_ERROR_CB> onNativeBannerErrorCbs;
    static std::map<std::string, ON_NATIVE_BANNER_NO_AD_AVAILABLE_CB> onNativeBannerNoAdAvailableCbs;
    static std::map<std::string, ON_NATIVE_BANNER_NO_NETWORK_CB> onNativeBannerNoNetworkCbs;

    static std::map<std::string, ON_NATIVE_VIDEO_AD_AVAILABLE_CB> onNativeVideoAdAvailableCbs;
    static std::map<std::string, ON_NATIVE_VIDEO_ERROR_CB> onNativeVideoErrorCbs;
    static std::map<std::string, ON_NATIVE_VIDEO_NO_AD_AVAILABLE_CB> onNativeVideoNoAdAvailableCbs;
    static std::map<std::string, ON_NATIVE_VIDEO_NO_NETWORK_CB> onNativeVideoNoNetworkCbs;
};



#endif //PROJ_ANDROID_STUDIO_TAPSELL_H
