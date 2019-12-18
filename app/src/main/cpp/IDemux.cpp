//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::main()
{
    while (!isExit)
    {
        XData data = read();
        if (data.size > 0)
        {
            notify(data);
        }
//        XLOGI("IDemux read %d", d.size);
//        if (d.size <= 0)
//            break;
    }
}