#define ON_AD_SHOW_FINISHED std::function<void(std::string, std::string, bool)>
#define ON_AD_AVAILABLE_CB std::function<void(std::string)>
#define ON_ERROR_CB std::function<void(std::string)>
#define ON_NO_AD_AVAILABLE_CB std::function<void()>
#define ON_NO_NETWORK_CB std::function<void()>
#define ON_EXPIRING_CB std::function<void(std::string)>
#define ON_OPENED_CB std::function<void(std::string)>
#define ON_CLOSED_CB std::function<void(std::string)>

#define ROTATION_LOCKED_PORTRAIT 1
#define ROTATION_LOCKED_LANDSCAPE 2
#define ROTATION_UNLOCKED 3
#define ROTATION_LOCKED_REVERSED_LANDSCAPE 4
#define ROTATION_LOCKED_REVERSED_PORTRAIT 5


class TSTapsell {
public:
    static void initialize(std::string appKey);
    static void setRewardListener(ON_AD_SHOW_FINISHED onAdShowFinished);
    static void requestAd(std::string zoneId, bool isCached,
                          ON_AD_AVAILABLE_CB onAdAvailable,
                          ON_NO_AD_AVAILABLE_CB onNoAdAvailable,
                          ON_ERROR_CB onError,
                          ON_EXPIRING_CB onExpiring);
    
    static void showAd(std::string zoneId, std::string adId, bool back_disabled,
                       bool immersive_mode, int rotation_mode,
                       bool showExitDialog);
    static void showAd(std::string zoneId, std::string adId, bool back_disabled,
                       bool immersive_mode, int rotation_mode,
                       bool showExitDialog, ON_OPENED_CB onOpened,
                       ON_CLOSED_CB onClosed);
    static void setDebugMode(bool debug);
    static bool isDebugMode();
    static void setAppUserId(std::string appUserId);
    static std::string getAppUserId();
    static std::string getVersion();

};
