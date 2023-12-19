/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:01:27 by yxu               #+#    #+#             */
/*   Updated: 2023/12/19 16:40:50 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	remap(t_data *data)
{
	data->map[data->player.x_from][data->player.y_from] = '0';
	data->map[data->enemy.x_from][data->enemy.y_from] = '0';
	data->map[data->player.x][data->player.y] = 'P';
	data->map[data->enemy.x][data->enemy.y] = 'V';
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
		data->move_nb++;
	}
	if (to == 'C')
		data->player.collectible--;
	if (to == 'E' && data->player.collectible == 0)
		quit(0, data);
	return (data->move_nb);
}

int	enemy_move(t_data *data)
{
	static int	direction = 1;

	data->enemy.x_from = data->enemy.x;
	data->enemy.y_from = data->enemy.y;
	if (data->map[data->enemy.x + direction][data->enemy.y] != '0'
		&& data->map[data->enemy.x + direction][data->enemy.y] != 'P')
		direction *= -1;
	if (data->map[data->enemy.x + direction][data->enemy.y] == '0'
		|| data->map[data->enemy.x + direction][data->enemy.y] == 'P')
		data->enemy.x += direction;
	return (0);
}

int	key(int keycode, t_data *data)
{
	if (keycode == 53)
		quit(1, data);
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
	{
		ft_printf("number of movements: %d\n", move(keycode, data));
		enemy_move(data);
		remap(data);
		if ((data->enemy.y == data->player.y && data->enemy.x == data->player.x)
			|| (data->enemy.y == data->player.y_from
				&& data->enemy.x == data->player.x_from
				&& data->enemy.y_from == data->player.y
				&& data->enemy.x_from == data->player.x))
		{
			data->map[data->player.x][data->player.y] = '0';
			data->map[data->enemy.x][data->enemy.y] = 'V';
			data->player.life = 0;
		}
		print_map(data->map);
	}
	return (0);
}