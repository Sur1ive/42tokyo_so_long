/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:12:31 by yxu               #+#    #+#             */
/*   Updated: 2023/12/17 18:58:31 by yxu              ###   ########.fr       */
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
	frame = (frame + 1) % 4;
	return (0);
}

int	mkwall(t_data *data)
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
			if (data->map[x][y] == 'P')
				mlx_put_image_to_window(data->mlx, data->win,
					data->texture.player_s.image, 12 + y * 88, 12 + x * 88);
			if (data->map[x][y] == 'C')
				mlx_put_image_to_window(data->mlx, data->win,
					data->texture.collect.image, 12 + y * 88, 12 + x * 88);
			y++;
		}
		x++;
	}
	return (0);
}

int	screenctl(t_data *data)
{
	static int	frame = 0;

	mkbackground(frame, data);
	mkwall(data);
	frame = (frame + 1) % 4;
	// usleep(400000);
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
	data->texture.player_s.image = mlx_xpm_file_to_image(data->mlx,
			"textures/player_s.xpm",
			&data->texture.player_s.width, &data->texture.player_s.height);
	data->texture.collect.image = mlx_xpm_file_to_image(data->mlx,
			"textures/egg.xpm",
			&data->texture.collect.width, &data->texture.collect.height);
	return (0);
}

int	destory_win(t_data *data)
{
	quit(1, data);
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
	map = read_map(argv[1], &data);
	load_map(map, &data);
	check_map(argv[1], map, &data);
	print_map(data.map);
	load_texture(&data);

	data.win = mlx_new_window(data.mlx, 88 * data.cols, 88 * data.rows, "game");
	data.img = mlx_new_image(data.mlx, 88 * data.cols, 88 * data.rows);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);

	mlx_key_hook(data.win, key, &data);
	mlx_hook(data.win, 17, 0, destory_win, &data);
	mlx_loop_hook(data.mlx, screenctl, &data);
	mlx_loop(data.mlx);
}
