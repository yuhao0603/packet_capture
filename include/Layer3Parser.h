/*************************************************************************
	> File Name: Layer3Parser.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 00时39分49秒
 ************************************************************************/

#ifndef _LAYER3PARSER_H
#define _LAYER3PARSER_H

#include <netinet/ip.h>

class Layer3Parser:public Parser{
private:
    struct iphdr *pstHeader;
    char errMsg[ERR_MSG_MAX_LEN+1];
public:
    Layer3Parser();
    ~Layer3Parser();
    RET_E check(char *buf, int len);
    void putPacketInfo();
    RET_E nextLayerParse(char *buf, int buf_len);
    RET_E parse(char *buf, int buf_len);
    char *getErrMsg();
};
#endif
