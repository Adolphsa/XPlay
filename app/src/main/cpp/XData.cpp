//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#include "XData.h"

extern "C"
{
#include "libavformat/avformat.h"
}


void XData::drop()
{
    if (!data) return;
    av_packet_free((AVPacket **)&data);
    data = 0;
    size = 0;
}