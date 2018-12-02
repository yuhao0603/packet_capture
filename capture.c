/*************************************************************************
	> File Name: capture.c
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年11月23日 星期五 19时19分10秒
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/in.h>
#include <linux/if_ether.h>
#include "base.h"
#include "error.h"
#include "proto.h"
#include "ip_opt.h"

#define HOST_NAME_MAX 128
#define RECV_MAX_LEN  2048
#define MAX_LINK      1000

char g_szHostName[HOST_NAME_MAX];

static int g_sockfd;
static void inline set_global_sock(int fd) 
{
    g_sockfd = fd;

    return ;
}

static int inline get_global_sock(int fd) 
{
    return g_sockfd;
}

int hostname_init(void)
{
    strcpy(g_szHostName, "172.0.0.1");

    return ERR_SUCCESS;
}

int socket_init(void)
{
    int sock;
    int real_len;
    TRANS_PROTO_E proto_type;
    char recv_buf[RECV_MAX_LEN + 1];

    bzero(recv_buf, RECV_MAX_LEN);

    #if 0
    if ((sock = socket(PF_PACKET, 
                      SOCK_RAW|SOCK_DGRAM, 
                      htons(ETH_P_IP|ETH_P_ARP|ETH_P_ALL))) < 0)
    #endif
    if ((sock = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_IP))) < 0)
    {
        printf("create sock failed\n");
        perror("socket()");
        return ERR_FAILED;
    }

    printf("create socketfd %d.\n", sock);
    printf("gonna capture IP packet.\n");
    set_global_sock(sock);

    while(1)
    {
        real_len = recv(sock, recv_buf, RECV_MAX_LEN, 0);
        if (real_len < 0)
        {
            perror("recv()");
            continue ;
        }
        printf("%d bytes read\n", real_len);

        if (IP_Parse(recv_buf, real_len, &proto_type) != ERR_SUCCESS)
        {
            continue ;
        }
    }

    return ERR_SUCCESS;
}

/* 销毁函数 */
void fini(void)
{
    return ;
}

/* 初始化函数 */
int init()
{
    int retval;
    retval |= hostname_init();
    retval |= socket_init();

    if (retval != ERR_SUCCESS)
    {
        fini();
    }

    return retval;
}

/* 主函数 */
int main(int argc, char *argv[])
{
    int retval = ERR_SUCCESS;
    retval |= init();

    if (ERR_SUCCESS != retval)
    {
        fini();
    }
}
