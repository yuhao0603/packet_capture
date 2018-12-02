/*************************************************************************
	> File Name: proto.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年12月02日 星期日 14时22分24秒
 ************************************************************************/

#ifndef _PROTO_H
#define _PROTO_H
typedef struct tag_IPHeader{
    unsigned char v_len;        //前4bit版本号后4bit是ip头长
    unsigned char tos;          //differentiated services field
    unsigned short total_len;   //ip包的总长度
    unsigned short id_info;     //身份信息
    unsigned char  flag;        //三位标志位，第一个bit是保留字段
                                //第二bit是是否可以分片，的标志位1代表不可以分片
                                //第三个代表是否有下一个分片，1代表有
    unsigned short frag_offset; //分片偏移
    unsigned char  ttl;
    unsigned char  proto_id;
    unsigned short head_chechsum;
    unsigned int   src_ip;
    unsigned int   dst_ip;
}IP_HEADER_S;

typedef struct tag_UDPHeader{
    unsigned short src_port;
    unsigned short dst_port;
    unsigned short data_len;  //用户数据包长度+8字节固定udp包头
    unsigned short checksum;
}UDP_HEADER_S;

typedef struct tag_TCPHeader{
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
}TCP_HEADER_S;

#endif
