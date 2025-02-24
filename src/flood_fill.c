#include "../includes/cub3D.h"

bool	map_is_flooded(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

void	flood_fill(t_main *data, char **map_cp, int x, int y)
{
	if (x < -1 || y < -1)
		return ;
	map_cp[y][x] = '1';
	if (map_cp[y + 1][x] == '0')
		flood_fill(data, map_cp, x, y + 1);
	if (map_cp[y - 1][x] == '0')
		flood_fill(data, map_cp, x, y - 1);
	if (map_cp[y][x + 1] == '0')
		flood_fill(data, map_cp, x + 1, y);
	if (map_cp[y][x - 1] == '0')
		flood_fill(data, map_cp, x - 1, y);
}

char	**cpy_map(char **map)
{
	char	**map_cp;
	int		len;
	int		i;

	len = ft_tablen((void **)map);
	map_cp = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		map_cp[i] = ft_strdup(map[i]);
		i++;
	}
	map_cp[i] = NULL;
	return (map_cp);
}
