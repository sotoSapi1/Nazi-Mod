#include "android/log.h"

#define LOG_TAG "zyCheats"

#ifndef DEVBUILD

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define LOG_PROPLAM(msg, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "[PROPLAM | %s:%i] " msg, __FUNCTION__, __LINE__, ## __VA_ARGS__);
#define LOG_INFO(msg, ...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "[Info | %s:%i] " msg, __FUNCTION__, __LINE__, ## __VA_ARGS__)

#else

#define LOGD(...)
#define LOGW(...)
#define LOGE(...)
#define LOGI(...)

#define LOG_PROPLAM(msg, ...)
#define LOG_INFO(msg, ...)

#endif