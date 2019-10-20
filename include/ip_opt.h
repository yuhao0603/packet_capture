/*************************************************************************
	> File Name: ip_opt.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年12月02日 星期日 15时02分56秒
 ************************************************************************/
#ifndef _IP_OPT_H
#define _IP_OPT_H
int IP_Check(IP_HEADER_S *p_ip_head);
int IP_Parse(char *buf, int *len, TRANS_PROTO_E *p_proto_type);
#endif
