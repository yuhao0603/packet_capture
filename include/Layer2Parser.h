/*************************************************************************
	> File Name: Layer2Parser.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 12时19分57秒
 ************************************************************************/

#ifndef _LAYER2PARSER_H
#define _LAYER2PARSER_H
class Layer2Parser:public Parser{
private:
    char errMsg[ERR_MSG_MAX_LEN+1];
public:
    Layer2Parser();
    ~Layer2Parser();
    RET_E check(char *buf, int len);
    RET_E parse(char *buf, int len);
    RET_E nextLayerParse(char *buf, int len);
    void putPacketInfo();
    char *getErrMsg();
};
#endif
