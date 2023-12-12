/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheak_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:04:34 by yxu               #+#    #+#             */
/*   Updated: 2023/12/12 22:30:25 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	count_line(void)
// {
// 	int		fd;
// 	int		nb;
// 	char	*line;

// 	fd = open(MAP_PATH, O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	nb = 0;
// 	line = read_next_line(fd);
// 	while (line)
// 	{
// 		nb++;
// 		free(line);
// 		line = read_next_line(fd);
// 	}
// 	close(fd);
// 	return (nb);
// }

// char	**read_map(int fd, int rows)
// {
// 	char	**map;
// 	int		i;

// 	map = (char **)malloc(sizeof(char *) * (rows + 1));
// 	map[rows] = NULL;
// 	i = 0;
// 	while (i < rows)
// 		map[i++] = read_next_line(fd);
// 	return (map);
// }

// int	check_map(char **map)
// {



// }
