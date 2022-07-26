#ifndef __GCODE_FORWARD_H
#define __GCODE_FORWARD_H
#include <string.h>
#include <stdlib.h>

char *GCodeForward(char *Gcode, void(*GCodeToSend)(char *));

#endif //__GCODE_FORWARD_H
