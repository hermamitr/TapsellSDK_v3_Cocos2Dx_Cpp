#import "TSTapsell.h"
#import "cocos2d.h"
#import <Foundation/Foundation.h>
#import <TapsellSDKv3/TapsellSDKv3.h>
NSMutableDictionary * tapsellAds;

void TSTapsell::initialize(std::string appKey) {
    [Tapsell initializeWithAppKey:[NSString stringWithCString:appKey.c_str()
                                                     encoding:[NSString defaultCStringEncoding]]];
    tapsellAds = [[NSMutableDictionary alloc] init];
}

void TSTapsell::requestAd(std::string zoneId, bool isCached,
                      ON_AD_AVAILABLE_CB onAdAvailable,
                      ON_NO_AD_AVAILABLE_CB onNoAdAvailable,
                      ON_ERROR_CB onError,
                      ON_EXPIRING_CB onExpiring) {
    TSAdRequestOptions* requestOptions = [[TSAdRequestOptions alloc] init];
    NSInteger cacheType = 1;
    if(isCached)
        cacheType = 2;
    [requestOptions setCacheType:(CacheType)cacheType];
    
    [Tapsell requestAdForZone:[NSString stringWithCString:zoneId.c_str()
                                                 encoding:[NSString defaultCStringEncoding]]
                   andOptions:requestOptions
                onAdAvailable:^(TapsellAd *ad){
                    [tapsellAds setObject:ad forKey:ad.getId];
                    onAdAvailable([ad.getId UTF8String]);
                }
                onNoAdAvailable:^{
                    onNoAdAvailable();
                }
                onError:^(NSString* error){
                    onError([error UTF8String]);
                }
                onExpiring:^(TapsellAd* ad){
                    onExpiring([ad.getId UTF8String]);
                }];
}
void TSTapsell::showAd(std::string zoneId, std::string adId, bool back_disabled,
                   bool immersive_mode, int rotation_mode,
                   bool showExitDialog){
    TSAdShowOptions* showOptions = [[TSAdShowOptions alloc] init];
    [showOptions setOrientation:(Orientation)(NSInteger)rotation_mode];
    [showOptions setBackDisabled:back_disabled];
    [showOptions setShowDialoge:showExitDialog];
    
    TapsellAd* ad = tapsellAds[[NSString stringWithCString:adId.c_str()
                                                  encoding:[NSString defaultCStringEncoding]]];
    [ad showWithOptions:showOptions
      andOpenedCallback:^(TapsellAd * _Nullable ad){
          
      }
      andClosedCallback:^(TapsellAd * _Nullable ad){
         
      }];
}
void TSTapsell::showAd(std::string zoneId, std::string adId, bool back_disabled,
                   bool immersive_mode, int rotation_mode,
                   bool showExitDialog, ON_OPENED_CB onOpened,
                   ON_CLOSED_CB onClosed) {
    TSAdShowOptions* showOptions = [[TSAdShowOptions alloc] init];
    [showOptions setOrientation:(Orientation)(NSInteger)rotation_mode];
    [showOptions setBackDisabled:back_disabled];
    [showOptions setShowDialoge:showExitDialog];
    
    TapsellAd* ad = tapsellAds[[NSString stringWithCString:adId.c_str()
                                                  encoding:[NSString defaultCStringEncoding]]];
    [ad showWithOptions:showOptions
      andOpenedCallback:^(TapsellAd * _Nullable ad){
          onOpened([ad.getId UTF8String]);
      }
      andClosedCallback:^(TapsellAd * _Nullable ad){
          onClosed([ad.getId UTF8String]);
      }];
}

