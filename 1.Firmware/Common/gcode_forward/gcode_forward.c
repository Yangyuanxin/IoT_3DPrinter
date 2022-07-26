#include "gcode_forward.h"

char *GCodeForward(char *Gcode, void(*GCodeToSend)(char *))
{
	if(NULL == Gcode || NULL == GCodeToSend)
		return NULL;
	GCodeToSend(Gcode);
	return "OK";
}
