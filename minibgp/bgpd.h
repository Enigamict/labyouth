#pragma once

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

#define BGP_MSG_TYPE_OPEN 1
#define BGP_MSG_TYPE_UPDATE 2
#define BGP_MSG_TYPE_NOTFICATION 3
#define BGP_MSG_TYPE_KEEPALIVE 4

#define BGP_MARKER 16
#define BGP_OPEN_OPT 48

#define BGP_HDR_LEN 19
#define BGP_HDR_MAX_LEN 4096
#define BGP_OPEN_HDR_LEN 10
#define BGP_KEEPALIVE_LEN 19

#define BGP_VERSION 0x04
#define BGP_HOLDTIME 0x00B4


struct config {
    uint16_t as_number;
    struct in_addr peer_address;
    struct in_addr bgp_identifier;
};


typedef struct bgp_hdr_t {
 uint8_t marker[BGP_MARKER];
 uint16_t len;
 uint8_t type;
}__attribute__((packed)) bgp_hdr;


typedef struct {
 bgp_hdr bgphdr;
 uint8_t version;
 uint16_t my_autonomous_system;
 uint16_t hold_time;
 struct in_addr bgp_identifier;
 uint8_t opt_parm_length;
}__attribute__((packed)) bgp_open;

struct bgp_keepalive {
 uint8_t marker[BGP_MARKER];
 uint16_t len;
 uint8_t type;
};

struct bgp_update {
 uint8_t marker[BGP_MARKER];
 uint16_t len;
 uint8_t type;
 uint16_t wl;
 uint16_t pl;
};

bgp_hdr parseBgpHdr(const uint8_t *buf);
struct stream bgp_stream_init();


struct bgp_rib *parseBgpUpdateHdr(struct bgp_rib *r, const uint8_t *buf);
int bgp_hdr_create_buf(struct stream *s, int hdrlen);
int bgp_keepalive_hdr_create_buf(struct stream *s);
int bgp_openhdr_create_buf(struct stream *s, struct config *conf);