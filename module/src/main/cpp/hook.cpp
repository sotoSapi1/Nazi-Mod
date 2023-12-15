#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/system_properties.h>
#include <dlfcn.h>
#include <dlfcn.h>
#include <cstdlib>
#include <cinttypes>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <fstream>
#include <limits>
#include <iostream>
#include <chrono>

#include "obfuscate.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_android.h"
#include "KittyMemory.h"
#include "MemoryPatch.h"
#include "KittyScanner.h"
#include "KittyUtils.h"
#include "Includes/Dobby/dobby.h"
#include "Unity.h"
#include "utils/json.hpp"
#include "moment/vars.h"
#include "utils/logger.h"
#include "moment/lists.h"

#include "Misc.h"
#include "hook.h"
#include "Include/Roboto-Regular.h"
#include "Include/Quaternion.h"
#include "Include/Rect.h"
#include "Asset/FontAwesome.h"

#include "utils/parrallel.h"

#include "xdl.h"
#include "il2cpp-types.h"
#include "il2cpp-utils.h"

#include "moment/functions.h"
#include "moment/menu.h"

#define GamePackageName "com.pixel.gun3d" // define the game package name here please

int glHeight, glWidth;

int isGame(JNIEnv *env, jstring appDataDir) {
    if (!appDataDir)
        return 0;
    const char *app_data_dir = env->GetStringUTFChars(appDataDir, nullptr);
    int user = 0;
    static char package_name[256];
    if (sscanf(app_data_dir, "/data/%*[^/]/%d/%s", &user, package_name) != 2) {
        if (sscanf(app_data_dir, "/data/%*[^/]/%s", package_name) != 1) {
            package_name[0] = '\0';
            LOGW(OBFUSCATE("can't parse %s"), app_data_dir);
            return 0;
        }
    }
    if (strcmp(package_name, GamePackageName) == 0) {
        LOGI(OBFUSCATE("detect game: %s"), package_name);
        game_data_dir = new char[strlen(app_data_dir) + 1];
        strcpy(game_data_dir, app_data_dir);
        env->ReleaseStringUTFChars(appDataDir, app_data_dir);
        return 1;
    } else {
        env->ReleaseStringUTFChars(appDataDir, app_data_dir);
        return 0;
    }
}

bool setupimg;

