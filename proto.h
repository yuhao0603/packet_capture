/*************************************************************************
	> File Name: proto.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年12月02日 星期日 14时22分24秒
 ************************************************************************/

#ifndef _PROTO_H
#define _PROTO_H
typedef struct tag_IPHeader{
    uchar v_len;        //前4bit版本号后4bit是ip头长
    uchar tos;          //differentiated services field
    ushort total_len;   //ip包的总长度
    ushort id_info;     //身份信息
    uchar  flag;        //三位标志位，第一个bit是保留字段
                                //第二bit是是否可以分片，的标志位1代表不可以分片
                                //第三个代表是否有下一个分片，1代表有
    ushort frag_offset; //分片偏移
    uchar  ttl;
    uchar  proto_id;
    ushort head_chechsum;
    uint   src_ip;
    uint   dst_ip;
}IP_HEADER_S;

typedef struct tag_UDPHeader{
    ushort src_port;
    ushort dst_port;
    ushort data_len;  //用户数据包长度+8字节固定udp包头
    ushort checksum;
}UDP_HEADER_S;

typedef struct tag_TCPHeader{
    ushort src_port;
    ushort dst_port;
    uint   seq_no;
    uint   ack_no;
    uchar  header_len:4; //4bit头部长度，比如5，则长度为5*32/8=20
    uchar  reverse:3;    //6bit保留字段
    uchar  nonce:1;      //1bit nonce
    uchar  cwr:1;        //1bit congestion window reduced
    uchar  ecn_echo:1;   //1bit ECN-Echo
    uchar  urgent:1;     //1bit Urgent
    uchar  ack:1;        //1bit Acknowledgment
    uchar  push:1;       //1bit Push
    uchar  reset:1;      //1bit Reset
    uchar  syn:1;        //1bit Syn
    uchar  fin:1;        //1bit Fin
    ushort win_size;
    ushort checksum;
    ushort urgent_pointer;
}TCP_HEADER_S;

#endif
