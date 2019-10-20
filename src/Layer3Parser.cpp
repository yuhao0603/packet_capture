/*************************************************************************
	> File Name: Layer3Parser.cpp
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月19日 星期六 23时48分56秒
 ************************************************************************/
#include <string.h>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include "../public/base.h"
#include "../public/parser.h"
#include "../include/Session.h"
#include "../include/Layer3Parser.h"
#include "../include/TcpParser.h"

Layer3Parser::Layer3Parser(){
}

Layer3Parser::~Layer3Parser(){

}

RET_E Layer3Parser::check(char *buf, int len){
    if ((int)pstHeader->version != 4) {
        memset(errMsg, 0x0, sizeof(errMsg));
        sprintf(errMsg, "版本号为:%d, 不支持的ip协议版本\n", (int)pstHeader->version);
        return ERROR_FAILED;
    }
    else if((pstHeader->ihl * 8) < MIN_IP_HEADER_LEN) {
        memset(errMsg, 0x0, sizeof(errMsg));
        sprintf(errMsg, "ip包头长度有误:%d，丢包\n", pstHeader->ihl * 4);
        return ERROR_FAILED;
    }
    else if(pstHeader->ttl >= 64) {
        memset(errMsg, 0x0, sizeof(errMsg));
        sprintf(errMsg, "ttl = %d, 超时\n", (int)pstHeader->ttl);
        return ERROR_FAILED;
    }
    else{
        return ERROR_SUCCESS;
    }
}

void Layer3Parser::putPacketInfo(){
    printf("*******************************************\n");
    printf("****************IP HEADER******************\n");
    printf("*******************************************\n");
    printf("包头长度:%d\n", (int)pstHeader->ihl * 4);
    printf("Differentiated Services Field:%d\n", (int)pstHeader->tos);
    printf("ip包总长度:%d\n", (int)pstHeader->tot_len);
    printf("Identification:%d\n", (int)pstHeader->id);
    printf("ttl = %d\n", (int)pstHeader->ttl);

    struct in_addr src_ip;
    struct in_addr dst_ip;
    memcpy(&src_ip, &pstHeader->saddr, sizeof(src_ip));
    memcpy(&dst_ip, &pstHeader->daddr, sizeof(dst_ip));
    printf("四层协议类型id为:%d\n", (int)pstHeader->protocol);
    printf("源ip地址为:%s\n", inet_ntoa(src_ip));
    printf("目的ip地址为:%s\n", inet_ntoa(dst_ip));
    printf("\n\n");
}

RET_E Layer3Parser::nextLayerParse(char *buf, int buf_len){
    if (pstHeader == nullptr){
        return ERROR_FAILED;
    }
    int proto = pstHeader->protocol;
    switch(proto){
        case IPPROTO_TCP:{
            TcpParser tpParser;
            tpParser.parse(buf, buf_len);
            break;
        }
        default:{
            break;
        }
    }
    return ERROR_SUCCESS;
}

RET_E Layer3Parser::parse(char *buf, int buf_len){
    RET_E ret;
    if(buf_len <= sizeof(struct iphdr)){
        memset(errMsg, 0x0, sizeof(errMsg));
        strcpy(errMsg, "不是IP包");
        return ERROR_FAILED;
    }

    pstHeader = (struct iphdr *)buf;
    
    ret = check(buf, buf_len);
    if (ret != ERROR_SUCCESS){
        return ret;
    }
    
    putPacketInfo();
    char payload_len = buf_len - pstHeader->ihl * 4;
    char *payload = buf + pstHeader->ihl * 4;
    return nextLayerParse(payload, payload_len);
}

char *Layer3Parser::getErrMsg(){
    return this->errMsg;
}
