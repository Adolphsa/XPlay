//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#ifndef XPLAY_FFDEMUX_H
#define XPLAY_FFDEMUX_H


#include "IDemux.h"

class FFDemux: public IDemux{
public:
    //打开文件 或者流媒体 rtmp http rtsp
    virtual bool open(const char* url);

    //读取一帧数据  数据由调用者清理
    virtual XData read();

};


#endif //XPLAY_FFDEMUX_H
