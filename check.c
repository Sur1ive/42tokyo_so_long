/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:52:07 by yxu               #+#    #+#             */
/*   Updated: 2023/12/17 18:41:10 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* obj_nb[exit_nb, start_nb, collectable_nb] */
int	check_map_obj(char **map, int *obj_nb)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'P')
				obj_nb[1]++;
			else if (map[x][y] == 'C')
				obj_nb[2]++;
			else if (map[x][y] == 'E')
				obj_nb[0]++;
			else if (map[x][y] != '0' && map[x][y] != '1')
				return (-1);
			y++;
		}
		x++;
	}
	if (obj_nb[0] != 1 || obj_nb[1] != 1 || obj_nb[2] < 1)
		return (-1);
	return (0);
}

int	check_map_rectangular(char **map)
{
	int		i;
	size_t	row_length;

	row_length = ft_strlen(map[0]);
	i = 1;
	while (map[i])
		if (ft_strlen(map[i++]) != row_length)
			return (-1);
	return (0);
}

int	check_map_wall(char **map, int rows)
{
	int	x;
	int	y;
	int	cols;

	cols = ft_strlen(map[0]);
	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (x == 0 || y == 0 || x == rows - 1 || y == cols - 1)
				if (map[x][y] != '1')
					return (-1);
			y++;
		}
		x++;
	}
	return (0);
}

int	check_map_valid(char **map, int x, int y)
{
	int	result;

	result = 1;
	map[x][y] = '1';
	if (map[x + 1][y] == 'E' || map[x - 1][y] == 'E'
		|| map[x][y + 1] == 'E' || map[x][y - 1] == 'E')
		return (0);
	if (map[x + 1][y] == '0' || map[x + 1][y] == 'C')
		result *= check_map_valid(map, x + 1, y);
	if (map[x - 1][y] == '0' || map[x - 1][y] == 'C')
		result *= check_map_valid(map, x - 1, y);
	if (map[x][y + 1] == '0' || map[x][y + 1] == 'C')
		result *= check_map_valid(map, x, y + 1);
	if (map[x][y - 1] == '0' || map[x][y - 1] == 'C')
		result *= check_map_valid(map, x, y - 1);
	return (result);
}

int	check_map(char *path, char **map, t_data *data)
{
	int		obj_nb[3];
	char	**map_cp;

	obj_nb[0] = 0;
	obj_nb[1] = 0;
	obj_nb[2] = 0;
	if (check_map_obj(map, obj_nb))
		quit(10, data);
	if (check_map_rectangular(map))
		quit(11, data);
	if (check_map_wall(map, data->rows))
		quit(12, data);
	map_cp = read_map(path, data);
	if (check_map_valid(map_cp, data->player.x, data->player.y))
	{
		free_map(map_cp);
		quit(13, data);
	}
	free_map(map_cp);
	return (0);
}
