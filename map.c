/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:04:34 by yxu               #+#    #+#             */
/*   Updated: 2023/12/19 16:50:38 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_line(char *path)
{
	int		fd;
	int		nb;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	nb = 0;
	line = get_next_line(fd);
	while (line)
	{
		nb++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb);
}

char	**read_map(char *path, t_data *data)
{
	int		fd;
	char	**map;
	int		i;

	data->rows = count_line(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (data->rows + 1));
	map[data->rows] = NULL;
	i = 0;
	while (i < data->rows)
		map[i++] = get_next_line(fd);
	close(fd);
	i = 0;
	while (i < data->rows - 1)
	{
		map[i][ft_strlen(map[i]) - 1] = '\0';
		i++;
	}
	data->cols = ft_strlen(map[0]);
	return (map);
}

int	print_map(char **map)
{
	int	x;

	x = 0;
	while (map[x])
	{
		ft_printf("%s\n", map[x]);
		x++;
	}
	ft_printf("\n");
	return (0);
}

int	free_map(char **map)
{
	int	x;

	x = 0;
	while (map[x])
	{
		free(map[x]);
		x++;
	}
	free(map);
	return (0);
}
