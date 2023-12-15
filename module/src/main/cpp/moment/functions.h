// PATTERN SCANNING IS FOR THE WEAK!!!! 🗣️🗣️🗣️

#include "pointerfuncs.h"
#include "utilfuncs.h"

AnalyticsParams offerwallParams = {0x0, 0x82, 0x18, 0x0, 0x0, 0x0, 0x0, false, nullptr, 0x0, false, 0x0, nullptr, false, 0x1, 0};
//{0x0, 0x82, 0x18, 0x0, 0x0, 0x0, 0x0, false, nullptr, 0x0, false, 0x0, nullptr, false, 0x1, 0};

void (*oldPixelTime)(void *ths);
void PixelTime(void *ths) {
    if(ths != nullptr) {
        static int readDelay = 0;

        if(manualWeaponUnlock) {
            keyboardPtr = OpenKeyboard(MonoString_new(""), 0, false, false);
            manualWeaponUnlock = false;
        }

        if(keyboardPtr != nullptr) {
            monoString* text = KeyboardGetText(keyboardPtr);
            
            if(text != nullptr && !MonoString_equels(text, MonoString_new(""))) {
                manualUnlockInput = text->getChars(); 
            }
        }

        if(unlockPet) {
            for(auto &v : petsList) {
                AddPet(MonoString_new(v), 260);
            }
        }

        readDelay++;

        if(discord) {
            OpenURL(MonoString_new("https://discord.gg/Y3gj2Rszq6"));
            discord = false;
        }

        if (currency) {
            monoString* str = MonoString_new(curList[selectedCur]);
            AddCurrency(WebInstance(), str, curAmount, 1, false, false, offerwallParams);
            currency = false;
        }
        if(loopCur) {
            monoString* str = MonoString_new(curList[selectedCur]);
            AddCurrency(WebInstance(), str, curAmount, 1, false, false, offerwallParams);
        }
        if (addAllGadgets) {
            for (int i = 0; i < IM_ARRAYSIZE(gadgetList); i++) {
                ProvideGadget(MonoString_new(gadgetList[i]), 65);
            }
            addAllGadgets = false;
        }
        if(unlockWear) {

            for(auto &i: armorList) {
                BuyArmor(WebInstance(), WearIndex(MonoString_new(i)), 65, MonoString_new("migr"), offerwallParams);
            }
            for(auto &i: hatList) {
                AddWear(6, MonoString_new(i));
            }
            for(auto &i: maskList) {
                AddWear(12, MonoString_new(i));
            }
            for(auto &i: capeList) {
                AddWear(9, MonoString_new(i));
            }
            for(auto &i: bootsList) {
                AddWear(10, MonoString_new(i));
            }
            unlockWear = false;
        }

        if(unlockCosmetics) {
            for(int i = startCosIndex - 1; i < endCosIndex; i++) {
                AddRoyale(MonoString_new(avatarList[i]), true, offerwallParams);
            }
            unlockCosmetics = false;
        }

        if(easyUnlockCos) {
            int length =  sizeof(wepList) / sizeof(wepList[0]);
            int groupSize = length / 8;

            if(easyUnlockCosStep == 0) {
                for(int i = 0; i < groupSize; i++) {
                    AddRoyale(MonoString_new(avatarList[i]), true, offerwallParams);
                }
                easyUnlockCosStep++;
            }

            else if (easyUnlockCosStep > 0 and easyUnlockCosStep <= 8) {
                for(int i = fmin(std::size(avatarList), groupSize * easyUnlockCosStep); i < fmin(std::size(avatarList), groupSize * (easyUnlockCosStep + 1)); i++) {
                    AddRoyale(MonoString_new(avatarList[i]), true, offerwallParams);
                }
                easyUnlockCosStep++;
            }
            easyUnlockCos = false;
        }
    }

    oldPixelTime(ths);
}

