/*************************************************************************
	> File Name: main.cpp
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 01时06分46秒
 ************************************************************************/

#include <iostream>
#include <netinet/ip.h>
#include "../public/base.h"
#include "../public/parser.h"
#include "../include/Session.h"
#include "../include/Layer2Parser.h"
#include "../include/Layer3Parser.h"
#include "../include/MyCapture.h"
using namespace std;

int main(){
    MyCapture *c = new MyCapture();
    if(ERROR_SUCCESS == c->Init()) {
        c->PacketCaptureStart();
    }
    delete(c);
}
