//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#ifndef XPLAY_IDEMUX_H
#define XPLAY_IDEMUX_H

#include "XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"

/**
 * 解封装接口
 */
class IDemux: public IObserver{

public:
    //打开文件 或者流媒体 rtmp http rtsp
    virtual bool open(const char* url) = 0;

    //获取视频参数
    virtual XParameter getVXParameter() = 0;
    //获取音频参数
    virtual XParameter getAXParameter() = 0;

    //读取一帧数据  数据由调用者清理
    virtual XData read() = 0;

    //总时长 （毫秒）
    int totalMs = 0;

protected:
    virtual void main();
};


#endif //XPLAY_IDEMUX_H