int effectSpamDelay = 0;
void NetworkStartTable(void *ths) {

    Il2CppClass *thsClass = GET_CLASS("NetworkStartTable");
    Il2CppClass *MoveC = GET_CLASS("Player_move_c");

    photonViewList = GetStaticFieldByIndex<monoList<void**>*>(GET_CLASS("PhotonObjectCacher"), 0x0);

    if (ths != nullptr && photonViewList != nullptr) {

        players = GetPlayers(ths);

        // nigger naggot dev patched the most craziest mod
        if (killAll) {
            players->foreach([&](void *player, int index) {

                if (player != nullptr) {

                    if(get_PlayerIsMine(player)) return;

                    void *transform = get_PlayerTransform(player);
                    void *plrObject = Component$get_gameObject(transform);
                    void *bodyAimCollider = *(void **) GetFieldPtr(MoveC, player, "_bodyAimCollider");

                    DamageTarget(character, plrObject, 99999999.0f, bodyAimCollider, Transform$get_position(transform),
                                 il2cpp_string_new("gadget_fakebonus"), 0, 24);
                }
            });
        }

        if(disableJumpAll) {

            float val0 = 99999999999.0f;
            float val1 = 99999999999.0f;
            Il2CppArray* arr = il2cpp_array_new(CSharpTypeClass.Object, 2);
            arr->vector[0] = il2cpp_value_box(CSharpTypeClass.Float, &val0);
            arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Float, &val1);

            photonViewList->foreach([&](void *view, int index) {
                if(view != nullptr && !PhotonViewIsMine(view)) {
                    RPC(view, EventEnum::JumpDisableRPC, PhotonTargets::All, arr);
                }
            });
        }

        if(destroy) {
            auto photonplayers = PhotonNetwork_playerListothers();
            LOG_INFO("Test1");
            for(int i = 0; i < photonplayers->getLength(); ++i) {
                auto photonplayer = photonplayers->getPointer()[i];
                if(photonplayer != nullptr) {
                    LOG_INFO("Test2");
                    DestroyPlayer(photonplayer);
                }

            }
            destroy = false;
        }

        if(destroyAuto) {
            auto photonplayers = PhotonNetwork_playerListothers();
            for(int i = 0; i < photonplayers->getLength(); ++i) {
                auto photonplayer = photonplayers->getPointer()[i];
                if(photonplayer != nullptr) {
                    DestroyPlayer(photonplayer);
                }
            }
        }

        if(spawnRacingCar) {
            players->foreach([&](void* player, int index) {
                if(player == nullptr || get_PlayerIsMine(player)) return;
                void *car = SpawnPrefab(MonoString_new(realPrefabs[selectedPrefab]), get_PlayerVec(player), Quaternion(0, 0, 0, 0), 0);
                if(dontRenderCar) {
                    Object$Destroy(car);
                }
            });

            spawnRacingCar = false;
        }

        if(autoCar) {
            players->foreach([&](void* player, int index) {
                if(player == nullptr || get_PlayerIsMine(player)) return;
                void *car = SpawnPrefab(MonoString_new(realPrefabs[selectedPrefab]), get_PlayerVec(player), Quaternion(0, 0, 0, 0), 0);
                if(dontRenderCar) {
                    Object$Destroy(car);
                }
            });
        }

        if(handBug) {

            int16_t val3 = 834;
            int16_t val4 = 2;
            int32_t val5 = 0;

            Il2CppArray* arr = il2cpp_array_new(CSharpTypeClass.Object, 3);
            arr->vector[0] = il2cpp_value_box(CSharpTypeClass.Int16, &val3);
            arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Int16, &val4);
            arr->vector[2] = il2cpp_value_box(CSharpTypeClass.Int32, &val5);


            photonViewList->foreach([&](void* view, int index) {
                if(view != nullptr && !PhotonViewIsMine(view)) {
                    RPC(view, EventEnum::SetWeaponRPC, PhotonTargets::All, arr);
                }
            });

            handBug = false;
        }

        if(setNickname) {

            auto arr = il2cpp_array_new(CSharpTypeClass.Object, 1);
            arr->vector[0] = MonoString_new(nicknames[selectedNickname]);

            photonViewList->foreach([&](void* view, int index) {
                if(view != nullptr && !PhotonViewIsMine(view)) {
                    RPC(view, EventEnum::SetNickName, PhotonTargets::All, arr);
                }
            });

            setNickname = false;
        }

        if(setAvatar) {

            auto arr = il2cpp_array_new(CSharpTypeClass.Object, 1);
            arr->vector[0] = MonoString_new(avatarRPC[selectedAvatarRPC]);


            photonViewList->foreach([&](void* view, int index) {
                if(view != nullptr && !PhotonViewIsMine(view)) {
                    RPC(view, EventEnum::SetRoyaleAvatarRPC, PhotonTargets::All, arr);
                }
            });

            setAvatar = false;
        }

        if(effectSpam && effectSpamDelay % 10 == 0) {
            players->foreach([&](void *plr, int index) {
                if(plr != nullptr && !get_PlayerIsMine(plr)) {
                    void *pixelView_ = *(void**) GetFieldPtr(GET_CLASS("Player_move_c"), plr, "pixelView");
                    void *photonView_ = *(void**) GetFieldPtr(GET_CLASS("Player_move_c"), plr, "photonView");
                    int viewID_ = GetPixelViewID(pixelView_);
                    int val2 = 5;
                    float val3 = 1 / 55;
                    Il2CppArray *arr = il2cpp_array_new(CSharpTypeClass.Object, 4);
                    arr->vector[0] = MonoString_new("Weapon1652");
                    arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Int32, &val2);
                    arr->vector[2] = il2cpp_value_box(CSharpTypeClass.Float, &val3);
                    arr->vector[3] = il2cpp_value_box(CSharpTypeClass.Int32, &viewID_);

                    RPC(photonView_, EventEnum::PlayerEffectRPC, PhotonTargets::All,arr);

                    int32_t val4 = 2;
                    arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Int32, &val4);
                    RPC(photonView_, EventEnum::PlayerEffectRPC, PhotonTargets::All,arr);

                    int32_t val5 = 7;
                    arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Int32, &val5);
                    RPC(photonView_, EventEnum::PlayerEffectRPC, PhotonTargets::All,arr);

                    int32_t val6 = 11;
                    arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Int32, &val6);
                    RPC(photonView_, EventEnum::PlayerEffectRPC, PhotonTargets::All,arr);
                }
            });
        }

        effectSpamDelay++;

        if(blackScreen) {

            float val0 = 0.0f/0.0f;
            float val1 = 99999999999.0f;
            Il2CppArray* arr = il2cpp_array_new(CSharpTypeClass.Object, 2);
            arr->vector[0] = il2cpp_value_box(CSharpTypeClass.Float, &val0);
            arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Float, &val1);

            photonViewList->foreach([&](void *view, int index) {
                if(view != nullptr && !PhotonViewIsMine(view)) {
                    photonViewList->foreach([&](void *view2, int index2) {
                        if(PhotonViewIsMine(view2)) return;
                        RPC(view, EventEnum::SlowdownRPC, PhotonTargets::All, arr);
                    });
                }
            });

            blackScreen = false;
        }
    }
}

