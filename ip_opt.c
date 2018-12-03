/*************************************************************************
	> File Name: ip_opt.c
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年12月02日 星期日 14时53分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include "base.h"
#include "error.h"
#include "proto.h"

#define IP_STR_LEN 63

typedef struct tag_IPAddr{
  #if __BYTE_ORDER == __BIG_ENDIAN
    uint one:8;
    uint two:8;
    uint three:8;
    uint four:8;
  #elif __BYTE_ORDER == __LITTLE_ENDIAN
    uint four:8;
    uint three:8;
    uint two:8;
    uint one:8;
  #else
    # error	"Please fix <bits/endian.h>"
  #endif
}IP_ADDR;

void int_converto_ip(uint ip, char *str)
{
    printf("ip = %x\n", ip);
    IP_ADDR stIP;
    char    tmp_str[16];
    int     tmp_len = 0;

    bzero(&stIP, sizeof(IP_ADDR));
    memcpy(&stIP, &ip, sizeof(uint));

    sprintf(tmp_str, "%d", stIP.one);
    tmp_len = strlen(tmp_str);
    tmp_str[tmp_len] = '.';
    tmp_str[tmp_len + 1] = '\0';
    strcat(str, tmp_str);
    bzero(tmp_str, 16);

    sprintf(tmp_str, "%d", stIP.two);
    tmp_len = strlen(tmp_str);
    tmp_str[tmp_len] = '.';
    tmp_str[tmp_len + 1] = '\0';
    strcat(str, tmp_str);
    bzero(tmp_str, 16);

    sprintf(tmp_str, "%d", stIP.three);
    tmp_len = strlen(tmp_str);
    tmp_str[tmp_len] = '.';
    tmp_str[tmp_len + 1] = '\0';
    strcat(str, tmp_str);
    bzero(tmp_str, 16);

    sprintf(tmp_str, "%d", stIP.four);
    strcat(str, tmp_str);

    return ;
}

static void cal_trans_proto(int proto_id, TRANS_PROTO_E *proto_type)
{
    if (proto_id == 6)
    {
        *proto_type = PROTO_TCP;
    }
    else if (proto_id == 8)
    {
        *proto_type = PROTO_UDP;
    }
    else
    {
        printf("暂不支持tcp、udp之外的运输层协议");
    }
}


int IP_Check(IP_HEADER_S *p_ip_head)
{
    if ((int)p_ip_head->version != 4) {
        printf("版本号为:%d, 不支持的ip协议版本\n", (int)p_ip_head->version);
        return ERR_FAILED;
    }
    else if((p_ip_head->head_len * 4) != MIN_IP_HEADER_LEN) {
        printf("ip包头长度有误:%d，丢包\n", p_ip_head->head_len * 4);
        return ERR_FAILED;
    }
    else if(p_ip_head->ttl >= 64) {
        printf("ttl = %d, 超时\n", (int)p_ip_head->ttl);
        return ERR_FAILED;
    }
    else{
        return ERR_SUCCESS;
    }
}


int IP_Parse(char *buf, int *ihl, TRANS_PROTO_E *p_proto_type)
{
    char        src_ip[IP_STR_LEN + 1];
    char        dst_ip[IP_STR_LEN + 1];
    IP_HEADER_S ip_head;
    int         retval = ERR_SUCCESS;


    bzero(src_ip, sizeof(src_ip));
    bzero(dst_ip, sizeof(dst_ip));
    bzero(&ip_head, sizeof(IP_HEADER_S));

    ip_head = *(IP_HEADER_S *)buf;

    /* ip包合法性检查 */
    if ((retval = IP_Check(&ip_head)) != ERR_SUCCESS) {
        return retval;
    }

    *ihl = (int)ip_head.head_len;

    printf("*******************************************\n");
    printf("****************IP HEADER******************\n");
    printf("*******************************************\n");

    printf("包头长度:%d\n", (int)ip_head.head_len);
    printf("Differentiated Services Field:%d\n", (int)ip_head.tos);
    printf("ip包总长度:%d\n", (int)ip_head.total_len);
    printf("Identification:%d\n", (int)ip_head.id_info);
    printf("ttl = %d\n", (int)ip_head.ttl);
    
    if (ip_head.can_frag == 1) {
        printf("本ip包不能分片\n");
    }
    else if (ip_head.has_next_frag == 1) {
        printf("ip包还有下一片，本片的偏移为:%d\n", (int)ip_head.frag_offset);
    }

    cal_trans_proto((int)ip_head.proto_id, p_proto_type);

    printf("四层协议类型id为:%d\n", (int)ip_head.proto_id);
    int_converto_ip(ntohl(ip_head.src_ip), src_ip);
    int_converto_ip(ntohl(ip_head.dst_ip), dst_ip);

    printf("源ip地址为:%s\n", src_ip);
    printf("目的ip地址为:%s\n", dst_ip);
    printf("*******************************************\n");
    printf("*******************************************\n");
    printf("\n\n\n\n");

    return retval;
}
