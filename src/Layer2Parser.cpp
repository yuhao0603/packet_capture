/*************************************************************************
	> File Name: Layer2Parser.cpp
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 12时21分42秒
 ************************************************************************/

#include <iostream>
#include <string.h>
#include "../public/base.h"
#include "../public/parser.h"
#include "../include/Layer2Parser.h"
#include "../include/Layer3Parser.h"
Layer2Parser::Layer2Parser(){
}

Layer2Parser::~Layer2Parser(){
}

RET_E Layer2Parser::check(char *buf, int len){
    if (len <= 14){
        strcpy(errMsg, "以太网头有误.\n");
        return ERROR_FAILED;
    }
    return ERROR_SUCCESS;
}

RET_E Layer2Parser::parse(char *buf, int len){
    RET_E ret;
    ret = check(buf, len);
    if(ERROR_SUCCESS != ret){
        return ret;
    }

    char *payload = buf + 14;
    char payload_len = len - 14;
    return nextLayerParse(payload, payload_len);
}

RET_E Layer2Parser::nextLayerParse(char *buf, int len){
    Layer3Parser *l3Parser = new Layer3Parser();
    l3Parser->parse(buf, len);
    delete(l3Parser);
}

char *Layer2Parser::getErrMsg(){
    return errMsg;
}

void Layer2Parser::putPacketInfo(){
    printf("L2\n");
}

