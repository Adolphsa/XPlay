//
// Created by ENABOT-LUCAS on 2019/12/17.
//

extern "C"
{
#include <libavcodec/avcodec.h>
}

#include "FFDecode.h"
#include "XLog.h"

bool FFDecode::open(XParameter parameter)
{
    if (!parameter.para)
        return false;

    AVCodecParameters *p = parameter.para;

    //1.查找解码器
    AVCodec *avCodec = avcodec_find_decoder(p->codec_id);
    if (!avCodec)
    {
        XLOGI("avcodec_find_decoder %d failed!", p->codec_id);
        return false;
    }
    XLOGI("avcodec_find_decoder success!");

    //2.创建解码上下文，并复制参数
    avCodecContext = avcodec_alloc_context3(avCodec);
    avcodec_parameters_to_context(avCodecContext, p);
    avCodecContext->thread_count = MAX_THREAD_COUNT;

    //3.打开解码器
    int re = avcodec_open2(avCodecContext, 0, 0);
    if (re != 0)
    {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf)-1);
        XLOGI("avcodec_open2 failed %s",buf);
        return false;
    }

    if (avCodecContext->codec_type == AVMEDIA_TYPE_VIDEO)
    {
        this->isAudio = false;

    } else if (avCodecContext->codec_type == AVMEDIA_TYPE_AUDIO)
    {
        this->isAudio = true;
    }

    XLOGI("avcodec_open2 success!");
    return true;
}

//future模型 发送数据到线程解码
bool FFDecode::sendPacket(XData pkt)
{
    if (pkt.size <= 0 || !pkt.data)
    {
        return false;
    }

    if (!avCodecContext)
    {
        return false;
    }

    int re = avcodec_send_packet(avCodecContext, (AVPacket*)pkt.data);
    if (re != 0)
    {
        return false;
    }

    return true;
}

//从线程中获取解码结果
XData FFDecode::recvFrame()
{
    if (!avCodecContext)
    {
        return XData();
    }

    if (!frame)
    {
        frame = av_frame_alloc();
    }

    int re =avcodec_receive_frame(avCodecContext, frame);
    if (re != 0)
    {
        return XData();
    }

    XData d;
    d.data = (unsigned char*)frame;
    if (avCodecContext->codec_type == AVMEDIA_TYPE_VIDEO)
    {
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2])*frame->height;
    } else if(avCodecContext->codec_type == AVMEDIA_TYPE_AUDIO)
    {
        //样本字节数 * 单通道样本数 * 通道数
        d.size = av_get_bytes_per_sample((AVSampleFormat)frame->format)*frame->nb_samples*2;
    }

    return d;
}