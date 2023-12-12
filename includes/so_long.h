/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:21:34 by yxu               #+#    #+#             */
/*   Updated: 2023/12/12 22:31:18 by yxu              ###   ########.fr       */
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

# ifndef MAP_PATH
#  define MAP_PATH "./maps/map.ber"
# endif

typedef struct s_data {
	void	*win;
	void	*mlx;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		todo;
}	t_data;

int	create_trgb(int t, int r, int g, int b);

#endif
