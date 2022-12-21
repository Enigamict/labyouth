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
#include <stdlib.h>

struct bgprib_link_node {
    struct bgprib_link_node *next; 
    struct bgprib_link_node *prev; 

    uint32_t prefix;
    uint8_t origin;
    uint32_t as_path;
    uint8_t as_path_length;
    uint32_t next_hop;
    uint32_t med;
    uint32_t local_pref;
};

struct bgp_rib {
    struct bgprib_link_node *head; 
    struct bgprib_link_node *tail;
};

struct bgp_peer {
    struct bgp_rib *prev;
    struct bgp_rib *next;
};

struct bgp_rib *bgpInitRib();
struct bgprib_link_node *new_node(uint32_t data);
struct bgprib_link_node *add_next_node(struct bgprib_link_node *node, uint32_t data);

struct bgprib_link_node *pop_node(struct bgprib_link_node *node);
struct bgprib_link_node *delete_node(struct bgprib_link_node  *node);
void ribPop(struct bgp_rib *r);
struct bgp_rib *ribPush(struct bgp_rib *r, uint32_t data);
void print_node(struct bgprib_link_node *n);