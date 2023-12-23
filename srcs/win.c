/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:28:14 by yxu               #+#    #+#             */
/*   Updated: 2023/12/23 17:13:47 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mkbackground(int frame, t_data *data)
{
	int			x;
	int			y;

	y = 0;
	while (y < 88 * data->rows)
	{
		x = -192 + frame * 64;
		while (x < 88 * data->cols)
		{
			mlx_put_image_to_window(data->mlx, data->win,
				data->texture.water.image, x, y);
			x += 256;
		}
		y += 64;
	}
	return (0);
}

int	mkstatic1(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
				mlx_put_image_to_window(data->mlx, data->win,
					data->texture.wall.image, y * 88, x * 88);
			if (data->map[x][y] == 'E')
				mlx_put_image_to_window(data->mlx, data->win,
					data->texture.escape.image, y * 88, 22 + x * 88);
			y++;
		}
		x++;
	}
	return (0);
}

int	mkstatic2(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == 'C')
				mlx_put_image_to_window(data->mlx, data->win,
					data->texture.collect.image, 12 + y * 88, 12 + x * 88);
			if (data->map[x][y] == 'V')
				mlx_put_image_to_window(data->mlx, data->win,
					data->texture.enemy.image, 22 + y * 88, 22 + x * 88);
			y++;
		}
		x++;
	}
	return (0);
}

int	mksprite(int frame, t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == 'P' && frame % 2 == 0)
				mlx_put_image_to_window(data->mlx, data->win,
					data->texture.player_s1.image, 12 + y * 88, 12 + x * 88);
			if (data->map[x][y] == 'P' && frame % 2 == 1)
				mlx_put_image_to_window(data->mlx, data->win,
					data->texture.player_s2.image, 12 + y * 88, 12 + x * 88);
			y++;
		}
		x++;
	}
	return (0);
}

int	screenctl(t_data *data)
{
	static int	frame = 0;
	int			frame_per_anime;
	char		*move_nb;

	is_player_die(data);
	frame_per_anime = 25;
	mkbackground(frame / frame_per_anime, data);
	mksprite(frame / frame_per_anime, data);
	frame = (frame + 1) % (4 * frame_per_anime);
	mkstatic1(data);
	mkstatic2(data);
	move_nb = ft_itoa(data->move_nb);
	if (move_nb == NULL)
		quit(1, "Malloc failed when running\n", data);
	mlx_string_put(data->mlx, data->win, 10, 10, 0x00FFFFFF, "movements:");
	mlx_string_put(data->mlx, data->win, 120, 10, 0x00FFFFFF, move_nb);
	free(move_nb);
	return (0);
}
