/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:00 by tforster          #+#    #+#             */
/*   Updated: 2024/08/08 13:43:53 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdbool.h>
# include "MLX42/MLX42.h"
# include "graph_lib/graph_types.h"

// MAP ATTRIBUTES //
# define MINI_MAP_S	480

// PLAYER ATTRIBUTES //
# define PLAYER_SIZE	7
# define WALL_OFFSET	0.1

// PLAYER MOVEMENT //
# define STEP			0.05
# define STRF_STEP		0.02

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
	float		orientation;
	int			min_dim;
	mlx_image_t	*img;
}				t_map_ctx;

// PLAYER TYPES //
typedef struct s_draw
{
	bool		xy_axis;
	bool		rays;
}				t_draw;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*floor;
	mlx_texture_t	*ceiling;
}				t_texture;

typedef struct s_player
{
	t_vec2		p0;
	t_vec2		disp;
	float		dgr;
	mlx_image_t	*shape;
	mlx_image_t	*view;
	int			pixel;
	float		fov;
	t_draw		to_draw;
	t_texture	*texture;
}				t_player;

// MAP FUNCs //
t_map_ctx	map_ctx(void);
void		init_map(void);

// PLAYER FUNCs //
void		init_player(t_player *player);
void		player_shape(t_vec2 *geometry);
void		draw_player(void *param);

// PLAYER MOVEMENT //
void		movement(void *param);

#endif