void (*oldNetworkStartTableHOOK)(void* ths);
void NetworkStartTableHOOK(void* ths) {

    if(ths != nullptr) {
    }

    oldNetworkStartTableHOOK(ths);
}

void (*oldWeaponManager)(void *ths);
void WeaponManager(void *ths) {
    if(ths != nullptr) {

        character = *(void**) GetFieldPtr(GET_CLASS("WeaponManager"), ths, "myPlayerMoveC");

        if(character != nullptr) {
            void* networkTable = *(void**) GetFieldPtr(GET_CLASS("Player_move_c"), character, "mySkinName", -2);
            NetworkStartTable(networkTable);
        }

        if (weapon) {

            Il2CppObject* upgObj = il2cpp_object_new(GET_CLASS("WeaponUpgradeV8"));
            UpgradeV8Constructor(upgObj, weaponLevel, selectedRarity);

            for(int i = startWepIndex - 1; i < endWepIndex; i++) {
                AddWeapon(ths, MonoString_new(wepList[i]), 14, false, false, upgObj, offerwallParams);
            }
            weapon = false;
        }

        if(easyUnlockWep) {
            int length =  sizeof(wepList) / sizeof(wepList[0]);
            int groupSize = length / 12;

            Il2CppObject* upgObj = il2cpp_object_new(GET_CLASS("WeaponUpgradeV8"));
            UpgradeV8Constructor(upgObj, weaponLevel, selectedRarity);

            if(easyUnlockWepStep == 0) {
                for(int i = 0; i < groupSize; i++) {
                    AddWeapon(ths, MonoString_new(wepList[i]), 14, false, false, upgObj, offerwallParams);
                }
                easyUnlockWepStep++;
            }
            else if (easyUnlockWepStep > 0 and easyUnlockWepStep <= 12) {
                for(int i = fmin(std::size(wepList), groupSize * easyUnlockWepStep); i < fmin(std::size(wepList), groupSize * (easyUnlockWepStep + 1)); i++) {
                    AddWeapon(ths, MonoString_new(wepList[i]), 14, false, false, upgObj, offerwallParams);
                }
                easyUnlockWepStep++;
            }
            easyUnlockWep = false;

        }

        if(startIllegalUnlockingWep) {

            Il2CppObject* upgObj = il2cpp_object_new(GET_CLASS("WeaponUpgradeV8"));
            UpgradeV8Constructor(upgObj, weaponLevel, selectedRarity);

            for(auto &i: goofyWeps) {
                AddWeapon(ths, MonoString_new(i), 62, false, false, upgObj, offerwallParams);
            }

            startIllegalUnlockingWep = false;
        }

        // ha aha ah unsafe cast make funny bug
        if(corruptedSniper) {

            Il2CppObject* upgObj = il2cpp_object_new(GET_CLASS("WeaponUpgradeV8"));
            UpgradeV8Constructor(upgObj, LONG_MIN, 5);

            AddWeapon(ths, (monoString*)il2cpp_string_new("mutagen_neutralizer"), 62, false, false, upgObj, offerwallParams);
            AddWeapon(ths, (monoString*)il2cpp_string_new("anniversary_anti_champion"), 62, false, false, upgObj, offerwallParams);
            AddWeapon(ths, (monoString*)il2cpp_string_new("disruptive_howitzer"), 62, false, false, upgObj, offerwallParams);

            corruptedSniper = false;
        }

        if(ammo) {
            auto playerWepList = GetPlayerWeapons(ths);
            for(int i = 0; i < playerWepList->getSize(); ++i) {
                auto wepw = playerWepList->getItems()[i];
                if(wepw != nullptr) {
                    SetStoredAmmo(wepw, 9999);
                    SetClipAmmo(wepw, 9999);
                }
            }
        }
    }

    oldWeaponManager(ths);
}

