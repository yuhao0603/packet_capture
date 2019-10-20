/*************************************************************************
	> File Name: base.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年12月02日 星期日 14时35分52秒
 ************************************************************************/

#ifndef _BASE_H
#define _BASE_H

#define ERR_MSG_MAX_LEN 127

typedef enum ErrCode{
    ERROR_SUCCESS = 0,
    ERROR_FAILED
}RET_E;

#define MyLog printf

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

typedef struct iphdr  IP_HEADER_S;
typedef struct tcphdr TCP_HEADER_S;
typedef struct udphdr UDP_HEADER_S;


#define MIN_IP_HEADER_LEN  sizeof(IP_HEADER_S)
#define UDP_HEADER_LEN     sizeof(UDP_HEADER_S)
#define TCP_HEADER_LEN     sizeof(TCP_HEADER_S)

#endif
