
#ifndef ZygiskImGui_HOOK_H
#define ZygiskImGui_HOOK_H

#include <jni.h>

static int enable_hack;
static char *game_data_dir = NULL;

int isGame(JNIEnv *env, jstring appDataDir);

void *hack_thread(void *arg);

#define HOOKAF(ret, func, ...) \
    ret (*orig##func)(__VA_ARGS__); \
    ret my##func(__VA_ARGS__)

#endif //ZygiskImGui_HOOK_H