void (*oldWeaponSounds)(void *ths);
void WeaponSounds(void *ths) {

    currentWeaponSounds = ths;

    if (ths != nullptr) {

        Il2CppClass *thsClass = GET_CLASS("WeaponSounds");

        if (elecShock) {
            FIELD(bool, "isElectricShock") = true;
            FIELD(float, "electricShockCoeff") = 99999;
            FIELD(float, "electricShockTime") = 99999;
        }
        if (slientAim) {
            FIELD(bool , "isRoundMelee") = true;
            FIELD(float, "radiusRoundMelee") = 99999;
        }

        if(infScore) {
            FIELD(bool , "isBuffPoints") = true;
            FIELD(float , "buffBonusPointsForKill") = 99999;
        }

        if(polymorhp) {
            FIELD(bool, "polymorpher") = true;
            FIELD(float, "polymorphDuarationTime") = 9999999999999.0f;
            FIELD(int, "polymorphType") = 1;
            FIELD(float, "polymorphMaxHealth") = 9999999999999.0f;

            FIELD(bool, "harpoon") = true;
            FIELD(float, "harpoonMaxDistance") = 9999999999999.0f;
            FIELD(float, "harpoonMinDistance") = 9999999999999.0f;
        }

        if(noCharge) {
            FIELD(bool, "isCharging") = false;
            FIELD(float, "chargeTime") = 99999999.0f;
            FIELD(int , "chargeMax") = 2;
        }

        if(floatHit) {
            FIELD(bool, "isPoisoning") = true;
            FIELD(int, "poisonCount") = 3;
            FIELD(int, "poisonType") = 2;
            FIELD(float, "poisonDamageMultiplier") = 0.1;
            FIELD(float, "poisonTime") = 0.1;
        }

        if(targetExplode) {
            FIELD(bool, "isKilledTargetExplode") = true;
            FIELD(float, "killedTargetExplosionRadiusDamage") = 20.0;
            FIELD(float, "killedTargetExplosionRadiusDamageSelf") = 0;
            FIELD(float, "killedTargetExplosionDamageMultiplier") = 0;
        }

    }

    oldWeaponSounds(ths);
}

