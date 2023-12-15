// PATTERN SCANNING IS FOR THE WEAK!!!! 🗣️🗣️🗣️

#define REG_CLASS_NAMECHECK(klass, name)  if(NAME_CHECK(klass, name)) { REG_CLASS(klass, name); }
#define NAME_CHECK(klass, name) strcmp(il2cpp_class_get_name(klass), name) == 0
#define CHECK_CLASSIZE(klass, size) il2cpp_class_get_data_size(klass) == size
#define NAMESPACE_CHECK(klass, namespaze) strcmp(il2cpp_class_get_namespace(klass), namespaze) == 0

// if dev added new field everything goes rip
FieldPattern ProgressUpdaterPattern {"List`1", "List`1", "String", "String", "String", nullptr, "Int32", "Int32", "Int32", "Int32", "String", "String", "String", "String", "String", "String", "String", "String", "String", "Action", "Action", "Action", "Action", "Boolean", "Boolean", "String", "String", "Boolean", "String", "Queue`1", "List`1", "String", "List`1", "Dictionary`2", "Dictionary`2", nullptr, "String", "Boolean", "Int32", "String", "Boolean", "String", "String", "Boolean", "String", "Dictionary`2", "List`1", "String", "String", "Action`1", "Action`1", "Dictionary`2", "List`1", "Dictionary`2", "Dictionary`2", "Int32", "Int32", "Int32", "Int32", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "Dictionary`2", "List`1", "List`1", "Int32", "Int32", "Dictionary`2", "List`1", "Coroutine", "UInt32"};
FieldPattern GadgetProgressPattern {nullptr, nullptr, nullptr, "Action`1"};
FieldPattern PhotonNetworkPattern {"String", "String", "PhotonHandler", nullptr, "Int32", "Int32", "String", "ServerSettings", "Boolean", "PhotonLogLevel", "List`1", "Single", "Single", "Single", "Boolean", "Boolean", "Dictionary`2", "HashSet`1", "HashSet`1", "Type", "Boolean", "Boolean", nullptr, "Int32", "Boolean", "Boolean", "Int32", "Int32", "Boolean", nullptr, "Boolean", "Stopwatch", "Single", "Boolean", nullptr, "Int32", "Int32", "List`1"};
FieldPattern PhotonPlayerPattern {"Int32", "String", "String", "Boolean", "Boolean", "Hashtable", "Object"};
FieldPattern ItemModulePattern {"Action", "Lazy`1", "Nullable`1", "Texture", "String", "String", "String", "String"};
FieldPattern WeaponSkinManagerPattern {"Single", "String", "Comparison`1", "Dictionary`2", "Dictionary`2", "Dictionary`2", "Action`3", "Action`2", "Dictionary`2", "List`1", "List`1"};
FieldPattern WeaponSkinIdkPattern {"Action", "String", "String", "String", "String", "List`1", "Boolean", "Dictionary`2"};
FieldPattern FreeBundle1Pattern {"LobbyItemsBundle", "Nullable`1", "LobbyItemSlot", "String", "String", "String", "Int32", "String[]", "LobbyItemBuff[]", "LobbyItemLockInfo[]", "Boolean", "String"};
FieldPattern WearClassPattern {"String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "String", "List`1", "HashSet`1", "List`1", "String", "String", "String", "String", "String", "List`1", "Dictionary`2", "Dictionary`2", "Dictionary`2", "Int32", "WearScriptableObject_GENERATED", "Action"};
FieldPattern RoyaleClassPattern {"String", "String", "String", "String", "String", "String", "String", "String", "String", "RoyaleScriptableObject_GENERATED", "Action`1", "Action`1", "Action`1", "Action`1", "Action`1", "Dictionary`2"};
FieldPattern WeaponUpgradeV8Pattern {"Int32", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ItemRarity"};
FieldPattern WeaponWPattern {nullptr, nullptr, "ItemRecord", nullptr, "Int32", "Int32[]", "Boolean", "Boolean", "Boolean"};
FieldPattern AccountCreatedPattern {"String", "Int32", "String", "Boolean", "Boolean", "Nullable`1", "Boolean", "String", "String", "Action"};
FieldPattern SwearingClassPattern {"String", "String", "RegexOptions", "String[]", "String[]", "String[]", "String[]", "Boolean"};
FieldPattern PlayerListClassPattern {"List`1", "List`1", "List`1", "List`1", "List`1", "List`1", "List`1", "List`1", "Dictionary`2", "Dictionary`2", "Dictionary`2", "Dictionary`2", "Dictionary`2", "List`1", "Dictionary`2", "List`1", "Dictionary`2", "HashSet`1"};
FieldPattern NiggerObfuscatedClassPattern {"Int32", "Action`2", "Action`1", "Action`1"};

void CorlibLoad(Il2CppClass* klass) {
    if(NAMESPACE_CHECK(klass, "System.Text")) {
        REG_CLASS_NAMECHECK(klass, "Encoding");
    }
}

void UnityCoreLoad(Il2CppClass* klass) {
    if(NAMESPACE_CHECK(klass, "UnityEngine")) {
        REG_CLASS_NAMECHECK(klass, "Component");
        REG_CLASS_NAMECHECK(klass, "Transform");
        REG_CLASS_NAMECHECK(klass, "Object");
        REG_CLASS_NAMECHECK(klass, "SystemInfo");
        REG_CLASS_NAMECHECK(klass, "Application");
        REG_CLASS_NAMECHECK(klass, "TouchScreenKeyboard");
    }
}

void ObfuscatedLoad(Il2CppClass* klass) {

    // Progress
    if(NAMESPACE_CHECK(klass, "Progress")) {

        // ProgressUpdater
        if(CheckContentCount(klass, {82, 100}, {478, 500}) && CheckFieldPattern(klass, ProgressUpdaterPattern) == 1.0) {
            REG_CLASS(klass, "ProgressUpdater");
        }
    }

    if(NAMESPACE_CHECK(klass, "")) {

        if(CheckContentCount(klass, {4, 4}, {25, 25}) && CheckFieldPattern(klass, GadgetProgressPattern) == 1.0) {
            REG_CLASS(klass, "GadgetProgress");
        }
        if(CheckContentCount(klass, {11,11}, {118, 118}) && CheckFieldPattern(klass, WeaponSkinManagerPattern) == 1.0) {
            REG_CLASS(klass, "WeaponSkinManager");
        }
        if(CheckContentCount(klass, {38, 38}, {148, 148}) && CheckFieldPattern(klass, PhotonNetworkPattern) == 1.0) {
            REG_CLASS(klass, "PhotonNetwork");
        }
        if(CheckContentCount(klass, {7, 7}, {40, 40}) && CheckFieldPattern(klass, PhotonPlayerPattern) == 1.0) {
            REG_CLASS(klass, "PhotonPlayer");
        }
        if(CheckContentCount(klass, {12, 12}, {33, 33}) && CheckFieldPattern(klass, FreeBundle1Pattern) == 1.0) {
            REG_CLASS(klass, "FreeBundle1");
        }
        if(CheckContentCount(klass, {186, 186}, {64, 64}) && CheckFieldPattern(klass, WearClassPattern) == 1.0) {
            REG_CLASS(klass, "WearClass");
        }
        if(CheckContentCount(klass, {16, 16}, {48, 48}) && CheckFieldPattern(klass, RoyaleClassPattern) == 1.0) {
            REG_CLASS(klass, "RoyaleCustomizationItemsManager");
        }
        if(CheckContentCount(klass, {9, 9}, {12, 12}) && CheckFieldPattern(klass, WeaponUpgradeV8Pattern) == 1.0) {
            REG_CLASS(klass, "WeaponUpgradeV8");
        }
        if(CheckContentCount(klass, {9,9}, {12, 12}) && CheckFieldPattern(klass, WeaponWPattern) == 1.0) {
            REG_CLASS(klass, "WeaponW");
        }
        if(CheckContentCount(klass, {10,10}, {10, 10}) && CheckFieldPattern(klass, AccountCreatedPattern) == 1.0) {
            REG_CLASS(klass, "AccountCreated");
        }
        if(CheckContentCount(klass, {8, 8}, {5, 5}) && CheckFieldPattern(klass, SwearingClassPattern) == 1.0) {
            REG_CLASS(klass, "SwearingClass");
        }
        if(CheckContentCount(klass, {17, 17}, {30, 30}) && CheckFieldPattern(klass, PlayerListClassPattern) == 1.0) {
            REG_CLASS(klass, "PlayerListClass");
        }


        REG_CLASS_NAMECHECK(klass, "FirstPersonControlSharp");
        REG_CLASS_NAMECHECK(klass, "SkinName");
        REG_CLASS_NAMECHECK(klass, "PixelTime");
        REG_CLASS_NAMECHECK(klass, "WeaponManager");
        REG_CLASS_NAMECHECK(klass, "WeaponSounds");
        REG_CLASS_NAMECHECK(klass, "Player_move_c");
        REG_CLASS_NAMECHECK(klass, "NetworkStartTable");
        REG_CLASS_NAMECHECK(klass, "Rocket");
        REG_CLASS_NAMECHECK(klass, "GameConnect");
        REG_CLASS_NAMECHECK(klass, "PlayerDamageable");

        REG_CLASS_NAMECHECK(klass, "ItemRecord");

        REG_CLASS_NAMECHECK(klass, "ExperienceController");

        REG_CLASS_NAMECHECK(klass, "AlmanachTutorialManager");
        REG_CLASS_NAMECHECK(klass, "AlmanachMainUI");
        REG_CLASS_NAMECHECK(klass, "TrainingController");

        REG_CLASS_NAMECHECK(klass, "PhotonObjectCacher");
        REG_CLASS_NAMECHECK(klass, "PhotonView");
        REG_CLASS_NAMECHECK(klass, "PixelView");

        REG_CLASS_NAMECHECK(klass, "StoreKitEventListener");
        REG_CLASS_NAMECHECK(klass, "ProfileController");
    }

    if(NAMESPACE_CHECK(klass, "Rilisoft")) {
        if(CheckContentCount(klass, {8, 8}, {17, 17}) && CheckFieldPattern(klass, WeaponSkinIdkPattern) == 1.0) {
            REG_CLASS(klass, "WeaponSkinIdk");
        }
        REG_CLASS_NAMECHECK(klass, "LobbyItemsBundle");
    }

    if(NAMESPACE_CHECK(klass, "PGCompany")) {
        if(CheckContentCount(klass, {8, 8}, {47, 47}) && CheckFieldPattern(klass, ItemModulePattern)) {
            REG_CLASS(klass, "ItemModule");
        }
        if(CheckContentCount(klass, {4, 4}, {41, 41}) && CheckFieldPattern(klass, NiggerObfuscatedClassPattern) == 1.0) {
            REG_CLASS(klass, "NiggerObfuscatedClass");
        }
    }
}
