#include "libbuf.h"
#include "bgpd.h"

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
//
//int set2byteBE(uint8_t *buf, uint16_t data) {
//
//  buf[0] = (uint8_t)data;
//  buf[1] = (uint8_t)(data >> 8);
//
//  hexdump1(stdout, &buf, 2);
//  return 0;
//}
//
//int streamSet(struct stream *s, const uint8_t *buf, size_t bufSize) {
//  
//  if (s->size + bufSize > 4096) return -1;
//
//  memcpy(s->buf, buf, bufSize);
//  s->size += bufSize;
//  return 0;
//}

int streamSet2byteBE(struct stream *s, uint16_t data) {
  
  //uint8_t buf[1];
  //set2byteBE(buf, data);
  //return streamSet(s, buf, 1); 

  if (s->size > 4096) return -1;

  s->buf[s->size++] = (uint8_t)data;
  s->buf[s->size++] = (uint8_t)(data >> 8);
}

int streamSetipv4AddrBE(struct stream *s, struct in_addr addr) {
  
  memcpy(s->buf + s->size, &addr, sizeof(uint32_t)); // iden
	s->size += sizeof(uint32_t);
  return 1;
}