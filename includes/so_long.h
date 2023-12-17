/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:21:34 by yxu               #+#    #+#             */
/*   Updated: 2023/12/17 18:43:14 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
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
}	t_obj;

typedef struct s_image{
	void	*image;
	int		width;
	int		height;
}	t_image;

typedef struct s_texture{
	t_image	player_w;
	t_image	player_a;
	t_image	player_s;
	t_image	player_d;
	t_image	water;
	t_image	wall;
	t_image	escape;
	t_image	collect;
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
	t_obj		player;
	t_texture	texture;
}	t_data;

int		create_trgb(int t, int r, int g, int b);
char	**read_map(char *path, t_data *data);
int		load_map(char **map, t_data *data);
int		print_map(char **map);
int		free_map(char **map);
int		check_map(char *path, char **map, t_data *data);
int		quit(int exitcode, t_data *data);
int		key(int keycode, t_data *data);
int		mkwall(t_data *data);

#endif
