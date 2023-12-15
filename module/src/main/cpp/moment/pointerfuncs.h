// PATTERN SCANNING IS FOR THE WEAK!!!! 🗣️🗣️🗣️

#include "classFinder.h"

#define DEFINE_FUNC(name, return_type, args) \
        typedef return_type(*name##_ptr)args; \
        inline name##_ptr name

#define DECLARE_FUNC(name) name = (name##_ptr)

struct AnalyticsParams {
    int enum1;
    int enum2;
    int enum3;
    int enum4;
    int enum5;
    int enum6;
    int enum7;
    bool boolean1;
    void* klass1;
    int enum8;
    bool boolean2;
    int enum9;
    void* klass2;
    bool boolean3;
    int enum10;
    int integer1;
};

DEFINE_FUNC(Transform$get_position, Vector3, (void* instance));
DEFINE_FUNC(Transform$set_position, void, (void* instance, Vector3 pos));
DEFINE_FUNC(Transform$lookAt, void, (void* instance, void* transform));
DEFINE_FUNC(Component$get_transform, void*, (void* instance));
DEFINE_FUNC(Component$get_gameObject, void*, (void* instance));

DEFINE_FUNC(DamageTarget, void, (void *x, void *target, float dmg, void *hitCollider, Vector3 dmgPos, Il2CppString *wepName, int typeDead, int typeKill));
DEFINE_FUNC(GetPlayers, monoList<void **>*, (void* x));

DEFINE_FUNC(WebInstance, void*, ());
DEFINE_FUNC(AddCurrency, void, (void* instance, monoString* curName, int num, int num2, bool b1, bool b2, AnalyticsParams params));

// Stolen from zygisk 2 for the funny
DEFINE_FUNC(UpdateExperience, void, (void* instance, int experience, int obtaincause));
DEFINE_FUNC(UpdateLevel, void, (void* instance, int level));

DEFINE_FUNC(UpgradeV8Constructor, void*, (void* obj, int level, int ItemRarity));
DEFINE_FUNC(AddWeapon, void, (void* instance, monoString* name, int num, bool idfk1, bool idfk2, void* WeaponUpgradeV8, AnalyticsParams params));
DEFINE_FUNC(ProvideGadget, void, (monoString* name, int num));

DEFINE_FUNC(SendChat, void, (void* obj, monoString* text, bool isClan, monoString* logoid));

DEFINE_FUNC(get_UTF8, void*, ());
DEFINE_FUNC(Encoding$GetString, monoString*, (void* instance, void* bytes));
DEFINE_FUNC(Encoding$GetBytes, void*, (void* instance, Il2CppString* str));

DEFINE_FUNC(RPC, void, (void* instance, int eventEnum, int photonTarget, Il2CppArray* param));
DEFINE_FUNC(PhotonViewIsMine, bool, (void* instance));
DEFINE_FUNC(GetPixelViewID, int, (void* instance));

DEFINE_FUNC(AddWear, void, (int enumerator, monoString* item));
DEFINE_FUNC(BuyArmor, void, (void* instance, int id, int level, monoString* reason, AnalyticsParams params));
DEFINE_FUNC(AddRoyale, void, (monoString* item, bool idfk, AnalyticsParams params));
DEFINE_FUNC(WearIndex, int, (monoString* str));

DEFINE_FUNC(SpawnPrefab, void*, (monoString* prefabName, Vector3 pos, Quaternion rot, uint8_t byte));
DEFINE_FUNC(DestroyPlayer, void, (void* player));
DEFINE_FUNC(Object$Destroy, void, (void* instance));
DEFINE_FUNC(PhotonNetwork_playerListothers, monoArray<void**>*, ());

DEFINE_FUNC(SetPlayerSpeed, void, (void *instance, void *target, float duration, float power));

DEFINE_FUNC(_Shot, void, (void* x));
DEFINE_FUNC(ShootS, void, (void* x));

DEFINE_FUNC(SkipTraining, void, (void* x));

DEFINE_FUNC(GetPlayerWeapons, monoList<void **> *, (void* instance));
DEFINE_FUNC(SetClipAmmo, void, (void* instance, int amount));
DEFINE_FUNC(SetStoredAmmo, void, (void* instance, int amount));

DEFINE_FUNC(GetDeviceUniqueIdentifier, monoString*, ());
DEFINE_FUNC(GetPlayerID, monoString*, ());
DEFINE_FUNC(GetPlayerNickname, monoString*, ());

DEFINE_FUNC(OpenURL, void, (monoString* url));

DEFINE_FUNC(SetXrayShader, void, (void* x, bool active));

DEFINE_FUNC(OpenKeyboard, void*, (monoString* text, uint64_t TouchScreenKeyboardType, bool autocorrection, bool multiline));
DEFINE_FUNC(KeyboardGetText, monoString*, (void* keyboardPtr));

DEFINE_FUNC(GetPlayerByOwnerID, void*, (int ownerId));

DEFINE_FUNC(AddPet, void, (monoString* petString, int idfk));

void Pointers() {

    LOG_INFO("Initializing pointer functions");

    LOG_INFO("Getting Classes for pointer functions");

    Il2CppClass *Encoding = GET_CLASS("Encoding");

    Il2CppClass *Transform = GET_CLASS("Transform");
    Il2CppClass *Component = GET_CLASS("Component");

    Il2CppClass *WeaponManager = GET_CLASS("WeaponManager");
    Il2CppClass *NetworkStartTable = GET_CLASS("NetworkStartTable");
    Il2CppClass *PlayerMoveC = GET_CLASS("Player_move_c");
    Il2CppClass *ProgressUpdater = GET_CLASS("ProgressUpdater");
    Il2CppClass *WearClass = GET_CLASS("WearClass");
    Il2CppClass *RoyaleClass = GET_CLASS("RoyaleCustomizationItemsManager");

    LOG_INFO("Getting Classes done");

    LOG_INFO("Being declaring pointer functions");

    SignatureCondition Object$DestroyC {"public static", "Void", "Destroy", {"Object"}};
    DECLARE_FUNC(Object$Destroy) GetMethodPointer(GET_CLASS("Object"), Object$DestroyC);

    DECLARE_FUNC(Transform$lookAt) GetMethodPointerFromName(Transform, "LookAt");
    DECLARE_FUNC(Transform$get_position) GetMethodPointerFromName(Transform, "get_position");
    DECLARE_FUNC(Transform$set_position) GetMethodPointerFromName(Transform, "set_position");

    DECLARE_FUNC(Component$get_transform) GetMethodPointerFromName(Component, "get_transform");
    DECLARE_FUNC(Component$get_gameObject) GetMethodPointerFromName(Component, "get_gameObject");

    DECLARE_FUNC(get_UTF8) GetMethodPointerFromName(Encoding, "get_UTF8");

    DECLARE_FUNC(GetDeviceUniqueIdentifier) GetMethodPointerFromName(GET_CLASS("SystemInfo"), "GetDeviceUniqueIdentifier");
    DECLARE_FUNC(GetPlayerID) GetMethodPointerFromIndex(GET_CLASS("AccountCreated"), 0x2);
    DECLARE_FUNC(GetPlayerNickname) GetMethodPointerFromIndex(GET_CLASS("ProfileController"), 0x34);

    DECLARE_FUNC(OpenURL) GetMethodPointerFromName(GET_CLASS("Application"), "OpenURL");

    SignatureCondition DamageTargetC{"internal","Void",nullptr,{"GameObject", "Single", "Collider", "Vector3", "String", "ENUM", "ENUM"}};
    DECLARE_FUNC(DamageTarget) GetMethodPointer(PlayerMoveC, DamageTargetC);

    SignatureCondition GetPlayersC{"internal","Void",nullptr,{"DungeonSpawnPoint"}};
    DECLARE_FUNC(GetPlayers) GetMethodPointer(NetworkStartTable, GetPlayersC, 19);

    SignatureCondition SendChatC {"public","Void","SendChat",{"String", "Boolean", "String"}};
    DECLARE_FUNC(SendChat) GetMethodPointer(PlayerMoveC, SendChatC);

    SignatureCondition WebInstanceC {"internal","Void",nullptr,{"Dictionary`2", "Int32"}};
    DECLARE_FUNC(WebInstance) GetMethodPointer(ProgressUpdater, WebInstanceC, 5);

    static SignatureCondition AddCurrencyC {"internal", "Void", nullptr, {"String", "Int32", "ENUM", "Boolean", "Boolean", nullptr}};
    DECLARE_FUNC(AddCurrency) GetMethodPointer(ProgressUpdater, AddCurrencyC);

    static SignatureCondition UpgradeV8ConstructorC {"internal", "Void", ".ctor", {"Int32", "ENUM"}};
    DECLARE_FUNC(UpgradeV8Constructor) GetMethodPointer(GET_CLASS("WeaponUpgradeV8"), UpgradeV8ConstructorC);

    static SignatureCondition AddWeaponC {"internal", "Void", nullptr, {"String", "ENUM", "Boolean", "Boolean", nullptr, nullptr}};
    DECLARE_FUNC(AddWeapon) GetMethodPointer(WeaponManager, AddWeaponC);

    static SignatureCondition GetPlayerWeaponsC {"internal", "Void", nullptr, {nullptr, "Boolean", "Boolean"}};
    DECLARE_FUNC(GetPlayerWeapons) GetMethodPointer(WeaponManager, GetPlayerWeaponsC, 5);

    static SignatureCondition ProivedGadgetC {"internal static","Void",nullptr,{"String", "Int32"}};
    DECLARE_FUNC(ProvideGadget) GetMethodPointer(GET_CLASS("GadgetProgress"), ProivedGadgetC);

    static SignatureCondition Encoding$GetBytesC {"public virtual", "Byte[]", "GetBytes", {"String"}};
    DECLARE_FUNC(Encoding$GetBytes) GetMethodPointer(Encoding, Encoding$GetBytesC);

    static SignatureCondition Encoding$GetStringC {"public virtual", "String", "GetString", {"Byte[]"}};
    DECLARE_FUNC(Encoding$GetString) GetMethodPointer(Encoding, Encoding$GetStringC);

    static SignatureCondition RPCC {"internal", "Void", nullptr, {"ENUM", "ENUM", "Object[]"}};
    DECLARE_FUNC(RPC) GetMethodPointer(GET_CLASS("PhotonView"), RPCC);

    DECLARE_FUNC(GetPixelViewID) GetMethodPointerFromName(GET_CLASS("PixelView"), "get_viewID");
    DECLARE_FUNC(PhotonViewIsMine) GetMethodPointerFromName(GET_CLASS("PhotonView"), "get_isMine");

    static SignatureCondition KillRateObjectC {"internal","Void",nullptr,{"KillRateObject"}};

    DECLARE_FUNC(UpdateExperience) GetMethodPointer(ProgressUpdater, KillRateObjectC, 3);
    DECLARE_FUNC(UpdateLevel) GetMethodPointer(ProgressUpdater, KillRateObjectC, 2);

    static SignatureCondition BuyArmorC {"internal", "Void", nullptr, {"Int32", "Int32", "String", nullptr}};
    DECLARE_FUNC(BuyArmor) GetMethodPointer(ProgressUpdater, BuyArmorC);

    static SignatureCondition AddWearC {"internal static", "Void", nullptr, {"ENUM", "String"}};
    DECLARE_FUNC(AddWear) GetMethodPointer(WearClass, AddWearC);

    static SignatureCondition WearIndexC {"internal static", "Int32", nullptr, {"String"}};
    DECLARE_FUNC(WearIndex) GetMethodPointer(WearClass, WearIndexC);

    static SignatureCondition SpawnPrefabC {"public static", "GameObject", nullptr, {"String", "Vector3", "Quaternion", "Byte"}};
    DECLARE_FUNC(SpawnPrefab) GetMethodPointer(GET_CLASS("PhotonNetwork"), SpawnPrefabC);

    static SignatureCondition DestroyPlayerC {"public static", "Void", "Destroy", {"GameObject"}};
    DECLARE_FUNC(DestroyPlayer) GetMethodPointer(GET_CLASS("PhotonNetwork"), DestroyPlayerC, 1);

    static SignatureCondition PhotonNetwork_playerListothersC {"public static", "ServerConnection", nullptr, {}};
    DECLARE_FUNC(PhotonNetwork_playerListothers) GetMethodPointer(GET_CLASS("PhotonNetwork"), PhotonNetwork_playerListothersC, 9);

    static SignatureCondition _ShotC {"private", "IEnumerator", nullptr, {"Int32", "Animation", nullptr}};
    DECLARE_FUNC(_Shot) GetMethodPointer(PlayerMoveC, _ShotC, 2);

    static SignatureCondition ShootSC {"internal", "Boolean", nullptr, {"WeaponSounds", "Collider", "Vector3"}};
    DECLARE_FUNC(ShootS) GetMethodPointer(PlayerMoveC, ShootSC, -3);

    static SignatureCondition SkipTrainingC {"public", "Void", ".ctor", {}};
    DECLARE_FUNC(SkipTraining) GetMethodPointer(GET_CLASS("TrainingController"), SkipTrainingC, 3);

    static SignatureCondition AddRoyaleC {"internal static", "Void", nullptr, {"String", "Boolean", nullptr}};
    DECLARE_FUNC(AddRoyale) GetMethodPointerFromIndex(RoyaleClass, 0x1e);//(il2cpp_base + 0x3de4434);//GetMethodPointer(GET_CLASS("RoyaleCustomizationItemsManager"), AddWearC);

    DECLARE_FUNC(SetStoredAmmo) GetMethodPointerFromIndex(GET_CLASS("WeaponW"), 0x3);
    DECLARE_FUNC(SetClipAmmo) GetMethodPointerFromIndex(GET_CLASS("WeaponW"), 0x5);

    static SignatureCondition SetXrayShaderC {"internal", "Void", nullptr, {"Boolean", "ENUM"}};
    DECLARE_FUNC(SetXrayShader) GetMethodPointer(PlayerMoveC, SetXrayShaderC, 1);

    static SignatureCondition OpenKeyboardC {"public static", "TouchScreenKeyboard", "Open", {"String", "ENUM", "Boolean", "Boolean"}};
    DECLARE_FUNC(OpenKeyboard) GetMethodPointer(GET_CLASS("TouchScreenKeyboard"), OpenKeyboardC);
    DECLARE_FUNC(KeyboardGetText) GetMethodPointerFromName(GET_CLASS("TouchScreenKeyboard"), "get_text");

    static SignatureCondition AddPetC {"internal static", "Void", nullptr, {"String", "Int32"}};
    DECLARE_FUNC(AddPet) GetMethodPointer(GET_CLASS("NiggerObfuscatedClass"), AddPetC);

    LOG_INFO("Done");
}
