/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:00 by tforster          #+#    #+#             */
/*   Updated: 2024/08/04 16:47:52 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdbool.h>
# include "MLX42/MLX42.h"
# include "graph_lib/graph_types.h"

// MAP ATTRIBUTES //

// # define MINI_MAP_S	512
# define MINI_MAP_S	480

// PLAYER ATTRIBUTES //
# define PLAYER_SIZE	7

// PLAYER MOVEMENT //
# define STEP 0.05
# define STRF_STEP 0.02
typedef enum e_mov
{
	ANG = 2,
	RIGHT = 1,
	LEFT = -1,
	UP = 1,
	DOWN = -1,
}			t_mov;

// MAP TYPES //
typedef struct s_map_ctx
{
	int			*grid;
	t_ivec2		grid_dim;
	t_ivec2		grid_p0;
	int			orientation;
	int			min_dim;
}				t_map_ctx;

typedef struct s_map
{
	int			*grid;
	t_ivec2		grid_dim;
	int			player_ang;
	t_ivec2		player_pos0;
	mlx_image_t	*img;
}				t_map;

// PLAYER TYPES //
typedef struct s_draw
{
	bool	xy_axis;
	bool	rays;
}			t_draw;

typedef struct s_player
{
	t_vec2		p0;
	t_vec2		disp;
	t_vec2		camera;
	float		dgr;
	mlx_image_t	*shape;
	mlx_image_t	*view;
	int			*grid;
	t_ivec2		dof;
	t_draw		to_draw;
}				t_player;

// MAP FUNCs //
t_map_ctx	map_ctx(void);
void		init_map(t_map *map);
int			get_min_dim(t_ivec2 vec);
void		draw_minimap(t_map *mini_map);

// PLAYER FUNCs //
void		init_player(t_player *player, t_map *map);
void		player_shape(t_vec2 *geometry);
void		draw_player(void *param);

// PLAYER MOVEMENT //
void	movement(void *param);

#endif
