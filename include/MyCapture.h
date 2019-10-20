/*************************************************************************
	> File Name: capture.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2019年10月20日 星期日 00时44分40秒
 ************************************************************************/

#ifndef _CAPTURE_H
#define _CAPTURE_H

#define RECV_MAX_LEN  65534
#define INVALID_SOCK  -1

class MyCapture{
private:
    int sock = INVALID_SOCK;
    Layer2Parser *l2Parser = NULL; // 只解析IP包

public:
    MyCapture();
    ~MyCapture();

    RET_E Init(void);

    /* 核心业务处理流程 */
    void PacketCaptureStart();
};
#endif
