package org.cocos2dx.cpp;
/* Created by ahmadrezasy on 10/11/17. */


import org.cocos2dx.lib.Cocos2dxActivity;

import ir.tapsell.sdk.TapsellCocos2D;
import ir.tapsell.sdk.TapsellCocos2DListener;
import ir.tapsell.sdk.TapsellCocos2DModule;
import ir.tapsell.sdk.nativeads.TapsellCocos2DNativeCppListener;

public class Tapsell {
    public static native void onAdShowFinished(String zoneId, String adId, boolean completed, boolean rewarded);
    public static native void onAdAvailable(String zoneId, String adId);
    public static native void onError(String zoneId, String error);
    public static native void onNoAdAvailable(String zoneId);
    public static native void onNoNetwork(String zoneId);
    public static native void onExpiring(String zoneId, String adId);
    public static native void onClosed(String zoneId, String adId);
    public static native void onOpened(String zoneId, String adId);

    public static native void onNativeBannerAdAvailable(String s, String s1, String s2, String s3,
                                                        String s4, String s5, String s6, String s7);
    public static native void onNativeBannerError(String zoneId, String error);
    public static native void onNativeBannerNoAdAvailable(String zoneId);
    public static native void onNativeBannerNoNetwork(String zoneId);

    public static native void onNativeVideoAdAvailable(String s, String s1, String s2, String s3,
                                                        String s4, String s5, String s6);
    public static native void onNativeVideoError(String zoneId, String error);
    public static native void onNativeVideoNoAdAvailable(String zoneId);
    public static native void onNativeVideoNoNetwork(String zoneId);

    private static TapsellCocos2DModule tapsellCocos2DModule = null;
    private static Cocos2dxActivity app = null;
    private TapsellCocos2D tapsellCocos2D = null;

    public static void newInstance(Cocos2dxActivity app) {
        Tapsell.app = app;
        tapsellCocos2DModule = new TapsellCocos2DModule(app);
        Tapsell tapsell = new Tapsell();
        tapsell.initializeTapsell();
    }

    private void initializeTapsell() {
        tapsellCocos2D = TapsellCocos2D.newInstance(new TapsellCocos2DListener() {
            @Override
            public void onAdShowFinished(String zoneId, String adId, boolean completed, boolean rewarded) {
                Tapsell.onAdShowFinished(zoneId, adId, completed, rewarded);
            }

            @Override
            public void onAdAvailable(String zoneId, String adId) {
                Tapsell.onAdAvailable(zoneId, adId);
            }

            @Override
            public void onError(String zoneId, String error) {
                Tapsell.onError(zoneId, error);
            }

            @Override
            public void onNoAdAvailable(String zoneId) {
                Tapsell.onNoAdAvailable(zoneId);
            }

            @Override
            public void onNoNetwork(String zoneId) {
                Tapsell.onNoNetwork(zoneId);
            }

            @Override
            public void onExpiring(String zoneId, String adId) {
                Tapsell.onExpiring(zoneId, adId);
            }

            @Override
            public void onClosed(String zoneId, String adId) {
                Tapsell.onClosed(zoneId, adId);
            }

            @Override
            public void onOpened(String zoneId, String adId) {
                Tapsell.onOpened(zoneId, adId);
            }
        });
    }

    public static void initialize(String appKey) {
        tapsellCocos2DModule.initialize(appKey);
    }

    public static void showAd(final String adId, final boolean back_disabled, final boolean immersive_mode, final int rotation_mode,
                              final boolean showExitDialog) {

        tapsellCocos2DModule.showAd(adId, back_disabled, immersive_mode, rotation_mode,
                showExitDialog);

    }

    public static void requestAd(String zoneId, boolean isCached) {
        tapsellCocos2DModule.requestAd(zoneId, isCached);
    }

    public static void nativeBannerAdShown(String ad_id) {
        tapsellCocos2DModule.nativeBannerAdShown(ad_id, app);
    }

    public static void nativeBannerAdClicked(String ad_id) {
        tapsellCocos2DModule.nativeBannerAdClicked(ad_id, app);
    }

    public static void requestNativeBannerAd(final String zoneId) {
        tapsellCocos2DModule.requestNativeBannerAd(zoneId, app, new TapsellCocos2DNativeCppListener() {
            @Override
            public void onBannerAdAvailable(String s, String s1, String s2, String s3, String s4, String s5, String s6, String s7) {
                Tapsell.onNativeBannerAdAvailable(s, s1, s2, s3, s4, s5, s6, s7);
            }

            @Override
            public void onVideoAdAvailable(String s, String s1, String s2, String s3, String s4, String s5, String s6) {}

            @Override
            public void onError(String s, String s1) {
                Tapsell.onNativeBannerError(s, s1);
            }

            @Override
            public void onNoAdAvailable(String s) {
                Tapsell.onNativeBannerNoAdAvailable(s);
            }

            @Override
            public void onNoNetwork(String s) {
                Tapsell.onNativeBannerNoNetwork(s);
            }
        });
    }

    public static void nativeVideoAdShown(String ad_id) {
        tapsellCocos2DModule.nativeVideoAdShown(ad_id, app);
    }

    public static void nativeVideoAdClicked(String ad_id) {
        tapsellCocos2DModule.nativeVideoAdClicked(ad_id, app);
    }

    public static void requestNativeVideoAd(final String zoneId) {
        tapsellCocos2DModule.requestNativeVideoAd(zoneId, app, new TapsellCocos2DNativeCppListener() {
            @Override
            public void onVideoAdAvailable(String s, String s1, String s2, String s3, String s4, String s5, String s6) {
                Tapsell.onNativeVideoAdAvailable(s, s1, s2, s3, s4, s5, s6);
            }

            @Override
            public void onBannerAdAvailable(String s, String s1, String s2, String s3, String s4, String s5, String s6, String s7) {}

            @Override
            public void onError(String s, String s1) {
                Tapsell.onNativeVideoError(s, s1);
            }

            @Override
            public void onNoAdAvailable(String s) {
                Tapsell.onNativeVideoNoAdAvailable(s);
            }

            @Override
            public void onNoNetwork(String s) {
                Tapsell.onNativeVideoNoNetwork(s);
            }
        });
    }

    public static void setDebugMode(boolean debug) {
        tapsellCocos2DModule.setDebugMode(debug);
    }

    public static boolean isDebugMode() {
        return tapsellCocos2DModule.isDebugMode();
    }

    public static void setAppUserId(String appUserId) {
        tapsellCocos2DModule.setAppUserId(appUserId);
    }

    public static String getAppUserId() {
        return tapsellCocos2DModule.getAppUserId();
    }

    public static void setPermissionHandlerConfig(int permissionHandlerConfig) {
        tapsellCocos2DModule.setPermissionHandlerConfig(permissionHandlerConfig);
    }

    public static String getVersion() {
        return tapsellCocos2DModule.getVersion();
    }

    public static void setMaxAllowedBandwidthUsage(int maxBpsSpeed) {
        tapsellCocos2DModule.setMaxAllowedBandwidthUsage(maxBpsSpeed);
    }

    public static void setMaxAllowedBandwidthUsagePercentage(int maxPercentage) {
        tapsellCocos2DModule.setMaxAllowedBandwidthUsagePercentage(maxPercentage);
    }

    public static void clearBandwidthUsageConstrains() {
        tapsellCocos2DModule.clearBandwidthUsageConstrains();
    }

}
