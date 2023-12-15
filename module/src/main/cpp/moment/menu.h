#include <vector>
#include "imgui_mods.h"

using namespace ImGui;

bool test;
bool freeResize;
bool isOpen = true;
bool applyPressed;
float widgetSize = 1;
ImFont *mainFont = nullptr;
ImFont *iconFont = nullptr;
int titleIndex = 0;
int categorySelector = 0;
int subTabSelector = 0;
float transparency = 1.0f;
float subTabBarHeight = 50;


ImVec2 winSize;
float winX;
float winY;
#define groupX ((winX * 0.75f) - style.ItemSpacing.x * 2.0f)
#define groupY (winY * 0.9f - style.ItemSpacing.x * 2.0f)

int titleSelect = 0;
const char* title[] = {"Nazi Mod v1.4", "JUSDN v3, The future of modding!", "Vortex Mod Menu 2", "Happymod.com", "Proplam Mod Menu", ""};

void DrawMods() {

    ImGuiStyle &style = GetStyle();

    // Gameplay
    if (categorySelector == 0) {

        if (subTabSelector > 2)
            subTabSelector = 0;

        ImGuiMod::CategorySubTab(OBFUSCATE("Combat"), 0, &subTabSelector, [&] {
            ImGuiMod::Group(OBFUSCATE("Main"), OBFUSCATE("#KillAura"), {groupX * 0.5f, groupY}, [&] {
                Checkbox(OBFUSCATE("Kill All"), &killAll);
                Checkbox(OBFUSCATE("Slient Aim"), &slientAim);
                Checkbox(OBFUSCATE("Aimbot (WIP)"), &aimbot);
                Checkbox(OBFUSCATE("Teleport kill"), &teleKill);
            });
            SameLine();
            ImGuiMod::Group(OBFUSCATE("Misc"), OBFUSCATE("#CombatMisc"), {groupX * 0.5f, groupY}, [&] {
                Checkbox(OBFUSCATE("Cockmode"), &godmode);
                Checkbox(OBFUSCATE("Friendly Fire"), &teamKill);
                Checkbox(OBFUSCATE("Speedhack"), &speedhack);
                Checkbox(OBFUSCATE("Air Jump"), &airJump);
                Checkbox(OBFUSCATE("Infinite Score On Kill"), &infScore);
            });
        });

        ImGuiMod::CategorySubTab(OBFUSCATE("Weapons"), 1, &subTabSelector, [&] {
            ImGuiMod::Group(OBFUSCATE("General"), OBFUSCATE("#WepGeneral"), {groupX * 0.5f, groupY * 1.5f}, [&] {
                Checkbox(OBFUSCATE("Unlimited Ammo"), &ammo);
                Checkbox(OBFUSCATE("Target float on hit"), &floatHit);
                Checkbox(OBFUSCATE("Electric Shock (Sensitivity Troll)"), &elecShock);
                //Checkbox(OBFUSCATE("Coin Drop"), &coinDrop);
                Checkbox(OBFUSCATE("No Charge"), &noCharge);
                //Checkbox(OBFUSCATE("No Gadget Cooldown"), &noGadgetCd);
                Checkbox(OBFUSCATE("Killed Target Explode"), &targetExplode);
                PushItemWidth(GetWindowWidth() * 0.5f);
                SliderFloat(OBFUSCATE("Firerate"), &firerate, 1, 60);
                PopItemWidth();
                Checkbox(OBFUSCATE("Hack Firerate (Kickable)"), &firerateHack);
            });
            SameLine();
            ImGuiMod::Group(OBFUSCATE("Rocket"), OBFUSCATE("#Rocket"), {groupX * 0.5f, groupY * 1.5f}, [&] {
                PushItemWidth(GetWindowWidth() * 0.5f);
                Combo("Rocket Mode", &rocketMode, rocketModes, IM_ARRAYSIZE(rocketModes));
                PopItemWidth();
                Checkbox(OBFUSCATE("Long Lifetime"), &longLifetime);
                Checkbox(OBFUSCATE("Ricochet"), &ricochet);
                Checkbox(OBFUSCATE("Gravity"), &gravity);
                Checkbox(OBFUSCATE("Polymorpher"), &polymorhp);
                Checkbox(OBFUSCATE("Rocket Tower"), &tower);
            });
        });

        ImGuiMod::CategorySubTab(OBFUSCATE("Visual & Funs"), 2, &subTabSelector, [&] {
            ImGuiMod::Group(OBFUSCATE("Visual"), OBFUSCATE("#WepGeneral"), {groupX * 0.5f, groupY}, [&] {
                Checkbox(OBFUSCATE("X-ray vision"), &xray);
            });
            SameLine();
            ImGuiMod::Group(OBFUSCATE("Funs"), OBFUSCATE("#Rocket"), {groupX * 0.5f, groupY}, [&] {
                Checkbox(OBFUSCATE("Spam chat"), &spamChat);
                Checkbox(OBFUSCATE("Nuclear Explosion"), &nuke);
                TextUnformatted("Chat Commands:"
                                "\n/spam [Text]"
                                "\nCustomize Chat Spam");
            });
        });
    }

    // Social
    if (categorySelector == 1) {

        if (subTabSelector > 1)
            subTabSelector = 0;

        ImGuiMod::CategorySubTab(OBFUSCATE("Prefab"), 0, &subTabSelector, [&] {
            ImGuiMod::Group(OBFUSCATE("Settings"), OBFUSCATE("#PrefabSettings"), {groupX * 0.6f, groupY}, [&] {
                PushItemWidth(GetWindowWidth() * 0.5f);
#ifdef DEVBUILD
                Combo(OBFUSCATE("Prefabs"), &selectedPrefab, realPrefabs, IM_ARRAYSIZE(realPrefabs), 6);
#else
                Combo(OBFUSCATE("Prefabs"), &selectedPrefab, prefabs, IM_ARRAYSIZE(prefabs), 6);
#endif
                PopItemWidth();
                Checkbox(OBFUSCATE("Don't render"), &dontRenderCar);
            });
            SameLine();
            ImGuiMod::Group(OBFUSCATE("Spawn"), OBFUSCATE("#PrefabSpawn"), {groupX * 0.4f, groupY}, [&] {
                Checkbox(OBFUSCATE("Auto Spawn Prefab"), &autoCar);
                if (Button(OBFUSCATE("Spawn Prefab"))) {
                    spawnRacingCar = true;
                }
            });
        });
        ImGuiMod::CategorySubTab(OBFUSCATE("Sabotages"), 1, &subTabSelector, [&] {

            ImGuiMod::Group(OBFUSCATE("Player"), OBFUSCATE("#SaboMovement"), {groupX * 0.6f, groupY * 2.1f}, [&] {

                Checkbox(OBFUSCATE("Speedup All"), &speedupAll);
                Checkbox(OBFUSCATE("Slowdown All"), &slowdownAll);
                Checkbox(OBFUSCATE("Disable Jump All"), &disableJumpAll);
                Checkbox(OBFUSCATE("Effect Spam"), &effectSpam);

                Combo(OBFUSCATE("Nicknames List"), &selectedNickname, nicknamesCombo, IM_ARRAYSIZE(nicknamesCombo));
                if (Button("Set Nickname to everyone")) {
                    setNickname = true;
                }
                Combo(OBFUSCATE("Avatar List"), &selectedAvatarRPC, avatarRPC, IM_ARRAYSIZE(avatarRPC));
                if (Button(OBFUSCATE("Set Avatar to everyone"))) {
                    setAvatar = true;
                }
                if (Button(OBFUSCATE("Attract All"))) {
                    attractPlayers = true;
                }
                if (Button(OBFUSCATE("Hand Bug All"))) {
                    handBug = true;
                }
            });
            SameLine();
            ImGuiMod::Group(OBFUSCATE("Game"), OBFUSCATE("#Connection"), {groupX * 0.4f, groupY * 2.1f}, [&] {
                Checkbox(OBFUSCATE("Auto crash"), &destroyAuto);
                if (Button(OBFUSCATE("Crash All"))) {
                    destroy = true;
                }
                if (Button(OBFUSCATE("No-clip All"))) {
                    noClipAll = true;
                }
                if (Button(OBFUSCATE("Black screen All"))) {
                    blackScreen = true;
                }
            });
        });
    }

    // Account
    if (categorySelector == 2) {

        if (subTabSelector > 1)
            subTabSelector = 0;

        ImGuiMod::CategorySubTab(OBFUSCATE("Progress"), 0, &subTabSelector, [&] {
            ImGuiMod::Group(OBFUSCATE("General"), OBFUSCATE("#AccGeneral"), {groupX, groupY * 2.0f},
                            [&] {
                                Checkbox(OBFUSCATE("Hide ID (-1 ID)"), &hideId);
                                Checkbox(OBFUSCATE("XP Spoofer (Lvl 65 after match completion)"),
                                         &maxLevel);
                                Checkbox(OBFUSCATE("Free Module Upgrade"), &modUp);
                                Checkbox(OBFUSCATE("Purchase any weapon skin"), &wepSkins6);
                                Checkbox(OBFUSCATE("Free Bundle"), &freeBundle);
                                TextUnformatted(OBFUSCATE(
                                                        "Hide your ID while in match or from history.\nYour ID still can be found by searching with your nickname.\nMake sure you have a nickname that's hard to type."));
                                Combo(OBFUSCATE("Currencies"), &selectedCur, curList,
                                      IM_ARRAYSIZE(curList));
                                SliderInt(OBFUSCATE("Amount"), &curAmount, 100, 5000);
                                if (Button(OBFUSCATE("Add Currency"))) {
                                    currency = true;
                                }
                                SameLine();
                                Checkbox(OBFUSCATE("Auto Add"), &loopCur);
                                if (Button(OBFUSCATE("Ban Account"))) {
                                    ban = true;
                                }
                            });
        });
        ImGuiMod::CategorySubTab(OBFUSCATE("Content Unlocker"), 1, &subTabSelector, [&] {
            ImGuiMod::Group(OBFUSCATE("Weapon Unlocker"), OBFUSCATE("#WepUnlocker"),
                            {groupX, groupY * 1.5f}, [&] {
                        SliderInt(OBFUSCATE("Start"), &startWepIndex, 0,
                                  sizeof(wepList) / sizeof(wepList[0]));
                        SliderInt(OBFUSCATE("End"), &endWepIndex, 1,
                                  sizeof(wepList) / sizeof(wepList[0]));
                        Combo(OBFUSCATE("Raity"), &selectedRarity, rarities,
                              IM_ARRAYSIZE(rarities));
                        weaponLevel = std::min(65, weaponLevel);
                        InputInt(OBFUSCATE("Level"), &weaponLevel);
                        if (endWepIndex < startWepIndex) {
                            endWepIndex = startWepIndex;
                        }

                        startWepIndex = std::min(startWepIndex, endWepIndex);

                        if (Button(OBFUSCATE("Unlock"))) {
                            weapon = true;
                        }
                        if (easyUnlockWepStep <= 12) {
                            SameLine();
                            int length = sizeof(wepList) / sizeof(wepList[0]);
                            int groupSize = length / 12;
                            std::string str = "Easy Unlock ";

                            if (easyUnlockWepStep == 0) {
                                str = str + "0-" + std::to_string(groupSize);
                            } else if (easyUnlockWepStep > 0 and easyUnlockWepStep <= 12) {
                                str = str + std::to_string(
                                        (int) fmin(std::size(wepList),
                                                   groupSize * easyUnlockWepStep)) + "-" +
                                      std::to_string((int) fmin(std::size(wepList),
                                                                groupSize *
                                                                (easyUnlockWepStep + 1)));
                            }

                            if (Button(str.c_str())) {
                                easyUnlockWep = true;
                            }
                        }

                        SameLine();
                        if (Button(OBFUSCATE("Unlock Secret Weapons"))) {
                            startIllegalUnlockingWep = true;
                        }
                        if (Button(OBFUSCATE("Manual Unlock (with string)"))) {
                            startIllegalUnlockingWep = true;
                        }
                        SameLine();
                    });
            ImGuiMod::Group(OBFUSCATE("Cosmetic Unlocker"), OBFUSCATE("#CosUnlocker"),
                            {groupX, groupY * 0.7f}, [&] {
                        SliderInt(OBFUSCATE("Start "), &startCosIndex, 0,
                                  sizeof(avatarList) / sizeof(avatarList[0]));
                        SliderInt(OBFUSCATE("End "), &endCosIndex, 1,
                                  sizeof(avatarList) / sizeof(avatarList[0]));

                        if (endCosIndex < startCosIndex) {
                            endCosIndex = startCosIndex;
                        }

                        startCosIndex = std::min(startCosIndex, endCosIndex);

                        if (Button(OBFUSCATE("Unlock"))) {
                            unlockCosmetics = true;
                        }

                        if (easyUnlockCosStep <= 8) {
                            SameLine();
                            int length = sizeof(avatarList) / sizeof(avatarList[0]);
                            int groupSize = length / 8;
                            std::string str = "Easy Unlock ";

                            if (easyUnlockCosStep == 0) {
                                str = str + "0-" + std::to_string(groupSize);
                            } else if (easyUnlockCosStep > 0 and easyUnlockCosStep <= 8) {
                                str = str + std::to_string(
                                        (int) fmin(std::size(avatarList),
                                                   groupSize * easyUnlockCosStep)) + "-" +
                                      std::to_string((int) fmin(std::size(avatarList),
                                                                groupSize *
                                                                (easyUnlockCosStep + 1)));
                            }

                            if (Button(str.c_str())) {
                                easyUnlockCos = true;
                            }
                        }
                    });
            ImGuiMod::Group(OBFUSCATE("Manual Unlock (Unlock with string)"),
                            OBFUSCATE("#CosUnlocker"), {groupX, groupY * 0.5f}, [&] {
                        Combo(OBFUSCATE("Unlock Type"), &manualWeaponType, manualWeaponTypes,
                              IM_ARRAYSIZE(manualWeaponTypes));
                        if (Button(OBFUSCATE("Open Keyboard"))) {
                            addAllGadgets = true;
                        }
                        SameLine();
                        if (Button(OBFUSCATE("Unlock"))) {
                            addAllGadgets = true;
                        }
                        SameLine();
                        TextUnformatted((std::string("Current Manual Unlock") +
                                         std::string(manualUnlockInput)).c_str());
                    });
            ImGuiMod::Group(OBFUSCATE("Misc Unlocker"), OBFUSCATE("#MiscUnlocker"),
                            {groupX, groupY * 0.5f}, [&] {
                        if (Button(OBFUSCATE("Unlock Gadgets"))) {
                            addAllGadgets = true;
                        }
                        SameLine();
                        if (Button(OBFUSCATE("Unlock Wears"))) {
                            unlockWear = true;
                        }
                        SameLine();
                        if (Button(OBFUSCATE("Unlock Pets"))) {
                            unlockPet = true;
                        }
                        /*if (Button(OBFUSCATE("Get Corrupted Snipers"))) {
                            corruptedSniper = true;
                        }
                        TextUnformatted("About Corrupted Sniper: "
                                        "\nAny player killed by Kill All "
                                        "\nwill get stuck on Kill-cam when you hold it."
                                        "\nBasically, a fancy version of crash all."
                                        "\n"
                                        "\nMake sure you don't unlock any weapons before.");*/
                    });
        });

        if (categorySelector == 3) {

            if (subTabSelector > 1)
                subTabSelector = 0;

            ImGuiMod::CategorySubTab(OBFUSCATE("UI"), 0, &subTabSelector, [&] {

                ImGuiMod::Group(OBFUSCATE("Menu Size"), OBFUSCATE("#MenuSize"), {groupX, groupY},
                                [&] {

                                    Combo(OBFUSCATE("Menu Resolution"), &resolutionIndex,
                                          resolutionVisual, IM_ARRAYSIZE(resolutionVisual));
                                    if (Button(OBFUSCATE("Apply"))) {

                                        applyPressed = true;
                                    }
                                    /*if (Button(OBFUSCATE("Change Title"))) {

                                        titleSelect = titleSelect + 1 % std::size(title);
                                    }*/
                                    Checkbox(OBFUSCATE("Resizable"), &freeResize);
                                    //TextUnformatted("Saved UI file location (delete to reset):\nandroid/data/com.pixelgun3d/files/uidata.json");
                                });
            });


            ImGuiMod::CategorySubTab("Credits", 1, &subTabSelector, [&] {

                ImGuiMod::Group("Thanks to", "#Credits", {groupX, groupY}, [&] {
                    TextUnformatted("Zygisk Source Code for most offsets");
                    TextUnformatted(
                            "coolmonke_ for giving zygisk offsets and helping with some stuff");
                    TextUnformatted(
                            "fedesito for mod template\ngithub.com/fedes1to/Zygisk-ImGui-Menu");
                    TextUnformatted(OBFUSCATE("And once again, created by soto_sapi1"));
                    if (Button("Join Our Discord")) {
                        discord = true;
                    }
                });
            });
        }


#ifdef DEVBUILD
        if (categorySelector == 4) {

            if (subTabSelector > 1)
                subTabSelector = 0;

            ImGuiMod::CategorySubTab("Placeholder", 0, &subTabSelector, [&] {

            });
        }
#endif
    }
}

