//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#include "XThread.h"
#include "XLog.h"
#include <thread>

using namespace std;

//启动线程
void XThread::start()
{
    thread th(&XThread::threadMain, this);
    th.detach();
}

void XThread::threadMain()
{
    XLOGI("线程函数进入");
    main();
    XLOGI("线程函数退出");
}

//通过控制isExit安全停止线程  (不一定成功)
void XThread::stop()
{

}