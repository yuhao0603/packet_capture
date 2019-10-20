/*************************************************************************
	> File Name: capture.c
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年11月23日 星期五 19时19分10秒
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include "../public/base.h"
#include "../public/parser.h"
#include "../include/Session.h"
#include "../include/Layer2Parser.h"
#include "../include/MyCapture.h"

MyCapture::MyCapture(){

}

MyCapture::~MyCapture(){
    if (l2Parser != NULL){
        delete(l2Parser);
    }
    if (sock != INVALID_SOCK){
        close(sock);
    }
}

RET_E MyCapture::Init(void){
    l2Parser = new Layer2Parser();
    if ((this->sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0) {
        MyLog("Create raw sock failed\n");
        perror("sock ");
        return ERROR_FAILED;
    }
}

/* 核心业务处理流程 */
void MyCapture::PacketCaptureStart(){
    int real_len;
    char recv_buf[RECV_MAX_LEN + 1];

    while(1) {
        memset(recv_buf, 0x0, sizeof(recv_buf));
        real_len = recvfrom(sock, recv_buf, RECV_MAX_LEN+1, 0, NULL, NULL);
        if (ERROR_SUCCESS != l2Parser->parse(recv_buf, real_len)){
            MyLog("real_len is %d.\n", real_len);
            MyLog("l2Parser parse a packet failed, because of %s.\n", l2Parser->getErrMsg());
        }
    }
}