bool defaultResized = false;
bool gex = false;

void DrawBase() {

    ImGuiStyle &style = GetStyle();

    if (!drawMenu) {

        Begin("Nazi Mod v1.51", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
        SetWindowSize(ImVec2(800 + style.ItemSpacing.x, 500));

        ImGui::Spacing();
        ImGui::Indent(ImGui::GetStyle().IndentSpacing / 4);
        TextUnformatted("Loading... (This might take a while)");
        End();
        return;
    }

    if (!gex) {
        SetWindowSize(ImVec2(800 + style.ItemSpacing.x, 500));
        gex = true;
    }

    if (!freeResize) {
#ifdef DEVBUILD

        Begin("Nazi Mod (TOP SECRET BUILD)", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
#else
        Begin("Nazi Mod v1.51", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
#endif
    } else {
#ifdef DEVBUILD

        Begin("Nazi Mod (TOP SECRET BUILD)", nullptr, ImGuiWindowFlags_NoScrollbar);
#else
        Begin("Nazi Mod v1.5", nullptr, ImGuiWindowFlags_NoScrollbar);
#endif
    }

    if (!defaultResized) {
        SetWindowSize(ImVec2(800 + style.ItemSpacing.x, 500));
        defaultResized = true;
    }

    if (applyPressed) {
        GImGui->Style = ImGuiModHelper::copiedStyle;
        switch (resolutionIndex) {

            case 0:
                SetWindowSize(ImVec2(600 + style.ItemSpacing.x, 400));
                style.ScaleAllSizes(0.5f);
                mainFont->Scale = 0.8f;
                //mainFont->FontSize = 5;
                resolutionMul = -1;
                subTabBarHeight = 40;
                break;
            case 1:
                SetWindowSize(ImVec2(800 + style.ItemSpacing.x, 500));
                style.ScaleAllSizes(1.0f);
                mainFont->Scale = 1.0f;
                //mainFont->FontSize = 25;
                resolutionMul = 0;
                subTabBarHeight = 50;
                break;
            case 2:
                SetWindowSize(ImVec2(1000 + style.ItemSpacing.x, 700));
                style.ScaleAllSizes(1.5f);
                mainFont->Scale = 1.1f;
                //mainFont->FontSize = 40;
                resolutionMul = 2;
                subTabBarHeight = 70;
                break;
            case 3:
                SetWindowSize(ImVec2(1400 + style.ItemSpacing.x, 1100));
                style.ScaleAllSizes(2.0f);
                mainFont->Scale = 1.6f;
                //mainFont->FontSize = 65;
                resolutionMul = 3;
                subTabBarHeight = 110;
                break;
        }
        applyPressed = false;
    }

    winSize = GetWindowSize();

    winY = winSize.y - (mainFont->FontSize + style.FramePadding.y * 2);
    winX = winSize.x;

    //winSize.y - (mainFont->FontSize + style.FramePadding.y * 2)
    //PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
    BeginChild("#CategorySelector", {winX / 4, winY * 1.20f}, false);
    {

        Spacing();
        PushFont(iconFont);
        PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.2f, 0.5f));
        PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        ImGuiMod::Category(ICON_FA_GAMEPAD "  Gameplay", 0, &categorySelector,
                           {winX / 4, winY * 0.10f});
        ImGuiMod::Category(ICON_FA_USERS "  Social  ", 1, &categorySelector,
                           {winX / 4, winY * 0.10f});
        ImGuiMod::Category(ICON_FA_ADDRESS_CARD "  Account", 2, &categorySelector,
                           {winX / 4, winY * 0.10f});
        ImGuiMod::Category(ICON_FA_COG "  Settings", 3, &categorySelector,
                           {winX / 4, winY * 0.10f});
#ifdef DEVBUILD
        ImGuiMod::Category(ICON_FA_FLASK "  Dev Stuff", 4, &categorySelector, {winX / 4, winY * 0.10f});
#endif
        PopStyleVar();
        PopStyleVar();
        PopFont();

        EndChild();

    }

    SameLine();

    PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
    PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
    BeginChild("#RightFrame", {(winX * 0.75f) - style.ItemSpacing.x * 2, winY * 1.10f}, false,
               ImGuiWindowFlags_NoScrollbar);
    {

        PopStyleColor();

        Spacing();

        BeginChild("#CategorySubTab", {(winX * 0.75f) - style.ItemSpacing.x * 2, subTabBarHeight},
                   false, ImGuiWindowFlags_NoScrollbar);
        {

            DrawMods();
            EndChild();

        }

        PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));

        BeginChild("#GroupFrame", {(winX * 0.75f) - style.ItemSpacing.x * 2, winY * 0.9f}, false);
        {

            PopStyleColor();

            if (ImGuiModHelper::CurrentSubTabDrawFunc != nullptr)
                ImGuiModHelper::CurrentSubTabDrawFunc();

            /*ImGuiMod::Group("Nigger sex", {300, 200}, [&] {
                Checkbox("kigger", &test);
            });*/

            EndChild();
        }

        PopStyleVar();
        EndChild();
    }
    End();
}