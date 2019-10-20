/*************************************************************************
	> File Name: ../include/TcpParser.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 19时34分23秒
 ************************************************************************/

#ifndef _TCPPARSER_H
#define _TCPPARSER_H
class TcpParser:public Parser{
private:
    char *payload;
    char payload_len;
    char errMsg[ERR_MSG_MAX_LEN+1];
    TCP_HEADER_S *pstHeader;
public:
    RET_E check(char *buf, int len);
    RET_E parse(char *buf, int len);
    RET_E nextLayerParse(char *buf, int len);
    void SessionProcess();
    void putPacketInfo();
    char *getErrMsg();
};
#endif