void (*oldPlrMoveC)(void *ths);
void PlrMoveC(void *ths) {

    if (ths != nullptr && character != nullptr) {

        Il2CppClass *thsClass = GET_CLASS("Player_move_c");
        Il2CppClass *SkinName_class = GET_CLASS("SkinName");
        Il2CppClass *FirstPersonControlSharp_class = GET_CLASS("FirstPersonControlSharp");

        if(get_PlayerIsMine(ths)) {

            void *skinName = *(void **) GetFieldPtr(thsClass, character, "mySkinName");
            void *fpController = *(void **) GetFieldPtr(SkinName_class, skinName, "firstPersonControl");

            if (airJump) {
                *(bool *) GetFieldPtr(FirstPersonControlSharp_class, fpController,
                                      "runJoystickAngleDeadZone", 1) = true;
                *(bool *) GetFieldPtr(FirstPersonControlSharp_class, fpController,
                                      "batleRoyaleAdditionalLandingGravity", 1) = true;
                *(bool *) GetFieldPtr(FirstPersonControlSharp_class, fpController, "_moveC",
                                      37) = false;
            }

            if (spamChat) {
                SendChat(character, MonoString_new(spam.c_str()), false, MonoString_new("0"));
            }

            if (xray) {
                SetXrayShader(ths, true);
            }

            if (teleKill && players != nullptr) {

                void *closetPlayer = nullptr;
                closetPlayer = findNearestPlayer(character, players);

                if (closetPlayer != nullptr && IsEnemyTo(character, closetPlayer)) {
                    Transform$set_position(get_PlayerTransform(character),
                                           get_PlayerVec(closetPlayer) + Vector3(0, 0, 3));
                    Transform$lookAt(get_PlayerTransform(character),
                                     get_PlayerTransform(closetPlayer));
                }
            }

            if (aimbot && players != nullptr) {

                void *closetPlayer = nullptr;
                closetPlayer = findNearestPlayer(character, players);

                if (closetPlayer != nullptr && IsEnemyTo(character, closetPlayer)) {
                    Transform$lookAt(get_PlayerTransform(character),
                                     get_PlayerTransform(closetPlayer));
                }
            }

            if (attractPlayers) {

                void *pixelView_ = *(void **) GetFieldPtr(GET_CLASS("Player_move_c"), ths,
                                                          "pixelView");
                void *photonView_ = *(void **) GetFieldPtr(GET_CLASS("Player_move_c"), ths,
                                                           "photonView");
                int viewID_ = GetPixelViewID(pixelView_);
                int32_t val2 = 9;
                float val3 = 9999999999.0f;
                Il2CppArray *arr = il2cpp_array_new(CSharpTypeClass.Object, 4);
                arr->vector[0] = MonoString_new("Weapon1652");
                arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Int32, &val2);
                arr->vector[2] = il2cpp_value_box(CSharpTypeClass.Float, &val3);
                arr->vector[3] = il2cpp_value_box(CSharpTypeClass.Int32, &viewID_);

                RPC(photonView_, EventEnum::PlayerEffectRPC, PhotonTargets::Others, arr);

                attractPlayers = false;
            }

            static int tpToNormalPosTimer = 0;

            if (noClipAll) {

                static Vector3 oldPos;

                if (tpToNormalPosTimer <= 0) {
                    oldPos = get_PlayerVec(character);
                }

                if (tpToNormalPosTimer < 5) {
                    tpToNormalPosTimer++;
                    set_PlayerVec(character, Vector3(0.0f / 0.0f, 0.0f / 0.0f, 0.0f / 0.0f));
                } else {
                    set_PlayerVec(character, oldPos);
                    tpToNormalPosTimer = 0;
                    noClipAll = false;
                }
            }

            if (slowdownAll) {
                float val0 = -99999999999.0f;
                float val1 = 99999999999.0f;
                Il2CppArray* arr = il2cpp_array_new(CSharpTypeClass.Object, 2);
                arr->vector[0] = il2cpp_value_box(CSharpTypeClass.Float, &val0);
                arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Float, &val1);

                photonViewList->foreach([&](void *view, int index) {
                    if(view != nullptr && !PhotonViewIsMine(view)) {
                        RPC(view, EventEnum::SlowdownRPC, PhotonTargets::All, arr);
                    }
                });
            }

            if (speedupAll) {
                float val0 = 99999999999.0f;
                float val1 = 99999999999.0f;
                Il2CppArray* arr = il2cpp_array_new(CSharpTypeClass.Object, 2);
                arr->vector[0] = il2cpp_value_box(CSharpTypeClass.Float, &val0);
                arr->vector[1] = il2cpp_value_box(CSharpTypeClass.Float, &val1);

                photonViewList->foreach([&](void *view, int index) {
                    if(view != nullptr && !PhotonViewIsMine(view)) {
                        RPC(view, EventEnum::SlowdownRPC, PhotonTargets::All, arr);
                    }
                });
            }
        }
    }

    oldPlrMoveC(ths);
}

void (*oldRocket)(void* ths, void* RocketSettings);
void Rocket(void* ths, void* RocketSettings) {

    Il2CppClass *thisClass = il2cpp_class_from_name(LibImages.AssemblyCSharp, "","Rocket");
    Il2CppClass *RocketSettings_class = il2cpp_class_from_name(LibImages.AssemblyCSharp, "","RocketSettings");

    if (ths != nullptr) {

        if(!*(bool *) GetFieldPtr(thisClass, ths, "harpoonMinDistance", 14)) {
            oldRocket(RocketSettings, ths);
            return;
        }

        if(nuke) {
            *(Il2CppString **) GetFieldPtr(thisClass, ths, "isStun", -13) = il2cpp_string_new("a-bomb_mini");
        }

        if(longLifetime) {
            *(float *) GetFieldPtr(RocketSettings_class, RocketSettings, "lifeTime") = 9999999999999.0f;
        }

        if(gravity) {
            *(bool *) GetFieldPtr(RocketSettings_class, RocketSettings, "useGravity") = true;
        }

        if(ricochet) {
            *(bool *) GetFieldPtr(RocketSettings_class, RocketSettings, "isRickochet") = true;
            *(int *) GetFieldPtr(RocketSettings_class, RocketSettings, "rickochetsCount") = 999999999;
        }

        switch (rocketMode) {
            case 1: // Homing
                *(int *) GetFieldPtr(RocketSettings_class, RocketSettings, "typeFly") = 10;
                *(float *) GetFieldPtr(RocketSettings_class, RocketSettings, "autoRocketForce") = 15.0f;
                *(float *) GetFieldPtr(RocketSettings_class, RocketSettings, "raduisDetectTarget") = 999999999999.0f;
                *(float *) GetFieldPtr(RocketSettings_class, RocketSettings, "autoHomingAngle") = 999999999999.0f;
                break;

            case 2: // Follow Crosshair
                *(int *) GetFieldPtr(RocketSettings_class, RocketSettings, "typeFly") = 4;
                *(float *) GetFieldPtr(RocketSettings_class, RocketSettings, "autoRocketForce") = 15.0f;
                break;
        }

    }

    oldRocket(RocketSettings, ths);
}

