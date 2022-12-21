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

#include "bgpd.h"
#include "rib.h"
#include "libbuf.h"

uint32_t ip_prefix_list[254]; // いずれ消す
int rib_count;

uint16_t convert_hex(int data) {
  return htons(data);
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

struct stream bgp_stream_init()
{

  struct stream s;

  s = (struct stream){0};
  return s;
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


struct bgp_rib *parseBgpUpdateHdr(struct bgp_rib *r, const uint8_t *buf)
{

  uint8_t ipv4_update_prefix_len;
  uint32_t ipv4_upd_prefix;
  ipv4_update_prefix_len = get1byte(buf + 41);
  printf("prefix len:%d\n", ipv4_update_prefix_len);

  if (ipv4_update_prefix_len > 24) {
    ipv4_upd_prefix = get4byteBE(buf + 42);
    printf("prefix:%x\n", ipv4_upd_prefix);
    return NULL;
  }

  uint8_t buf4[4] = {0};
  memcpy(buf4, buf + 42, 3);
  ipv4_upd_prefix = get4byteBE(buf4);

  printf("ip prefix:%x\n", ipv4_upd_prefix);
  struct in_addr inaddr = { htonl(ipv4_upd_prefix) };
	char *addrstr = inet_ntoa(inaddr);

  printf("%s\n", addrstr);
  printf("rib_address:%x\n", r);

  ribPush(r ,ipv4_upd_prefix);

  print_node(r->head);

  return r;
}

int parseBgpOpenHdr(const uint8_t *buf)
{
  bgp_open ret;
  uint32_t iden;

  static const int versionOffset = 19;
  static const int myasOffset = 20;
  static const int holdtimeOffset = 22;
  static const int idenOffset = 24;
  static const int optOffset = 28;

  ret.version = get1byte(buf + versionOffset);
  ret.my_autonomous_system = get2byteBE(buf + myasOffset);
  ret.hold_time = get2byteBE(buf + holdtimeOffset);
  iden = get4byteBE(buf + idenOffset); // idenは取れるけどどうIPにパースするかを考える FRRとかは専用のIPを取得するやつを作っている
  ret.opt_parm_length = get1byte(buf + optOffset);

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

int bgp_hdr_create_buf(struct stream *s, int hdrlen) {

  for (size_t i = 0; i < BGP_MARKER; i++) {
    streamSet1byte(s, (uint8_t)0xff);
  }

  uint16_t bgp_hdr_len = convert_hex(hdrlen);

  streamSet2byteBE(s, bgp_hdr_len); 
  streamSet1byte(s, BGP_MSG_TYPE_OPEN);
  return 0;

}


int bgp_keepalive_hdr_create_buf(struct stream *s) {

  for (size_t i = 0; i < BGP_MARKER; i++) {
    streamSet1byte(s, (uint8_t)0xff);
  }

  uint16_t bgp_hdr_len = convert_hex(19);

  streamSet2byteBE(s, bgp_hdr_len); 
  streamSet1byte(s, BGP_MSG_TYPE_KEEPALIVE);

  return 0; 
}

int bgp_openhdr_create_buf(struct stream *s, struct config *conf) {

  bgp_hdr_create_buf(s, 29);

  streamSet1byte(s, 0x04); // version

  uint16_t my_as = convert_hex(conf->as_number);

  streamSet2byteBE(s, my_as); // as
  streamSet2byteBE(s, htons(BGP_HOLDTIME)); // hold_time
  streamSetipv4AddrBE(s, conf->bgp_identifier);
  streamSet1byte(s, 0x00); // version

  return 0; 
}


int main(int argc, char** argv)
{
    struct sockaddr_in server;
    struct stream s;
    struct config config;
    int sock;
    uint8_t buf[4096];

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

    size_t size = send(sock, &s.buf, s.size, 0);

    if (size < 1) {
      printf("send error! \n");
      return 1;
    }

    printf("open send to... \n");
    printf("send size:%ld\n", size);

    bgp_hdr recv_bgp;

    struct bgp_rib *test;
    test = bgpInitRib();

    while (1)
    {
      ssize_t bgp_pkt_size = recv(sock, buf, sizeof(buf), 0);

      printf("pktsize:%ld\n", bgp_pkt_size);

      if (bgp_pkt_size > BGP_HDR_MAX_LEN) {
        fprintf(stderr, "over size error! \n");
        break;
      }

      recv_bgp = parseBgpHdr(buf);

      switch (recv_bgp.type)
      {
      case BGP_MSG_TYPE_OPEN:
        parseBgpOpenHdr(buf);
        break;
      case BGP_MSG_TYPE_UPDATE:
        parseBgpUpdateHdr(test, buf);
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