void TSTapsell::requestNativeBannerAd(std::string zoneId, ON_NATIVE_BANNER_AD_AVAILABLE_CB onAdAvailable,
                                  ON_NATIVE_BANNER_NO_AD_AVAILABLE_CB onNoAdAvailable,
                                      ON_NATIVE_BANNER_ERROR_CB onError) {
    [Tapsell requestNativeBannerAdForZone:[NSString stringWithCString:zoneId.c_str()
                                                             encoding:[NSString defaultCStringEncoding]] onAdAvailable:^(TSNativeBannerAdWrapper *nativeBannerAd) {
        onAdAvailable([nativeBannerAd.adId UTF8String], [nativeBannerAd.title UTF8String], [nativeBannerAd.htmlDescription UTF8String], [nativeBannerAd.logoUrl UTF8String], [nativeBannerAd.callToActionText UTF8String], [nativeBannerAd.portriatImageUrl UTF8String], [nativeBannerAd.landscapeImageUrl UTF8String]);
    } onNoAdAvailable:^{
        onNoAdAvailable();
    } onError:^(NSString * _Nullable error) {
        onError([error UTF8String]);
    }];
}
void TSTapsell::onNativeBannerAdShown(std::string adId) {
    [Tapsell nativeBannerAdShowWithAdId:[NSString stringWithCString:adId.c_str()
                                                           encoding:[NSString defaultCStringEncoding]]];
}
void TSTapsell::onNativeBannerAdClicked(std::string adId) {
    [Tapsell nativeBannerAdClickedWithAdId:[NSString stringWithCString:adId.c_str()
                                                             encoding:[NSString defaultCStringEncoding]]];
}

void TSTapsell::requestNativeVideoAd(std::string zoneId, ON_NATIVE_VIDEO_AD_AVAILABLE_CB onAdAvailable,
                                 ON_NATIVE_VIDEO_NO_AD_AVAILABLE_CB onNoAdAvailable,
                                     ON_NATIVE_VIDEO_ERROR_CB onError) {
    [Tapsell requestNativeVideoAdForZone:[NSString stringWithCString:zoneId.c_str()
                                                            encoding:[NSString defaultCStringEncoding]] onAdAvailable:^(TSNativeVideoAdWrapper * _Nonnull nativeVideoAd) {
        onAdAvailable([nativeVideoAd.adId UTF8String], [nativeVideoAd.title UTF8String], [nativeVideoAd.htmlDescription UTF8String], [nativeVideoAd.logoUrl UTF8String], [nativeVideoAd.callToActionText UTF8String], [nativeVideoAd.videoUrl UTF8String]);
    } onNoAdAvailable:^{
        onNoAdAvailable();
    } onError:^(NSString * _Nullable error) {
        onError([error UTF8String]);
    }];
}
    
void TSTapsell::onNativeVideoAdShown(std::string adId) {
    [Tapsell nativeVideoAdShowWithAdId:[NSString stringWithCString:adId.c_str()
                                                           encoding:[NSString defaultCStringEncoding]]];
}

void TSTapsell::onNativeVideoAdClicked(std::string adId) {
    [Tapsell nativeVideoAdClickedWithAdId:[NSString stringWithCString:adId.c_str()
                                                              encoding:[NSString defaultCStringEncoding]]];
}

void TSTapsell::setRewardListener(ON_AD_SHOW_FINISHED onAdShowFinished) {
    [Tapsell setAdShowFinishedCallback:^(TapsellAd *ad, BOOL completed) {
        onAdShowFinished([ad.getZoneId UTF8String], [ad.getId UTF8String], completed);
    }];
}
void TSTapsell::setDebugMode(bool debug) {
    [Tapsell setDebugMode:debug];
}
bool TSTapsell::isDebugMode() {
    return [Tapsell isDebugMode];
}
void TSTapsell::setAppUserId(std::string appUserId) {
    [Tapsell setAppUserId:[NSString stringWithCString:appUserId.c_str()
                                             encoding:[NSString defaultCStringEncoding]]];
}

void TSTapsell::requestStandardBannerAd(std::string zoneId, int bannerType,
                                        int horizontalGravity, int verticalGravity) {
    [TSBannerAdView loadAdWithZoneId:[NSString stringWithCString:zoneId.c_str() encoding:[NSString defaultCStringEncoding]] andBannerType:[NSNumber numberWithInteger:bannerType] andHorizGravity:[NSNumber numberWithInteger:horizontalGravity] andVertGravity:[NSNumber numberWithInteger:verticalGravity]];
}

std::string TSTapsell::getAppUserId() {
    return [[Tapsell getAppUserId] UTF8String];
}
std::string TSTapsell::getVersion() {
    return [[Tapsell getVersion] UTF8String];
}
