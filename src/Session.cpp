/*************************************************************************
	> File Name: Session.cpp
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 01时01分16秒
 ************************************************************************/

#include <iostream>
#include <netinet/in.h>
#include "../include/Session.h"

void Session::AddToSessionManager(void *header, int proto){
    switch(proto){
        case IPPROTO_TCP:{
            break;
        }
        case IPPROTO_UDP:{
            break;
        }
        default:{
            break;
        }
    }
}
