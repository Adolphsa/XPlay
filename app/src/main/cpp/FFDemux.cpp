//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#include "FFDemux.h"
#include "XLog.h"

extern "C"
{
#include "libavformat/avformat.h"
}

FFDemux::FFDemux()
{
    static bool isFirst = true;
    if (isFirst){

        isFirst = false;

        //注册所有封装器
        av_register_all();

        //注册所有的解码器
        avcodec_register_all();

        //初始化网络
        avformat_network_init();
        XLOGI("register ffmpeg");
    }
}

//打开文件 或者流媒体 rtmp http rtsp
bool FFDemux::open(const char* url)
{
    XLOGI("start open %s ", url);
    int re = avformat_open_input(&ic, url, 0, 0);
    if (re != 0)
    {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGI("FFDemux open %s failed", url);
        return false;
    }
    XLOGI("FFDemux open success");

    //获取文件信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0)
    {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        XLOGI("FFDemux avformat_find_stream_info %s failed", url);
        return false;
    }

    //这个值不一定有
    this->totalMs = ic->duration/(AV_TIME_BASE/1000);
    XLOGI("totalMs = %d", totalMs);

    return true;
}

//读取一帧数据  数据由调用者清理
XData FFDemux::read()
{
    if (!ic)
        return XData();
    XData d;
    AVPacket *pkt = av_packet_alloc();
    int re = av_read_frame(ic, pkt);
    if (re != 0)
    {
        av_packet_free(&pkt);
        return XData();
    }

    XLOGI("pack size id %d, pts is %lld", pkt->size, pkt->pts);
    d.data = (unsigned char *)pkt;
    d.size = pkt->size;

    return d;
}
