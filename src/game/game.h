/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:00 by tforster          #+#    #+#             */
/*   Updated: 2024/07/22 20:35:44 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdbool.h>
# include "MLX42/MLX42.h"
# include "graph_lib/graph_types.h"

// MAP ATTRIBUTES //
# define MAP_X	8		//map width
# define MAP_Y	8		//map height
# define MAP_S	64	//map cube size

// PLAYER ATTRIBUTES //
# define PLAYER_SIZE	7

// PLAYER MOVEMENT //
typedef enum e_mov
{
	STEP = 5,
	STRF_STEP = 2,
	ANG = 2,
	RIGHT = 1,
	LEFT = -1,
	UP = 1,
	DOWN = -1,
}			t_mov;

// MAP TYPES //
typedef struct s_map
{
	int			*grid;
	t_ivec2		grid_size;
	int			cube_s;
	int			player_ang;
	t_ivec2		player_pos0;
	mlx_image_t	*img;
}				t_map;

// PLAYER TYPES //
typedef struct s_draw
{
	bool	xy_axis;
	bool	player;
	bool	rays;
}			t_draw;

typedef struct s_player
{
	t_vec2		p0;
	t_vec2		disp;
	t_ivec2		cam_view;
	int			dgr;
	mlx_image_t	*map;
	mlx_image_t	*view;
	int			*grid;
	t_vec2		geometry[10];
	t_draw		to_draw;
}				t_player;

// MAP FUNCs //
void	init_map(t_map *map, int width, int height);
void	draw_minimap(t_map *mini_map);

// PLAYER FUNCs //
void	init_player(t_player *player, t_map *map, int x0, int y0);
void	draw_player(void *param);

// PLAYER MOVEMENT //
void	movement(void *param);

#endif
