/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:12:31 by yxu               #+#    #+#             */
/*   Updated: 2024/01/16 13:43:10 by yxu              ###   ########.fr       */
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

void	quit(int exitflag, char *msg, t_data *data)
{
	if (exitflag == 0)
		ft_printf("%sProgram exit successfully\n", msg);
	else
		ft_printf("Error\n%s", msg);
	if (exitflag == 1)
		print_map(data->map);
	if (exitflag != 2)
	{
		free_map(data->map);
		mlx_destroy_window(data->mlx, data->win);
	}
	exit(0);
}

int	destory_win(t_data *data)
{
	quit(0, "Manual exit\n", data);
	return (0);
}

// __attribute__((destructor))
// static void	destructor(void)
// {
// 	system("leaks -q so_long");
// }

int	main(int argc, char **argv)
{
	t_data	data;
	char	**map;

	if (argc != 2)
		quit(2, "Invalid arguments number\n", NULL);
	if (check_ext(argv[1]))
		quit(2, "Invalid file extension, use .ber\n", NULL);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		quit(2, "MLX initialization failed\n", NULL);
	data.rows = count_line(argv[1]);
	map = read_map(argv[1], &data);
	init_game(map, &data);
	check_map(argv[1], &data);
	mlx_key_hook(data.win, key, &data);
	mlx_hook(data.win, 17, 0, destory_win, &data);
	mlx_loop_hook(data.mlx, screenctl, &data);
	mlx_loop(data.mlx);
}
