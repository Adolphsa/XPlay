#include <jni.h>
#include <string>

#include "FFDemux.h"
extern "C"{
#include <libavcodec/avcodec.h>
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_lucas_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "";
    hello += avcodec_configuration();

    IDemux *de = new FFDemux();
    de->open("/sdcard/NORM0001.MP4");

    return env->NewStringUTF(hello.c_str());
}
