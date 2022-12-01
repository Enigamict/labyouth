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
#define BGP_OPEN_HDR_LEN 10
#define BGP_KEEPALIVE_LEN 19

#define BGP_VERSION 0x04
#define BGP_HOLDTIME 0x00B4

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

int bgp_keepalivehdr_create(struct bgp_keepalive *keep) {

  // BGP_MARKER
  uint8_t marker[BGP_MARKER] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                0xFF, 0xFF, 0xFF, 0xFF};

  memcpy(keep->marker, marker, BGP_MARKER);
  keep->len = convert_hex(19); // keepalive len
  keep->type = BGP_MSG_TYPE_KEEPALIVE;
  return 0;
}

 bgp_open bgp_openhdr_init() {

  bgp_open open;

  open = (bgp_open){ 0 };
  return open;
}


 bgp_open bgp_openhdr_create(struct config conf) {

  bgp_open open;
//  uint8_t marker[BGP_MARKER] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//                                0xFF, 0xFF, 0xFF, 0xFF};
  open = bgp_openhdr_init();
  open.bgphdr = bgp_hdr_create(BGP_MSG_TYPE_OPEN, 30); // bgplen 19 + bgpopen_hdr_len 10
//
//  memcpy(open.marker, marker, BGP_MARKER);
//  open.len = convert_hex(30); // keepalive len
//  open.type = BGP_MSG_TYPE_OPEN;
  open.version = 0x04;
  open.my_autonomous_system = convert_hex(conf.as_number);
  open.hold_time = htons(BGP_HOLDTIME);
  open.bgp_identifier = conf.bgp_identifier;
  open.opt_parm_length = 0;
  return open;
}


int main(int argc, char** argv)
{
    struct sockaddr_in server;
    bgp_open open;
    struct bgp_keepalive kep;
    struct config config;
    int sock;
    char buf[1000];

    config.as_number = 65001;
    inet_pton(AF_INET, "10.255.3.1", &config.bgp_identifier);

    memset(&kep, 0x0, sizeof(kep));

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(179);
    server.sin_addr.s_addr = inet_addr(argv[argc - 1]);

    bind(sock, (struct sockaddr *)&server, sizeof(server));
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    open = bgp_openhdr_create(config);

    size_t size = send(sock, &open, sizeof(open) + 1, 0);
    printf("open send to... \n");
    printf("%ld", size);

    while (1)
    {
      recv(sock, buf, sizeof(buf), 0);
      bgp_hdr* recv_bgp =  (bgp_hdr *)buf;
      switch (recv_bgp->type)
      {
      case BGP_MSG_TYPE_KEEPALIVE:
        /* code */
        bgp_hdr bgp;
        bgp = bgp_hdr_init();
        bgp = bgp_hdr_create(BGP_MSG_TYPE_KEEPALIVE, 19);
        printf("keep alive send to... \n");
        send(sock, &bgp, sizeof(bgp) + 1, 0);
        break; 
      default:
        continue;
      }
    }
    
    close(sock);
    return 0;
}
