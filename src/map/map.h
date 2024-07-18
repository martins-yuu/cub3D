/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:51:36 by tforster          #+#    #+#             */
/*   Updated: 2024/07/17 15:34:34 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "graph_lib/graph_types.h"
# include "MLX42/MLX42.h"

# define mapX 8		//map width
# define mapY 8		//map height
# define mapS 64	//map cube size

typedef struct	 s_map
{
	int			*grid;
	t_ivec2		grid_size;
	int			cube_s;
	int			player_ang;
	t_ivec2		player_pos0;
	mlx_image_t	*img;
}				t_map;

void	init_map(t_map *map, int width, int height);

#endif
