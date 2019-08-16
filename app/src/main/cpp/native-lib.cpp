#include <jni.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <jni.h>
#include <android/log.h>
#include "xhook/xhook.h"

#define  LOG_TAG    "HOOOOOOOOK"
#define  ALOG(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
typedef void *hook_func;

static int my_system_log_print(int prio, const char *tag, const char *fmt, ...) {
    va_list ap;
    char buf[1024];
    int r;

    snprintf(buf, sizeof(buf), "[%s] %s", (NULL == tag ? "" : tag), (NULL == fmt ? "" : fmt));

    va_start(ap, fmt);
    r = __android_log_vprint(prio, "xhook_system", buf, ap);
    va_end(ap);
    return r;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_myapplication_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {

    xhook_register("^/system/.*\\.so$", "__android_log_print", (hook_func) &my_system_log_print, NULL);
    xhook_register("^/vendor/.*\\.so$", "__android_log_print", (hook_func) &my_system_log_print, NULL);
    //just for testing
    xhook_ignore(".*/liblog\\.so$", "__android_log_print"); //ignore __android_log_print in liblog.so
    xhook_ignore(".*/libjavacore\\.so$", NULL); //ignore all hooks in libjavacore.so

    //xhook_register("libart.so", "pthread_create", (hook_func) &pthread_create_hook, NULL);
    xhook_refresh(1);
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}