void* (*oldCreateRocket)(void *weaponSounds, Vector3 pos, Quaternion rot, float chargePower, int smoke, int whateverthisis);
void* CreateRocket(void *weaponSounds, Vector3 pos, Quaternion rot, float chargePower, int smoke, int whateverthisis) {
    if (tower) {
        for (float i = 0; i < 15; ++i) {
            Vector3 moddedPos = pos + Vector3(0, i, 0);
            oldCreateRocket(weaponSounds, moddedPos, rot, chargePower, smoke, whateverthisis);
        }
    }
    return oldCreateRocket(weaponSounds, pos, rot, chargePower, smoke, whateverthisis);
}

void (*oldSendPlayerEffect)(void *ths, void *player, monoString *source, int effectIndex, float duration, int senderPixelID);
void SendPlayerEffect(void *ths, void *player, monoString *source, int effectIndex, float duration, int senderPixelID) {
    if (ths != nullptr && floatHit) {
        oldSendPlayerEffect(ths, player, source, 12, 99999999999.0f, senderPixelID);
    }
    oldSendPlayerEffect(ths, player, source, effectIndex, duration, senderPixelID);
}

float (*oldSpeedModifier)(void *ths);
float SpeedModifier(void * ths) {
    if (ths != nullptr) {
        if(speedhack)
            return 1000;
    }
    return oldSpeedModifier(ths);
}

int (*oldget_CurrentExp)();
int get_CurrentExp() {

    if(xpSpoofer) {

        return 32645;
    }

    return oldget_CurrentExp();
}

int (*oldget_CurrentLevel)();
int get_CurrentLevel() {

    if(xpSpoofer) {
        return 65;
    }

    return oldget_CurrentLevel();
}

void* (*oldEncryptCommand)(void* instance, void* byteArr, bool idk);
void* EncryptCommand(void* instance, void* byteArr, bool idk) {
    if (instance == nullptr) {
        return oldEncryptCommand(instance, byteArr, idk);
    }

    if (commandParams.empty()) {
        return oldEncryptCommand(instance, byteArr, idk);
    }

    LOG_INFO("TEST 1");
    std::string current = Encoding$GetString(get_UTF8(), byteArr)->getString();
    json j;

    try {
        j = json::parse(current);
    } catch (nlohmann::json::parse_error& e) {
        return oldEncryptCommand(instance, byteArr, idk);
    }

    auto req_it = j.find("req_id");
    if (req_it == j.end()) {
        return oldEncryptCommand(instance, byteArr, idk);
    }
    int req_id = *req_it;

    auto it = commandParams.find(req_id);
    if (it == commandParams.end()) {
        return oldEncryptCommand(instance, byteArr, idk);
    }

    (*it->second)[1]["req_id"] = req_id;
    std::string dump = (*it->second)[1].dump();

    commandParams.erase(it);
    return oldEncryptCommand(instance, Encoding$GetBytes(get_UTF8(), il2cpp_string_new(dump.c_str())), idk);
}

void* (*oldSendMessage)(void* instance, monoString* command, void* params, float idk1, void* delegate, void* bytearr);
void* SendMessage(void* instance, monoString* command, void* params, float idk1, void* delegate, void* bytearr) {
    WSMInstance = instance;

    return oldSendMessage(instance, command, params, idk1, delegate, bytearr);
}

void (*oldShotPressed)(void *ths);
void ShotPressed(void *ths) {

    static float counter = 1;

    if(ths != nullptr && currentWeaponSounds != nullptr && firerateHack) {

        if(counter >= 60) {
            //BulletShot(ths, GetField<void*>(ths, 0x620));
            _Shot(ths);
            ShootS(ths); // kickable
            counter = 0;
        }
        counter += firerate;
        return; //oldShotPressed(ths);
    }

    oldShotPressed(ths);
}

void (*oldSendChatHOOK)(void* obj, monoString* text, bool isClan, monoString* logoid);
void SendChatHOOK(void* obj, monoString* text, bool isClan, monoString* logoid) {

    std::stringstream stream(text->getString());
    std::string segment;
    std::vector<std::string> args;

    while(std::getline(stream, segment, ' ')) {
        args.push_back(segment);
    }

    if (args[0] == "/spam") {
        spam = text->getString().substr(6);
        return;
    }

    return oldSendChatHOOK(obj, text, isClan, logoid);
}

