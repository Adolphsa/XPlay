//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#include "FFDemux.h"
#include "XLog.h"

//打开文件 或者流媒体 rtmp http rtsp
bool FFDemux::open(const char* url)
{
    XLOGI("start open %s ", url);
    return true;
}

//读取一帧数据  数据由调用者清理
XData FFDemux::read()
{

    XData d;
    return d;
}