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
	map_cp[x][y] = '2';
	if (map_cp[x][y + 1] != 1 && map_cp[x][y + 1] != 2)
		flood_fill(data, map_cp, x, y + 1);
	if (map_cp[x][y - 1] != 1 && map_cp[x][y - 1] != 2)
		flood_fill(data, map_cp, x, y - 1);
	if (map_cp[x + 1][y] != 1
		&& map_cp[x + 1][y] != 2)
		flood_fill(data, map_cp, x + 1, y);
	if (map_cp[x - 1][y] != 1
		&& map_cp[x - 1][y] != 2)
		flood_fill(data, map_cp, x - 1, y);
}

char	**cpy_map(char **map)
{
	char	**map_cp;
	int		len;
	int		i;

	len = 0;
	while (map[len])
		len++;
	map_cp = malloc((len + 1) * sizeof(char *));
	i = 0;
	while (i < len)
	{
		map_cp[i] = ft_strdup(map[i]);
		i++;
	}
	return (map_cp);
}

void	get_player_pos(char **map, int	*x, int	*y)
{
	*x = 0;
	while (map[*x])
	{
		*y = 0;
		while(map[*x][*y])
		{
			if (map[*x][*y] == 'N' || map[*x][*y] == 'S'
				|| map[*x][*y] == 'E' || map[*x][*y] == 'W')
				return ;
			*y += 1;
		}
		*x += 1;
	}
}