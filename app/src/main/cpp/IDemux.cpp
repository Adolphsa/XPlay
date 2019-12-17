//
// Created by ENABOT-LUCAS on 2019/12/16.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::main()
{
    for(;;)
    {
        XData d = read();
        XLOGI("IDemux read %d", d.size);
        if (d.size <= 0)
            break;
    }
}