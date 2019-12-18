//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H

#include "IDemux.h"

struct AVFormatContext;

class FFDemux: public IDemux{
public:

    //构造函数
    FFDemux();

    //打开文件 或者流媒体 rtmp http rtsp
    virtual bool open(const char* url);

    //获取视频参数
    virtual XParameter getVXParameter();

    //获取音频参数
    virtual XParameter getAXParameter();

    //读取一帧数据  数据由调用者清理
    virtual XData read();

private:
    //C++11 在构造函数是无参数的生效  构造函数有参数的时候赋值不生效
    AVFormatContext *ic = 0;

    int audioStream = 1;
    int videoStream =0;
};


#endif //XPLAY_FFDEMUX_H
