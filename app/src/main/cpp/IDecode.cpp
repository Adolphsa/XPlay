//
// Created by ENABOT-LUCAS on 2019/12/17.
//

#include "IDecode.h"
#include "XLog.h"

void IDecode::update(XData pkt)
{
    if (pkt.isAudio != isAudio)
    {
        return;
    }

    while (!isExit)
    {
        packsMutex.lock();
        //阻塞
        if (packs.size() < maxList)
        {
            //生产者
            packs.push_back(pkt);
            packsMutex.unlock();
            break;
        }
        packsMutex.unlock();
        XSleep(1);
    }

}

void IDecode::main()
{
    while (!isExit)
    {
        packsMutex.lock();
        if (packs.empty())
        {
            packsMutex.unlock();
            XSleep(1);
            continue;
        }

        //取出packet 消费者
        XData pack = packs.front();
        packs.pop_front();

        //发送数据到解码线程 一个数据包，可能解码多个结果
        if (this->sendPacket(pack))
        {
            while (!isExit)
            {
                //获取解码数据
                XData frame = recvFrame();
                if (!frame.data) break;
                //发送数据给观察者
                XLOGI("recv frame size %d", frame.size);
                this->notify(frame);
            }

        }
        pack.drop();
        packsMutex.unlock();
    }

}