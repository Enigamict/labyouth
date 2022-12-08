#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <net/if.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "bgphdr.h"

#define BGP_HDR_LEN 19
#define BGP_HDR_MAX_LEN 4096
#define BGP_OPEN_HDR_LEN 10
#define BGP_KEEPALIVE_LEN 19

#define BGP_VERSION 0x04
#define BGP_HOLDTIME 0x00B4

static const int versionOffset = 19;

uint16_t convert_hex(int data) {
  char s[16];
  snprintf(s, 16, "%x", data); // 19
  long v = strtol(s, NULL, 16);
  return htons(v);
}


static void hexdump1(FILE* fp, const void *buffer, size_t bufferlen)
{
  const uint8_t *data = (const uint8_t*)(buffer); size_t row = 0;
  while (bufferlen > 0) {
    fprintf(fp, "%04zx:   ", row);
    size_t n;
    if (bufferlen < 16) n = bufferlen;
    else                n = 16;
//
    for (size_t i = 0; i < n; i++) { if (i == 8) fprintf(fp, " "); fprintf(fp, " %02x", data[i]); }
    for (size_t i = n; i < 16; i++) { fprintf(fp, "   "); } fprintf(fp, "   ");
    for (size_t i = 0; i < n; i++) {
      if (i == 8) fprintf(fp, "  ");
      uint8_t c = data[i];
      if (!(0x20 <= c && c <= 0x7e)) c = '.';
      fprintf(fp, "%c", c);
    }
    fprintf(fp, "\n"); bufferlen -= n; data += n; row  += n;
  }
}

bgp_hdr bgp_hdr_init()
{

  bgp_hdr hdr;

  hdr = (bgp_hdr){0};
  return hdr;
}

bgp_hdr bgp_hdr_create(int type, int hdrlen) {

  bgp_hdr bgp;
  bgp = bgp_hdr_init();
  uint8_t marker[BGP_MARKER] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                0xFF, 0xFF, 0xFF, 0xFF};

  memcpy(bgp.marker, marker, BGP_MARKER);
  bgp.len = convert_hex(hdrlen); 
  bgp.type = type;
  return bgp;
}

 bgp_open bgp_openhdr_init() 
 {

  bgp_open open;

  open = (bgp_open){ 0 };
  return open;
}


bgp_open bgp_openhdr_create(struct config conf) {

  bgp_open open;
  open = bgp_openhdr_init();

  open.bgphdr = bgp_hdr_create(BGP_MSG_TYPE_OPEN, 29); // bgplen 19 + bgpopen_hdr_len 10
  open.version = 0x04;
  open.my_autonomous_system = convert_hex(conf.as_number);
  open.hold_time = htons(BGP_HOLDTIME);
  open.bgp_identifier = conf.bgp_identifier;
  open.opt_parm_length = 0;
  return open;
}


uint8_t get1byte(const uint8_t *buf)
{
  return buf[0];
}
uint16_t get2byteBE(const uint8_t *buf)
{
  return (uint16_t)(buf[0] << 8) | buf[1];
}

uint32_t get4byteBE(const uint8_t *buf)
{
  return (uint32_t)(get2byteBE(buf) << 16) + get2byteBE(buf + 2);
}

bgp_hdr parseBgpHdr(const uint8_t *buf)
{

  bgp_hdr ret;
  ret.len = get2byteBE(buf + 16);

  if (ret.len > BGP_HDR_MAX_LEN) {
    fprintf(stderr, "over size error! \n");
  }

  printf("size:%d\n", ret.len);
  ret.type = get1byte(buf + 18);
  return ret;
}

