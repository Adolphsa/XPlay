//
// Created by ENABOT-LUCAS on 2019/12/17.
//

#include "IObserver.h"

//主体函数 添加观察者
void IObserver::addObserver(IObserver *observer)
{
    if (!observer)
        return;

    mutex.lock();
    observers.push_back(observer);
    mutex.unlock();
}

//通知所有观察者
void IObserver::notify(XData data)
{
    mutex.lock();
    for (int i = 0; i < observers.size(); ++i)
    {
        observers[i]->update(data);
    }
    mutex.unlock();

}