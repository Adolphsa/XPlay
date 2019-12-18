//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#ifndef XPLAY_XTHREAD_H
#define XPLAY_XTHREAD_H

//sleep 毫秒
void XSleep(int mis);

//C++ 11线程库
class XThread{
public:
    //启动线程
    virtual void start();

    //通过控制isExit安全停止线程  (不一定成功)
    virtual void stop();

    //入口主函数
    virtual void main(){}

protected:
    bool isExit = false;
    bool isRunning = false;
private:
    void threadMain();
};


#endif //XPLAY_XTHREAD_H