#ifdef DEVBUILD
void (*oldPeerRPC)(void* ths, void* view, uint8_t eventEnum, int photonTargets, void* targetPlayer, bool encrypt, Il2CppArray* parameters);
void PeerRPC(void* ths, void* view, uint8_t eventEnum, int photonTargets, void* targetPlayer, bool encrypt, Il2CppArray* parameters) {

    if(parameters == nullptr) {
        oldPeerRPC(ths, view, eventEnum, photonTargets, targetPlayer, encrypt, parameters);
        return;
    }

    if(targetPlayer != nullptr) {
        LOG_INFO("[PeerRPC] (eventEnum: %s) targetPlayer is not null", rpcEntries[eventEnum]);
    }
    else
    {
        LOG_INFO("[PeerRPC] (eventEnum: %s) photonTargets: %i", rpcEntries[eventEnum], photonTargets));
    }
    for (int i = 0; i < parameters->max_length; ++i) {

        if(parameters->vector[i]== nullptr) {
            LOG_INFO("[PeerRPC] (eventEnum: %s) index %i is null", rpcEntries[eventEnum], i);
        }
        else {

            //const char *namespaceName = il2cpp_class_get_namespace(il2cpp_object_get_class((Il2CppObject *) parameters->vector[i]));
            //const char *className = il2cpp_class_get_name(il2cpp_object_get_class((Il2CppObject *) parameters->vector[i]));
            const char *typeName = il2cpp_type_get_name(il2cpp_class_get_type(il2cpp_object_get_class((Il2CppObject *) parameters->vector[i])));

            if (typeName != nullptr) {

                char buff[2048];

                if(strcmp(typeName, "System.Single") == 0 ) {
                    LOG_INFO("[PeerRPC] (eventEnum: %s:%i) float value: %f",
                             rpcEntries[eventEnum], i, UnboxIl2cppObject<float>((Il2CppObject*)parameters->vector[i]);
                }
                else if(strcmp(typeName, "System.Int32") == 0 ) {
                    LOG_INFO("[PeerRPC] (eventEnum: %s:%i) int32 value: %i",
                             rpcEntries[eventEnum], i, UnboxIl2cppObject<int>((Il2CppObject*)parameters->vector[i]));
                }
                else if(strcmp(typeName, "System.Double") == 0 ) {
                    LOG_INFO("[PeerRPC] (eventEnum: %s:%i) double value: %f",
                             rpcEntries[eventEnum], i, UnboxIl2cppObject<double>((Il2CppObject*)parameters->vector[i]));
                }
                else if(strcmp(typeName, "System.Boolean") == 0 ) {
                    LOG_INFO("[PeerRPC] (eventEnum: %s:%i) bool value: %f",
                             rpcEntries[eventEnum], i, UnboxIl2cppObject<double>((Il2CppObject*)parameters->vector[i]));
                }
                else if(strcmp(typeName, "System.String") == 0 ) {
                    LOG_INFO("[PeerRPC] (eventEnum: %s:%i) string value: %s",
                             rpcEntries[eventEnum], i, (*(monoString**)(parameters->vector[i]))->getChars());
                }

            } else {
                LOG_INFO("[PeerRPC] (eventEnum: %s) typeName is null", rpcEntries[eventEnum]);
            }
        }
    }

    oldPeerRPC(ths, view, eventEnum, photonTargets, targetPlayer, encrypt, parameters);
}
#endif

bool (*oldWepSkins6_1)(void* idfk1);
bool WepSkins6_1(void* idfk1) {

    if(wepSkins6) return true;

    return oldWepSkins6_1(idfk1);
}


int (*oldModUp_1)(void* ths, int idfk1);
int ModUp_1(void* ths, int idfk1) {

    if(modUp) return 0;

    return oldModUp_1(ths, idfk1);
}

void Hooks() {

    LOG_INFO("Hooking");

    HOOK_UPDATE(GET_CLASS("WeaponManager"), WeaponManager);
    HOOK_UPDATE(GET_CLASS("PixelTime"), PixelTime);

    Il2CppClass *WeaponSounds_class = GET_CLASS("WeaponSounds");//il2cpp_class_from_name(LibImages.AssemblyCSharp, "","WeaponSounds");
    HOOK_UPDATE(WeaponSounds_class, WeaponSounds);

    Il2CppClass *PlrMoveC_class = GET_CLASS("Player_move_c");//il2cpp_class_from_name(LibImages.AssemblyCSharp, "","Player_move_c");
    HOOK_UPDATE(PlrMoveC_class, PlrMoveC);

    HOOK_UPDATE(GET_CLASS("NetworkStartTable"), NetworkStartTableHOOK);

    SignatureCondition CreateRocketC {
            "internal static",
            "Rocket",
            nullptr,
            {"WeaponSounds", "Vector3", "Quaternion", "Single", "Int32", "Int32"}
    };
    MethodPtr CreateRocketPtr = GetMethodPointer(PlrMoveC_class, CreateRocketC);
    HOOK(CreateRocketPtr, CreateRocket);

    SignatureCondition SendChatC {"public","Void","SendChat",{"String", "Boolean", "String"}};
    HOOK(GetMethodPointer(GET_CLASS("Player_move_c"), SendChatC), SendChatHOOK);

    SignatureCondition SendPlayerEffectC {"internal", "Void", nullptr, {nullptr, "String", "Int32", "Single", "Int32"}};
    MethodPtr SendPlayerEffectPtr = GetMethodPointer(PlrMoveC_class, SendPlayerEffectC);
    HOOK(SendPlayerEffectPtr, SendPlayerEffect);

    Il2CppClass *Rocket_class = GET_CLASS("Rocket");//il2cpp_class_from_name(LibImages.AssemblyCSharp, "","Rocket");
    SignatureCondition RocketC {
            "private",
            "Boolean",
            nullptr,
            {"RocketSettings"}
    };
    MethodPtr RocketPtr = GetMethodPointer(Rocket_class, RocketC);
    HOOK(RocketPtr, Rocket);

    Il2CppClass *ItemRecord_class = GET_CLASS("ItemRecord");//il2cpp_class_from_name(LibImages.AssemblyCSharp, "", "ItemRecord");
    HOOK(GetMethodPointerFromName(ItemRecord_class, "get_SpeedModifier"), SpeedModifier);

    SignatureCondition ShotPressedC {"private", "IEnumerator", nullptr, {"Int32", "Animation", nullptr}};
    HOOK(GetMethodPointer(PlrMoveC_class, ShotPressedC, -2), ShotPressed);

#ifdef DEVBUILD

    // HOOK((il2cpp_base + 0x5aa6a34), PeerRPC);

#endif
    static Il2CppClass *WeaponSkinManager_class = GET_CLASS("WeaponSkinManager");
    static Il2CppClass *WeaponSkinIdk = GET_CLASS("WeaponSkinIdk");
    static Il2CppClass *ItemModule_class = GET_CLASS("ItemModule");

    HOOK(GetMethodPointerFromIndex(WeaponSkinManager_class, 0x5f), WepSkins6_1);
    HOOK(GetMethodPointerFromIndex(ItemModule_class, 0x16), ModUp_1);

    LOG_INFO("Hooking done");
}

