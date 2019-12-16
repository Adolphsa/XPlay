//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H

#include "XData.h"

/**
 * 解封装接口
 */
class IDemux {

public:
    //打开文件 或者流媒体 rtmp http rtsp
    virtual bool open(const char* url) = 0;

    //读取一帧数据  数据由调用者清理
    virtual XData read() = 0;
};


#endif //XPLAY_IDEMUX_H
