/*************************************************************************
	> File Name: protocol.cpp
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月19日 星期六 21时14分13秒
 ************************************************************************/

#ifndef _PRASER_H_
#define _PRASER_H_
class Parser{
public:
    virtual RET_E check(char *buf, int len) = 0;
    virtual RET_E parse(char *buf, int len) = 0;
    virtual RET_E nextLayerParse(char *buf, int len) = 0;
    virtual void putPacketInfo() = 0;
    virtual char *getErrMsg() = 0;
};
#endif
