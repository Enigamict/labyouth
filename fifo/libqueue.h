#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct stream_que {
    int tail;
    int head;
    unsigned char bytedata[];
}stream_que;