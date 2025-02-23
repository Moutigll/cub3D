#include "../includes/cub3D.h"

void	flood_fill(t_main data, char *map_cp, int coords)
{
	map_cp[coords] = 2;
	if (map_cp[coords + 1] != 1 && map_cp[coords + 1] != 2)
		flood_fill(data, map_cp, coords + 1);
	if (map_cp[coords - 1] != 1 && map_cp[coords - 1] != 2)
		flood_fill(data, map_cp, coords - 1);
	if (map_cp[coords + data.max_line_len] != 1
		&& map_cp[coords + data.max_line_len] != 2)
		flood_fill(data, map_cp, coords + data.max_line_len);
	if (map_cp[coords - data.max_line_len] != 1
		&& map_cp[coords - data.max_line_len] != 2)
		flood_fill(data, map_cp, coords - data.max_line_len);
}