MethodPtr freeBundle1;
MethodPtr freeBundle2;
MethodPtr freeBundle3;

// dont use sex patch unless u want to trigger deadlock
void LoadPatch() {
    static Il2CppClass *StoreKitEventListener = GET_CLASS("StoreKitEventListener");
    static Il2CppClass *SwearingClass = GET_CLASS("SwearingClass");
    static Il2CppClass *FreeBundle1_class = GET_CLASS("FreeBundle1");
    static Il2CppClass *LobbyItemsBundle_class = GET_CLASS("LobbyItemsBundle");
    static SignatureCondition IsPayingUserC {"internal static", "Void", nullptr, {"Boolean"}};

    PATCH(GetMethodPointer(StoreKitEventListener,IsPayingUserC, 2), "20008052C0035FD6");
    PATCH(GetMethodPointerFromIndex(SwearingClass, 0x2), "000080D2C0035FD6");

    freeBundle1 = GetMethodPointerFromIndex(FreeBundle1_class, 0x1e);
    freeBundle2 = GetMethodPointerFromIndex(FreeBundle1_class, 0x16);
    freeBundle3 = GetMethodPointerFromIndex(LobbyItemsBundle_class, 0x7);
}
void Patches() {

    static Il2CppClass *NetworkStartTable_class = GET_CLASS("NetworkStartTable");
    static Il2CppClass *WeaponSkinManager_class = GET_CLASS("WeaponSkinManager");
    static Il2CppClass *PlayerMoveC_class = GET_CLASS("Player_move_c");
    static Il2CppClass *GameConnect_class = GET_CLASS("GameConnect");
    static Il2CppClass *ItemRecord_class = GET_CLASS("ItemRecord");
    static Il2CppClass *ExperienceController_class = GET_CLASS("ExperienceController");

    PATCH_SWITCH(freeBundle1, "00008052C0035FD6", freeBundle);
    PATCH_SWITCH(freeBundle2, "00008052C0035FD6", freeBundle);
    PATCH_SWITCH(freeBundle3, "20008052C0035FD6", freeBundle);

    static SignatureCondition TeamKill1C {"internal static", "Int32", nullptr, {"ENUM", "Boolean"}};
    PATCH_SWITCH(GetMethodPointer(GameConnect_class, TeamKill1C), "C0035FD6", teamKill);

    static SignatureCondition TeamKill2C {"internal static", "Void", nullptr, {"Boolean"}};
    PATCH_SWITCH(GetMethodPointer(GameConnect_class, TeamKill2C, -6), "C0035FD6", teamKill);

    static SignatureCondition Godmode1C {"private", "Void", nullptr, {"Single", "ENUM", "ENUM", "ENUM", "ENUM", "Vector3", "String", "Int32"}};
    PATCH_SWITCH(GetMethodPointer(PlayerMoveC_class, Godmode1C), "C0035FD6", godmode);

    static SignatureCondition HideIdC {"private", "Void", "Start", {}};
    PATCH_SWITCH(GetMethodPointer(NetworkStartTable_class, HideIdC, 2), "C0035FD6", hideId);

    PATCH_SWITCH(GetMethodPointerFromIndex(ExperienceController_class, 0x6), "A0F08FD2C0035FD6", maxLevel);
}