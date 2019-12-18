//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>

using namespace std;

void XSleep(int mis)
{
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

//启动线程
void XThread::start()
{
    isExit = false;
    thread th(&XThread::threadMain, this);
    th.detach();
}

void XThread::threadMain()
{
    XLOGI("线程函数进入");
    isRunning = true;
    main();
    isRunning = false;
    XLOGI("线程函数退出");
}

//通过控制isExit安全停止线程  (不一定成功)
void XThread::stop()
{
    isExit = true;
    for (int i = 0; i < 200; ++i)
    {
        if (!isRunning)
        {
            XLOGI("stop 停止线程成功");
            return;
        }
        XSleep(1);
    }
    XLOGI("stop 停止线程超时");
}