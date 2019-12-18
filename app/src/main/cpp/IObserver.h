//
// Created by ENABOT-LUCAS on 2019/12/17.
//

#ifndef XPLAY_IOBSERVER_H
#define XPLAY_IOBSERVER_H

#include "XData.h"
#include "XThread.h"
#include <vector>
#include <mutex>

//观察者 和 主体
class IObserver:public XThread
{
public:
    //观察者接受数据函数
    virtual void update(XData data){}

    //主体函数 添加观察者(线程安全)
    void addObserver(IObserver *observer);

    //通知所有观察者(线程安全)
    void notify(XData data);

protected:
    std::vector<IObserver *>observers;
    std::mutex mutex;
};


#endif //XPLAY_IOBSERVER_H
