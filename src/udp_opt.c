/*************************************************************************
	> File Name: udp_opt.c
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年12月05日 星期三 20时38分14秒
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include "base.h"
#include "error.h"
#include "proto.h"

int UDP_Parse(char *recv_buf, int buf_len)
{
    UDP_HEADER_S *udp_hdr = NULL;
    int retval            = ERR_SUCCESS;

    assert(recv_buf != NULL);

    if (buf_len < UDP_HEADER_LEN)
    {
        printf("incomplete udp packet\n");
        return ERR_FAILED;
    }
    
    udp_hdr = (UDP_HDEAR_S *)recv_buf;
    printf("******************************************\n");
    printf("****************UDP HEADER****************\n");
    printf("******************************************\n");
    printf("源端口号:%d\n", ntohs(udp_hdr->src_port));
    printf("目的端口号:%d\n", ntohs(udp_hdr->dst_port));
    printf("数据长度为:%d\n", ntohs(udp_hdr->data_len));
}