int parseBgpOpenHdr(const uint8_t *buf)
{
  bgp_open ret;
  uint32_t iden;

  ret.version = get1byte(buf + versionOffset);
  ret.my_autonomous_system = get2byteBE(buf + 20);
  ret.hold_time = get2byteBE(buf + 22);
  iden = get4byteBE(buf + 24); // idenは取れるけどどうIPにパースするかを考える FRRとかは専用のIPを取得するやつを作っている
  ret.opt_parm_length = get1byte(buf + 28);

  printf("version:%x\n", ret.version);
  printf("MY AS:%d\n", ret.my_autonomous_system);
  printf("HOLD TIME:%x\n", ret.hold_time);
  printf("Iden:%x\n", iden);
  printf("OPT LEN:%x\n", ret.opt_parm_length);

  if (ret.opt_parm_length > 1) {
    // parse_code
  }

  return 0;
}


int set1byte(struct stream *s, uint8_t data) {
  
  s->buf[s->size++] = data;
  return 1;
}

int set2byteBE(struct stream *s, uint16_t data) {
  

  s->buf[s->size++] = (uint8_t)data;
  s->buf[s->size++] = (uint8_t)(data >> 8);

  return 1;
}

int bgp_hdr_create_buf(struct stream *s, int hdrlen) {

  for (size_t i = 0; i < BGP_MARKER; i++) {
    set1byte(s, (uint8_t)0xff);
  }

  uint16_t bgp_hdr_len = convert_hex(hdrlen);

  set2byteBE(s, bgp_hdr_len); 
  set1byte(s, BGP_MSG_TYPE_OPEN);
  return 1;

}


int bgp_keepalive_hdr_create_buf(struct stream *s) {

  for (size_t i = 0; i < BGP_MARKER; i++) {
    set1byte(s, (uint8_t)0xff);
  }

  uint16_t bgp_hdr_len = convert_hex(19);

  set2byteBE(s, bgp_hdr_len); 
  set1byte(s, BGP_MSG_TYPE_KEEPALIVE);

  return 1; 
}

int bgp_openhdr_create_buf(struct stream *s, struct config *conf) {

  bgp_hdr_create_buf(s, 29);

  set1byte(s, 0x04); // version

  uint16_t my_as = convert_hex(conf->as_number);

  set2byteBE(s, my_as); // as
  set2byteBE(s, htons(BGP_HOLDTIME)); // hold_time
  memcpy(s->buf + s->size, &conf->bgp_identifier, sizeof(uint32_t)); // iden
	s->size += sizeof(uint32_t);

  set1byte(s, 0x00); // version

  return 1; 
}

struct stream bgp_stream_init()
{

  struct stream s;

  s = (struct stream){0};
  return s;
}

int main(int argc, char** argv)
{
    struct sockaddr_in server;
    //bgp_open open;
    struct stream s;
    struct config config;
    int sock;
    char buf[4096];

    config.as_number = 65001;
    inet_pton(AF_INET, "10.255.3.1", &config.bgp_identifier);

    s = bgp_stream_init();

    bgp_openhdr_create_buf(&s, &config);

    hexdump1(stdout, &s.buf, 29);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(179);
    server.sin_addr.s_addr = inet_addr(argv[argc - 1]);

    bind(sock, (struct sockaddr *)&server, sizeof(server));
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    //open = bgp_openhdr_create(config);

    size_t size = send(sock, &s.buf, s.size, 0);
    printf("open send to... \n");
    printf("%ld", size);

    bgp_hdr recv_bgp;

    while (1)
    {
      ssize_t bgp_pkt_size = recv(sock, buf, sizeof(buf), 0);

      printf("pktsize:%ld\n", bgp_pkt_size);

      if (bgp_pkt_size > BGP_HDR_MAX_LEN) {
        fprintf(stderr, "over size error! \n");
        break;
      }

      recv_bgp = parseBgpHdr((uint8_t *)buf);

      switch (recv_bgp.type)
      {
      case BGP_MSG_TYPE_OPEN:
        parseBgpOpenHdr((uint8_t *)buf);
        break;
      case BGP_MSG_TYPE_KEEPALIVE:
        struct stream kepps;
        kepps = bgp_stream_init();
        bgp_keepalive_hdr_create_buf(&kepps);
        send(sock, &kepps, BGP_HDR_LEN, 0);
        break;
      default:
        continue;
      }
    }
    
    close(sock);
    return 0;
}
