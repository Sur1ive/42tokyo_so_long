/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:52:07 by yxu               #+#    #+#             */
/*   Updated: 2023/12/13 18:23:38 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ext(char *path)
{
	char	*file_ext;

	file_ext = ".ber";
	if (ft_strlen(path) < 5
		|| ft_strncmp(&path[ft_strlen(path) - 4], file_ext, 4))
		return (-1);
	return (0);
}

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

// int	check_map_path(char **map)
// {


// }

int	check_map(char **map, t_data *data)
{
	int	obj_nb[3];

	obj_nb[0] = 0;
	obj_nb[1] = 0;
	obj_nb[2] = 0;
	if (check_map_obj(map, obj_nb))
		quit(10, data);
	if (check_map_rectangular(map))
		quit(11, data);
	if (check_map_wall(map, data->map_rows))
		quit(12, data);
	// if (check_map_path(map))
	// 	quit(13);
	return (0);
}
