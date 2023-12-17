/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:01:27 by yxu               #+#    #+#             */
/*   Updated: 2023/12/17 18:44:52 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	remap(t_data *data)
{
	data->map[data->player.x_from][data->player.y_from] = '0';
	data->map[data->player.x][data->player.y] = 'P';
	return (0);
}

char	move_to(int keycode, t_data *data)
{
	char		to;

	to = 0;
	if (keycode == 13)
		to = data->map[data->player.x - 1][data->player.y];
	if (keycode == 1)
		to = data->map[data->player.x + 1][data->player.y];
	if (keycode == 0)
		to = data->map[data->player.x][data->player.y - 1];
	if (keycode == 2)
		to = data->map[data->player.x][data->player.y + 1];
	return (to);
}

int	move(int keycode, t_data *data)
{
	static int	move_nb = 0;
	char		to;

	data->player.x_from = data->player.x;
	data->player.y_from = data->player.y;
	to = move_to(keycode, data);
	if (to != '1' && to != 'E')
	{
		if (keycode == 13)
			data->player.x--;
		if (keycode == 1)
			data->player.x++;
		if (keycode == 0)
			data->player.y--;
		if (keycode == 2)
			data->player.y++;
		move_nb++;
	}
	if (to == 'C')
		data->player.collectible--;
	if (to == 'E' && data->player.collectible == 0)
		quit(0, data);
	return (move_nb);
}

int	key(int keycode, t_data *data)
{
	if (keycode == 53)
		quit(1, data);
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
	{
		ft_printf("number of movements: %d\n", move(keycode, data));
		remap(data);
		print_map(data->map);
	}
	return (0);
}
