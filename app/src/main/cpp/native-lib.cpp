#include <jni.h>
#include <string>

#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"

extern "C"{
#include <libavcodec/avcodec.h>
}

class TestObs:public IObserver
{
public:
    void update(XData data)
    {
//        XLOGI("test update data size is %d",data.size);
    }
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_lucas_xplay_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "";
    hello += avcodec_configuration();

    ////////////////////////////////////
    //测试用代码
//    TestObs *tobs = new TestObs();
    IDemux *de = new FFDemux();
//    de->addObserver(tobs);
    de->open("/sdcard/NORM0001.MP4");

    IDecode *vdecode = new FFDecode();
    vdecode->open(de->getVXParameter());

    IDecode *adecode = new FFDecode();
    adecode->open(de->getAXParameter());

    de->addObserver(vdecode);
    de->addObserver(adecode);

    de->start();
    vdecode->start();
    adecode->start();

//    XSleep(3000);
//    de->stop();
    return env->NewStringUTF(hello.c_str());
}
