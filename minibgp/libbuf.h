#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include <netinet/in.h>

struct stream {
    unsigned char buf[4096];
    size_t size;
};


uint8_t get1byte(const uint8_t *buf);
uint16_t get2byteBE(const uint8_t *buf);
uint32_t get4byteBE(const uint8_t *buf);
int streamSet1byte(struct stream *s, uint8_t data);
int streamSet2byteBE(struct stream *s, uint16_t data);
int streamSetipv4AddrBE(struct stream *s, struct in_addr addr);