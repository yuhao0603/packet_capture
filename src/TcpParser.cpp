/*************************************************************************
	> File Name: TcpParser.cpp
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 19时33分44秒
 ************************************************************************/

#include <iostream>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#include "../public/base.h"
#include "../public/parser.h"
#include "../include/Session.h"
#include "../include/TcpParser.h"

RET_E TcpParser::check(char *buf, int len){
    if (len < sizeof(TCP_HEADER_S)){
        strcpy(errMsg, "tcp 头部长度有误");
        return ERROR_FAILED;
    }
    return ERROR_SUCCESS;
}

void TcpParser::SessionProcess(){
    //Session *s = Session::getInstance();
    //s->AddToSessionManager((void *)pstHeader, IPPROTO_TCP);
}

RET_E TcpParser::parse(char *buf, int len){
    pstHeader = (TCP_HEADER_S *)buf;
    SessionProcess();
    payload = buf + (pstHeader->th_off * 8);
    payload_len = len - (pstHeader->th_off * 8);
    putPacketInfo();
    return nextLayerParse(payload, payload_len);
}

RET_E TcpParser::nextLayerParse(char *buf, int len){
    return ERROR_SUCCESS;
}

void TcpParser::putPacketInfo(){
    if (pstHeader == nullptr){
        return;
    }

    if (pstHeader->syn == 1){
        printf("首包\n");
    }
    
    printf("****************TCP HEADER*****************\n");
    printf("源端口为:%d\n", (int)ntohs(pstHeader->th_sport));
    printf("目的端口为:%d\n", (int)ntohs(pstHeader->th_dport));
    printf("确认号为:%u\n", (unsigned int)ntohl(pstHeader->ack_seq));
    printf("序号为:%u\n", (unsigned int)ntohl(pstHeader->seq));
    printf("\n\n");
}

char *TcpParser::getErrMsg(){
    return errMsg;
}
