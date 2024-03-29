//
// Created by ENABOT-LUCAS on 2019/12/17.
//

#ifndef XPLAY_FFDECODE_H
#define XPLAY_FFDECODE_H


#include "XParameter.h"
#include "IDecode.h"

struct AVCodecContext;
struct AVFrame;

class FFDecode:public IDecode
{
public:
    virtual bool open(XParameter parameter);

    //future模型 发送数据到线程解码
    virtual bool sendPacket(XData pkt);
    //从线程中获取解码结果 再次调用会复用上次空间，线程不安全
    virtual XData recvFrame();

protected:
    AVCodecContext *avCodecContext = 0;
    AVFrame *frame = 0;
    int MAX_THREAD_COUNT = 8;
};


#endif //XPLAY_FFDECODE_H
