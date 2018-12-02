/*************************************************************************
	> File Name: test.c
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年12月02日 星期日 14时15分52秒
 ************************************************************************/

#include<stdio.h>

struct tag_TCPHeader{
    unsigned short src_port;
    unsigned short dst_port;
    unsigned int   seq_no;
    unsigned int   ack_no;
    unsigned char  header_len:4; //4bit头部长度，比如5，则长度为5*32/8=20
    unsigned char  reverse:3;    //6bit保留字段
    unsigned char  nonce:1;      //1bit nonce
    unsigned char  cwr:1;        //1bit congestion window reduced
    unsigned char  ecn_echo:1;   //1bit ECN-Echo
    unsigned char  urgent:1;     //1bit Urgent
    unsigned char  ack:1;        //1bit Acknowledgment
    unsigned char  push:1;       //1bit Push
    unsigned char  reset:1;      //1bit Reset
    unsigned char  syn:1;        //1bit Syn
    unsigned char  fin:1;        //1bit Fin
    unsigned short win_size;
    unsigned short checksum;
    unsigned short urgent_pointer;
};

int main()
{

    printf("size = %lu\n", sizeof(struct tag_TCPHeader));
}
