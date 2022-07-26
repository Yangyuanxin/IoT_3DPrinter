#include "gcode_analysis.h"

void marlin_data_buffer_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

/*
 example:
 T:27.00 /0.00 B:27.80 /0.00 @:0 B@:0       The first byte is a space
 ok T:27.03 /0.00 B:27.78 /0.00 @:0 B@:0   The first two bytes consist of ok
 */
void Get_Temperature(char *str, marlin_temp *temp_info)
{
	char buf[10] = { 0 };
	int cut_out_len = 0;
	char *data_field = NULL;
	char *space_field = NULL;
	if (str[0] == ' ' && str[1] == 'T')
		str += 1;
	if (str[0] == 'o' && str[1] == 'k')
		str += 3;
	data_field = strstr(str, ":");
	space_field = strstr(str, " ");
	cut_out_len = space_field - data_field - 1;
	memcpy(buf, data_field + 1, cut_out_len);
	temp_info->nozzle_cur_temp = atof(buf);
	data_field = strstr(space_field, "/");
	space_field = strstr(space_field + 1, " ");
	cut_out_len = space_field - data_field - 1;
	marlin_data_buffer_bzero(buf, 10);
	memcpy(buf, data_field + 1, cut_out_len);
	temp_info->nozzle_target_temp = atof(buf);
	data_field = strstr(space_field, ":");
	space_field = strstr(space_field + 1, " ");
	cut_out_len = space_field - data_field - 1;
	marlin_data_buffer_bzero(buf, 10);
	memcpy(buf, data_field + 1, cut_out_len);
	temp_info->hotbed_cur_temp = atof(buf);
	data_field = strstr(space_field, "/");
	space_field = strstr(space_field + 1, " ");
	cut_out_len = space_field - data_field - 1;
	marlin_data_buffer_bzero(buf, 10);
	memcpy(buf, data_field + 1, cut_out_len);
	temp_info->hotbed_target_temp = atof(buf);
}

/*X:66.50 Y:105.30 Z:1.10 E:0.00 Count X:5320 Y:8424 Z:920*/
void Get_Move_Coordinate(char *str, marlin_coordinate *axis_info)
{
	char buf[10] = { 0 };
	int cut_out_len = 0;
	char *data_field = NULL;
	char *space_field = NULL;
	data_field = strstr(str, ":");
	space_field = strstr(str, " ");
	cut_out_len = space_field - data_field - 1;
	memcpy(buf, data_field + 1, cut_out_len);
	axis_info->X = atof(buf);
	data_field = strstr(space_field, ":");
	space_field = strstr(space_field + 1, " ");
	cut_out_len = space_field - data_field - 1;
	marlin_data_buffer_bzero(buf, 10);
	memcpy(buf, data_field + 1, cut_out_len);
	axis_info->Y = atof(buf);
	data_field = strstr(space_field, ":");
	space_field = strstr(space_field + 1, " ");
	cut_out_len = space_field - data_field - 1;
	marlin_data_buffer_bzero(buf, 10);
	memcpy(buf, data_field + 1, cut_out_len);
	axis_info->Z = atof(buf);
	data_field = strstr(space_field, ":");
	space_field = strstr(space_field + 1, " ");
	cut_out_len = space_field - data_field - 1;
	marlin_data_buffer_bzero(buf, 10);
	memcpy(buf, data_field + 1, cut_out_len);
	axis_info->E = atof(buf);
}
