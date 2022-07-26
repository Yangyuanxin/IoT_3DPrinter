#ifndef __GCODE_ANALYSIS_H
#define __GCODE_ANALYSIS_H
#include <string.h>
#include <stdlib.h>

typedef struct Move_Coordinate
{
	double X;
	double Y;
	double Z;
	double E;
} marlin_coordinate;

typedef struct Temperature
{
	double nozzle_cur_temp;
	double nozzle_target_temp;
	double hotbed_cur_temp;
	double hotbed_target_temp;
} marlin_temp;

void Get_Temperature(char *str, marlin_temp *temp_info);
void Get_Move_Coordinate(char *str, marlin_coordinate *axis_info);

#endif //__GCODE_ANALYSIS_H
