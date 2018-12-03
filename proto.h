/*************************************************************************
	> File Name: proto.h
	> Author: yuhao
	> Mail: me.yuhao@outlook.com
	> Created Time: 2018年12月02日 星期日 14时22分24秒
 ************************************************************************/

#ifndef _PROTO_H
#define _PROTO_H

typedef struct tag_IPHeader{
  #if __BYTE_ORDER == __LITTLE_ENDIAN
    uchar head_len:4;       //4bit是ip头长
    uchar version:4;        //前4bit版本号
  #elif __BYTE_ORDER == __BIG_ENDIAN
    uchar version:4;        //前4bit版本号
    uchar head_len:4;       //4bit是ip头长
  #else
    # error	"Please fix <bits/endian.h>"
  #endif
    uchar tos;              //differentiated services field
    ushort total_len;       //ip包的总长度
    ushort id_info;         //身份信息
  #if __BYTE_ORDER == __BIG_ENDIAN
    uchar  reverse:1;       //一个bit是保留字段
    uchar  can_frag:1;      //是否可以分片，的标志位1代表不可以分
    uchar  has_next_frag:1; //是否有下一个分片，1代表有
    ushort frag_offset:13;  //分片偏移
  #elif __BYTE_ORDER == __LITTLE_ENDIAN
    ushort frag_offset:13;  //分片偏移
    uchar  has_next_frag:1; //是否有下一个分片，1代表有
    uchar  can_frag:1;      //是否可以分片，的标志位1代表不可以分
    uchar  reverse:1;       //一个bit是保留字段
  #else
    # error	"Please fix <bits/endian.h>"
  #endif
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

#define MIN_IP_HEADER_LEN  sizeof(IP_HEADER_S)
#define UDP_HEADER_LEN sizeof(UDP_HEADER_S)
#define TCP_HEADER_LEN sizeof(TCP_HEADER_S)

typedef enum tagTransProtoType{
    PROTO_TCP,
    PROTO_UDP,
    PROTO_MAX
}TRANS_PROTO_E;
#endif
