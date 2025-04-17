#include <jni.h>
#include <gst/gst.h>
#include <gio/gio.h>
#include <android/log.h>
#include <string>

static char const *TAG = "GStreamer";

static JavaVM *_java_vm = nullptr;

static jstring gst_native_get_gstreamer_info(JNIEnv *env, jobject thiz) {
    char *version_utf8 = gst_version_string();
    jstring version_jstring = env->NewStringUTF(version_utf8);
    g_free(version_utf8);
    return version_jstring;
}

/* List of implemented native methods */
static JNINativeMethod native_methods[] = {
        {"nativeGetGStreamerInfo", "()Ljava/lang/String;", (void *) gst_native_get_gstreamer_info}
};

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    _java_vm = vm;

    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Could not retrieve JNIEnv");
        return -1;
    }

    jclass klass = env->FindClass("me/longluo/gstreamer/MainActivity");
    if (!klass) {
        __android_log_print(ANDROID_LOG_ERROR, TAG,
                            "Could not retrieve class me.longluo.gstreamer.MainActivity");
        return -1;
    }

    if (env->RegisterNatives(klass, native_methods, G_N_ELEMENTS(native_methods))) {
        __android_log_print(ANDROID_LOG_ERROR, TAG,
                            "Could not register native methods for org.freedesktop.gstreamer.GStreamer");
        return -1;
    }

    return JNI_VERSION_1_6;
}