void Styling() {
    // nazimod style from ImThemes
    ImGuiStyle &style = GetStyle();

    style.Alpha = 1.0f;
    style.DisabledAlpha = 1.0f;
    style.WindowBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(4.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ChildRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.TabRounding = 0.0f;
    style.TabMinWidthForCloseButton = 0.0f;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.SelectableTextAlign = ImVec2(0.0f, 0.0f);
    style.ScrollbarSize = 8.0f;
    style.WindowPadding = ImVec2(0, 0);
    style.Colors[ImGuiCol_Text] = ImVec4(0.8980392217636108f, 0.8980392217636108f,
                                         0.8980392217636108f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.6000000238418579f, 0.6000000238418579f,
                                                 0.6000000238418579f, 1.0f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.65f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1098039224743843f, 0.1098039224743843f,
                                            0.1372549086809158f, 0.9200000166893005f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.4980392158031464f, 0.4980392158031464f,
                                           0.4980392158031464f, 0.0f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.5882353186607361f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4666666686534882f, 0.4666666686534882f,
                                                   0.686274528503418f, 0.4000000059604645f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.4196078479290009f, 0.407843142747879f,
                                                  0.6392157077789307f, 0.6899999976158142f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.4470588266849518f, 0.4470588266849518f,
                                            0.8980392217636108f, 1.0f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.4470588266849518f, 0.4470588266849518f,
                                                  0.8980392217636108f, 1.0f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(9.999899930335232e-07f, 9.999899930335232e-07f,
                                                     9.999999974752427e-07f, 0.2000000029802322f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.4000000059604645f, 0.4000000059604645f,
                                              0.5490196347236633f, 0.800000011920929f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(9.999899930335232e-07f, 9.999947678807075e-07f,
                                                9.999999974752427e-07f, 0.6000000238418579f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.4000000059604645f, 0.4000000059604645f,
                                                  0.800000011920929f, 0.300000011920929f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.4000000059604645f, 0.4000000059604645f,
                                                         0.800000011920929f, 0.4000000059604645f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.407843142747879f, 0.3882353007793427f,
                                                        0.800000011920929f, 0.6000000238418579f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.5145097970962524f, 0.5145097970962524f,
                                              0.800000011920929f, 1.0f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.2995617389678955f, 0.2995617389678955f,
                                               0.5921568870544434f, 1.0f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5137255191802979f, 0.5137255191802979f,
                                                     0.800000011920929f, 1.0f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 0.5882353186607361f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4000000059604645f, 0.47843137383461f,
                                                  0.7098039388656616f, 0.7900000214576721f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.4588235318660736f, 0.5372549295425415f,
                                                 0.800000011920929f, 1.0f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.7058823704719543f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.4470588266849518f, 0.4470588266849518f,
                                                  0.8980392217636108f, 0.800000011920929f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.529411792755127f, 0.529411792755127f,
                                                 0.8666666746139526f, 0.800000011920929f);
    style.Colors[ImGuiCol_Separator] = ImVec4(0.4039215743541718f, 0.4039215743541718f,
                                              0.7254902124404907f, 1.0f);
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.6000000238418579f, 0.6000000238418579f,
                                                     0.6980392336845398f, 1.0f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.6980392336845398f, 0.6980392336845398f,
                                                    0.8980392217636108f, 1.0f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.4470588266849518f, 0.4470588266849518f,
                                               0.8980392217636108f, 0.75f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4470588266849518f, 0.4470588266849518f,
                                                      0.8980392217636108f, 0.75);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.6665743589401245f, 0.6665743589401245f,
                                                     0.9882352948188782f, 0.75);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.3333333432674408f, 0.3333333432674408f,
                                        0.6823529601097107f, 0.9570815563201904f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.4470588266849518f, 0.4470588266849518f,
                                               0.8980392217636108f, 0.9871244430541992f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.4039215743541718f, 0.4039215743541718f,
                                              0.7254902124404907f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.2823529541492462f, 0.2823529541492462f,
                                                 0.5686274766921997f, 1.0f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.3490196168422699f, 0.3490196168422699f,
                                                       0.6509804129600525f, 1.0f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f,
                                                     1.0f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f,
                                                  1.0f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.2666666805744171f, 0.2666666805744171f,
                                                  0.3764705955982208f, 1.0f);
    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f,
                                                      0.4470588266849518f, 1.0f);
    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2588235437870026f, 0.2588235437870026f,
                                                     0.2784313857555389f, 1.0f);
    style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.07000000029802322f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.0f, 1.0f, 0.3499999940395355f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.4470588266849518f, 0.4470588266849518f,
                                                 0.8980392217636108f, 0.800000011920929f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f,
                                                      0.800000011920929f, 0.2000000029802322f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.2000000029802322f, 0.2000000029802322f,
                                                     0.2000000029802322f, 0.3499999940395355f);
}

HOOKAF(void, Input, void *thiz, void *ex_ab, void *ex_ac) {
    origInput(thiz, ex_ab, ex_ac);
    ImGui_ImplAndroid_HandleInputEvent((AInputEvent *) thiz);
    return;
}

void SetupImgui() {
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO &io = GetIO();
    io.DisplaySize = ImVec2((float) glWidth, (float) glHeight);
    ImGui_ImplOpenGL3_Init("#version 100");
    Styling();
    //GetStyle().ScaleAllSizes(7.0f);
    mainFont = io.Fonts->AddFontFromMemoryTTF(Roboto_Regular, 20, 20);

    static const ImWchar iconRanges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
    ImFontConfig iconConfig;
    iconConfig.MergeMode = true;
    iconConfig.PixelSnapH = true;
    iconConfig.OversampleH = 3;
    iconConfig.OversampleV = 3;

    iconFont = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 25,
                                                        &iconConfig, iconRanges);

    // FIXME: Put some effort into DPI awareness
    ImGui::GetStyle().ScaleAllSizes(4.0f);

    ImGuiModHelper::copiedStyle = GImGui->Style;

}

EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
    if (!setupimg) {
        SetupImgui();
        setupimg = true;
    }

    ImGuiIO &io = GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    NewFrame();

    DrawBase();
    Patches();
    EndFrame();
    Render();
    glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
    return old_eglSwapBuffers(dpy, surface);
}

