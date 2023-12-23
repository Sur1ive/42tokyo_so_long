/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:49:56 by yxu               #+#    #+#             */
/*   Updated: 2023/12/23 16:03:41 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map(char **map, t_data *data, int x, int y)
{
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'P')
			{
				data->player.x = x;
				data->player.y = y;
			}
			if (map[x][y] == 'C')
				data->player.collectible++;
			if (map[x][y] == 'V')
			{
				data->enemy.x = x;
				data->enemy.y = y;
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	load_texture(t_data *data)
{
	data->texture.water.image = mlx_xpm_file_to_image(data->mlx,
			"textures/water.xpm",
			&data->texture.water.width, &data->texture.water.height);
	data->texture.wall.image = mlx_xpm_file_to_image(data->mlx,
			"textures/grass.xpm",
			&data->texture.wall.width, &data->texture.wall.height);
	data->texture.escape.image = mlx_xpm_file_to_image(data->mlx,
			"textures/item.xpm",
			&data->texture.wall.width, &data->texture.wall.height);
	data->texture.player_s1.image = mlx_xpm_file_to_image(data->mlx,
			"textures/player_s1.xpm",
			&data->texture.player_s1.width, &data->texture.player_s1.height);
	data->texture.player_s2.image = mlx_xpm_file_to_image(data->mlx,
			"textures/player_s2.xpm",
			&data->texture.player_s2.width, &data->texture.player_s2.height);
	data->texture.collect.image = mlx_xpm_file_to_image(data->mlx,
			"textures/egg.xpm",
			&data->texture.collect.width, &data->texture.collect.height);
	data->texture.enemy.image = mlx_xpm_file_to_image(data->mlx,
			"textures/chicken.xpm",
			&data->texture.enemy.width, &data->texture.enemy.height);
	return (0);
}

void	init_game(char **map, t_data *data)
{
	data->cols = ft_strlen(map[0]);
	data->map = map;
	data->move_nb = 0;
	data->player.life = 1;
	data->player.collectible = 0;
	data->enemy.life = 1;
	data->enemy.x = -1;
	load_map(map, data, 0, 0);
	if (data->enemy.x == -1)
		data->enemy.life = 0;
	load_texture(data);
	data->win = mlx_new_window(data->mlx, 88 * data->cols, 88 * data->rows,
			"Eggstealer");
	data->img = mlx_new_image(data->mlx, 88 * data->cols, 88 * data->rows);
}
