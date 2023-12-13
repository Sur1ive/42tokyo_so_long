/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:12:31 by yxu               #+#    #+#             */
/*   Updated: 2023/12/13 18:25:45 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	quit(int exitcode, t_data *data)
{
	if (exitcode == 0)
		ft_printf("Congratulation! You made it!\n");
	else if (exitcode == 1)
		ft_printf("See you again!\n");
	else
	{
		ft_printf("Error code: %d\n", exitcode);
		print_map(data->map);
	}
	free_map(data->map);
	mlx_destroy_window(data->mlx, data->win);
	exit(exitcode);
}

int	test(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1920)
	{
		j = 0;
		while (j < 1080)
		{
			my_mlx_pixel_put(data, i, j, 0x00FFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

// int	printmouse(int button, int x, int y, t_data *data)
// {
// 	ft_printf("mouse click x: %d y: %d button: %d\n", x, y, button);
// 	return (0);
// }

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

int	printkey(int keycode, t_data *data)
{
	// ft_printf("push key: %d, keycode: %d\n", keycode, keycode);
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

__attribute__((destructor))
static void	destructor(void)
{
	system("leaks -q a.out");
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	**map;

	if (argc != 2)
		return (ft_printf("wrong arguments number\n"));
	if (check_ext(argv[1]))
		return (ft_printf("wrong file extension\n"));

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);

	map = read_map(argv[1], &data);
	load_map(map, &data);
	check_map(map, &data);
	print_map(data.map);

	// mlx_mouse_hook(data.win, printmouse, &data);
	mlx_key_hook(data.win, printkey, &data);
	// mlx_loop_hook(data.mlx, print_map, data.map);
	mlx_loop(data.mlx);
}