void *hack_thread(void *arg) {

    LOGI("hack thread injected");

    auto il2cppHandle = xdl_open(OBFUSCATE("libil2cpp.so"), 0);

    while(il2cppHandle == nullptr) {
        il2cppHandle = xdl_open(OBFUSCATE("libil2cpp.so"), 0);
        sleep(1);
    }

    /*if (il2cppHandle == nullptr) {
        LOG_PROPLAM("Can't open il2cpp lib");
    }*/

    auto eglhandle = dlopen("libunity.so", RTLD_LAZY);
    auto eglSwapBuffers = dlsym(eglhandle, "eglSwapBuffers");
    DobbyHook((void *) eglSwapBuffers, (void *) hook_eglSwapBuffers,
              (void **) &old_eglSwapBuffers);
    void *sym_input = DobbySymbolResolver(("/system/lib/libinput.so"),
                                          ("_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE"));
    if (NULL != sym_input) {
        DobbyHook(sym_input, (void *) myInput, (void **) &origInput);
    }

    init_il2cpp_api(il2cppHandle);
    if (il2cpp_domain_get_assemblies != nullptr) {

        Dl_info dlInfo;
        if (dladdr((void *) il2cpp_domain_get_assemblies, &dlInfo)) {
            il2cpp_base = reinterpret_cast<uint64_t>(dlInfo.dli_fbase);
        }

        while (!il2cpp_is_vm_thread(nullptr)) {
            sleep(1);
        }

        sleep(10);

        domain = il2cpp_domain_get();
        il2cpp_thread_attach(domain);
        LibImages.Corlib = il2cpp_get_corlib();
        libs = il2cpp_domain_get_assemblies(domain, &libCount);

        for (int i = 0; i < libCount; ++i) {
            const Il2CppImage *img = il2cpp_assembly_get_image(libs[i]);
            const char *img_name = il2cpp_image_get_name(img);
            if (strcmp(img_name, OBFUSCATE("Assembly-CSharp.dll")) == 0) {
                LibImages.AssemblyCSharp = img;
            }
            if (strcmp(img_name, OBFUSCATE("UnityEngine.CoreModule.dll")) == 0) {
                LibImages.UnityCoreModule = img;
            }
        }

        DEFAULTS_INIT(Byte, "System", "Byte");
        DEFAULTS_INIT(Int16, "System", "Int16");
        DEFAULTS_INIT(Int32, "System", "Int32");
        DEFAULTS_INIT(Int64, "System", "Int64");
        DEFAULTS_INIT(Float, "System", "Single");
        DEFAULTS_INIT(Double, "System", "Double");
        DEFAULTS_INIT(Char, "System", "Char");
        DEFAULTS_INIT(String, "System", "String");
        DEFAULTS_INIT(Object, "System", "Object");
        DEFAULTS_INIT(Array, "System", "Array");

        LOGI("Il2cpp api initialized");

    } else {
        LOG_PROPLAM("fail to initialize il2cpp.");
    }

    LOG_INFO("Finding classes");

    size_t Corlib_classCount = il2cpp_image_get_class_count(LibImages.Corlib);
    LOG_INFO("Scanning Corlib | %zu classes detected", Corlib_classCount);
    for(int j = 0; j < Corlib_classCount; j++) {
        auto klass = il2cpp_image_get_class(LibImages.Corlib, j);
        auto type = il2cpp_class_get_type(const_cast<Il2CppClass *>(klass));

        CorlibLoad(il2cpp_class_from_type(type));
    }

    size_t UnityCoreModule_classCount = il2cpp_image_get_class_count(LibImages.UnityCoreModule);
    LOG_INFO("Scanning UnityCoreModule | %zu classes detected", UnityCoreModule_classCount);
    for(int j = 0; j < UnityCoreModule_classCount; j++) {
        auto klass = il2cpp_image_get_class(LibImages.UnityCoreModule, j);
        auto type = il2cpp_class_get_type(const_cast<Il2CppClass *>(klass));

        UnityCoreLoad(il2cpp_class_from_type(type));
    }

    size_t AssemblyCSharp_classCount = il2cpp_image_get_class_count(LibImages.AssemblyCSharp);
    LOG_INFO("Scanning AssemblyCSharp | %zu classes detected", AssemblyCSharp_classCount);
    for(int j = 0; j < AssemblyCSharp_classCount; j++) {
        auto klass = il2cpp_image_get_class(LibImages.AssemblyCSharp, j);
        auto type = il2cpp_class_get_type(const_cast<Il2CppClass *>(klass));

        ObfuscatedLoad(il2cpp_class_from_type(type));
    }

    il2cppApiLoaded = true;

    LOG_INFO("Done");

    Pointers();
    Hooks();
    LoadPatch();

    LOGI("Everything Done!");
    drawMenu = true;
    return nullptr;
}
