/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:00 by tforster          #+#    #+#             */
/*   Updated: 2024/07/19 17:40:05 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "MLX42/MLX42.h"
# include "graph_lib/graph_types.h"

// MAP ATTRIBUTES //
# define mapX 8		//map width
# define mapY 8		//map height
# define mapS 64	//map cube size

// PLAYER ATTRIBUTES //
# define STEP	5
# define ANG	2
# define PLAYER_SIZE	7


// MAP TYPES //
typedef struct	 s_map
{
	int			*grid;
	t_ivec2		grid_size;
	int			cube_s;
	int			player_ang;
	t_ivec2		player_pos0;
	mlx_image_t	*img;
}				t_map;

// PLAYER TYPES //
typedef struct s_player
{
	t_vec2		p0;
	t_vec2		del;
	float		theta_dg;
	int			size;
	mlx_image_t	*map;
	mlx_image_t	*view;
	int			*grid;
	t_vec2		geometry[10];
}				t_player;

// MAP FUNCs //
void	init_map(t_map *map, int width, int height);

// PLAYER FUNCs //
void	init_player(t_map *map, t_player *player, int x0, int y0);
void	draw_player(void *param);

#endif
