/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:21:34 by yxu               #+#    #+#             */
/*   Updated: 2023/12/20 20:21:08 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <errno.h>
# include <libc.h>

typedef struct s_obj{
	int	x_from;
	int	y_from;
	int	x;
	int	y;
	int	collectible;
	int	life;
}	t_obj;

typedef struct s_image{
	void	*image;
	int		width;
	int		height;
}	t_image;

typedef struct s_texture{
	t_image	player_s1;
	t_image	player_s2;
	t_image	water;
	t_image	wall;
	t_image	escape;
	t_image	collect;
	t_image	enemy;
}	t_texture;

typedef struct s_data {
	void		*win;
	void		*mlx;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**map;
	int			rows;
	int			cols;
	int			move_nb;
	t_obj		player;
	t_obj		enemy;
	t_texture	texture;
}	t_data;

int		count_line(char *path);
char	**read_map(char *path, t_data *data);
int		print_map(char **map);
int		free_map(char **map);
int		check_map(char *path, t_data *data);
int		quit(int exitflag, char *msg, t_data *data);
int		key(int keycode, t_data *data);
int		screenctl(t_data *data);
void	init_game(char **map, t_data *data);

#endif
