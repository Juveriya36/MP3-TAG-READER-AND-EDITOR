#include "types.h"

int convert_size(unsigned char *size)
{
    int frame_size;
    frame_size = (size[0] << 24) | (size[1] << 16) | (size[2] << 8) | size[3];
    return frame_size;
}