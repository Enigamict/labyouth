#include "libbuf.h"

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

int streamSet1byte(struct stream *s, uint8_t data) {
  
  s->buf[s->size++] = data;
  return 0;
}

int streamSet2byteBE(struct stream *s, uint16_t data) {
  

  s->buf[s->size++] = (uint8_t)data;
  s->buf[s->size++] = (uint8_t)(data >> 8);

  return 0;
}

int streamSetipv4AddrBE(struct stream *s, struct in_addr addr) {
  

  memcpy(s->buf + s->size, &addr, sizeof(uint32_t)); // iden
	s->size += sizeof(uint32_t);
  return 1;
}