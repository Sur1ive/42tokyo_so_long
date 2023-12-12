/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:12:31 by yxu               #+#    #+#             */
/*   Updated: 2023/12/12 23:08:52 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	test(t_data *img)
{
	int	k = img->todo % 255;
	int i = 0;
	int j;

	while (i < 1920)
	{
		j = 0;
		while (j < 1080)
		{
			my_mlx_pixel_put(img, i, j, create_trgb(0, k, k, k));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}

int	plus(int button, int x, int y, t_data *img)
{
	ft_printf("mouse click x: %d y: %d button: %d\n", x, y, button);
	ft_printf("img->todo: %d\n", img->todo);
	img->todo += 10;
	return (0);
}

int	main(void)
{
	t_data	img;

	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(img.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	img.todo = 200;
	mlx_mouse_hook(img.win, plus, &img);
	mlx_loop_hook(img.mlx, test, &img);
	mlx_loop(img.mlx);

}
