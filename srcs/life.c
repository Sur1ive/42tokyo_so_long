/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:15:50 by yxu               #+#    #+#             */
/*   Updated: 2023/12/23 17:13:11 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	enemy_atk(t_data *data)
{
	if (data->enemy.life == 1 && ((data->enemy.y == data->player.y
				&& data->enemy.x == data->player.x)
			|| (data->enemy.y == data->player.y_from
				&& data->enemy.x == data->player.x_from
				&& data->enemy.y_from == data->player.y
				&& data->enemy.x_from == data->player.x)))
	{
		data->map[data->player.x][data->player.y] = '0';
		data->map[data->enemy.x][data->enemy.y] = 'V';
		data->player.life = 0;
	}
}

void	player_atk(t_data *data)
{
	if (data->enemy.life == 1)
	{
		data->enemy.life = 0;
		ft_printf("Ultimate skill! Enemy has been killed.\n");
		data->texture.enemy.image = mlx_xpm_file_to_image(data->mlx,
				"textures/chicken_died.xpm",
				&data->texture.enemy.width, &data->texture.enemy.height);
	}
	else
		ft_printf("Ultimate skill! But nothing happened.\n");
}

void	is_player_die(t_data *data)
{
	static int	death = 0;

	if (death == 1)
		quit(0, "You died!\n", data);
	if (data->player.life == 0)
		death = 1;
}
