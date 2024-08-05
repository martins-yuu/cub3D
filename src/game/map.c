/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:49:47 by tforster          #+#    #+#             */
/*   Updated: 2024/07/16 17:01:40 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "color/color.h"
#include "ctx/ctx.h"
#include "ctx/constants.h"
// #include "graph_lib/graph_func.h"
#include "game/game.h"
#include "graph_lib/graph_types.h"


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
// #include "vector/bresenham.h"

static void	draw_minimap(mlx_image_t *mini_map_img);
static void	draw_cube(mlx_image_t *mini_map, t_ivec2 grid_dim, t_color c);

int	*map_0(int *g_x, int *g_y)
{
	*g_x = 8;
	*g_y = 8;

	static int grid[8 * 8] =
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};

	// *g_x = 5;
	// *g_y = 5;

	// static int grid[5 * 5] =
	// {
	// 	1, 1, 1, 1, 1,
	// 	1, 0, 0, 0, 1,
	// 	1, 0, 0, 0, 1,
	// 	1, 0, 0, 0, 1,
	// 	1, 1, 1, 1, 1,
	// };


	return (grid);
}

int	*map_1(int *g_x, int *g_y)
{
	*g_x = 30;
	*g_y = 8;
	static int grid[30 * 8] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0,78, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	return (grid);
}

int	*map_2(int *g_x, int *g_y)
{
	*g_x = 30;
	*g_y = 48;
	static int grid[30 * 48] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// 0
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,	// 1
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,	// 2
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1,	// 3
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1,	// 4
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,	// 5
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,	// 6
		1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	// 7
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 8
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 9
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 10
		1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 11
		1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 12
		1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 13
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 14
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 15
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 16
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 17
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 18
		1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 19
		1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 20
		1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 21
		1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 22
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 23
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 24
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 25
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 26
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 27
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 28
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 29
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 30
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 31
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 32
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 33
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 34
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 35
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 36
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 37
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 38
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 39
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 40
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 41
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 42
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 43
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 44
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 45
		1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 46
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 47
	};
	return (grid);
}

int	*map_3(int *g_x, int *g_y)
{
	*g_x = 8;
	*g_y = 48;
	static int grid[8 * 48] =
	{
		1, 1, 1, 1, 1, 1, 1, 1,		// 0
		1, 0, 0, 0, 0, 0, 0, 1,		// 1
		1, 0, 0, 0, 0, 0, 0, 1,		// 2
		1, 0, 0, 0, 0, 0, 0, 1,		// 3
		1, 0, 0, 0,78, 0, 0, 1,		// 4
		1, 0, 0, 0, 0, 0, 0, 1,		// 5
		1, 0, 0, 0, 0, 0, 0, 1,		// 6
		1, 0, 0, 0, 0, 0, 0, 1,		// 7
		1, 0, 0, 0, 0, 0, 0, 1,		// 8
		1, 0, 0, 0, 0, 0, 0, 1,		// 9
		1, 0, 0, 0, 0, 0, 0, 1,		// 10
		1, 0, 1, 0, 0, 0, 0, 1,		// 11
		1, 0, 1, 0, 0, 0, 0, 1,		// 12
		1, 0, 1, 0, 0, 0, 0, 1,		// 13
		1, 0, 0, 0, 0, 0, 0, 1,		// 14
		1, 0, 0, 0, 0, 0, 0, 1,		// 15
		1, 0, 0, 0, 0, 0, 0, 1,		// 16
		1, 0, 0, 0, 0, 0, 0, 1,		// 17
		1, 0, 0, 0, 0, 0, 0, 1,		// 18
		1, 0, 0, 0, 0, 0, 1, 1,		// 19
		1, 0, 0, 0, 0, 0, 1, 1,		// 20
		1, 0, 0, 0, 0, 1, 1, 1,		// 21
		1, 0, 0, 0, 0, 1, 1, 1,		// 22
		1, 0, 0, 0, 0, 0, 0, 1,		// 23
		1, 0, 0, 0, 0, 0, 0, 1,		// 24
		1, 0, 0, 0, 0, 0, 0, 1,		// 25
		1, 0, 0, 0, 0, 0, 0, 1,		// 26
		1, 0, 0, 0, 0, 0, 0, 1,		// 27
		1, 0, 0, 0, 0, 0, 0, 1,		// 28
		1, 0, 0, 0, 0, 0, 0, 1,		// 29
		1, 0, 0, 0, 0, 0, 0, 1,		// 30
		1, 0, 0, 0, 0, 0, 0, 1,		// 31
		1, 0, 0, 0, 0, 0, 0, 1,		// 32
		1, 0, 0, 0, 0, 0, 0, 1,		// 33
		1, 0, 0, 0, 0, 0, 0, 1,		// 34
		1, 0, 0, 0, 0, 0, 0, 1,		// 35
		1, 0, 0, 0, 0, 0, 0, 1,		// 36
		1, 0, 0, 0, 0, 0, 0, 1,		// 37
		1, 0, 0, 0, 0, 0, 0, 1,		// 38
		1, 0, 0, 0, 0, 0, 0, 1,		// 39
		1, 0, 0, 0, 0, 0, 0, 1,		// 40
		1, 0, 0, 0, 0, 0, 0, 1,		// 41
		1, 0, 0, 0, 0, 0, 0, 1,		// 42
		1, 0, 0, 0, 0, 0, 0, 1,		// 43
		1, 0, 0, 0, 0, 0, 0, 1,		// 44
		1, 0, 0, 0, 0, 0, 0, 1,		// 45
		1, 0, 0, 0, 0, 0, 0, 1,		// 46
		1, 1, 1, 1, 1, 1, 1, 1,		// 47
	};
	return (grid);
}

float	get_orientation(char ch)
{
	return ((ch == 'N') * 90.0 + (ch == 'S') * 270.0
		+ (ch == 'E') * 0.0 + (ch == 'W') + 180.0);
}

t_map_ctx	map_ctx(void)
{
	static t_map_ctx	map_ctx;
	int					g_x;
	int					g_y;

	if (map_ctx.grid == NULL)
	{
		map_ctx.grid = map_2(&g_x, &g_y);
		map_ctx.grid_dim = (t_ivec2){g_x, g_y};
		map_ctx.grid_p0 = (t_ivec2){(float) 4, (float) 4};
		map_ctx.orientation = get_orientation('N');
		map_ctx.min_dim = get_min_dim(map_ctx.grid_dim);
		map_ctx.img = ctx_img_new(MINI_MAP_S, MINI_MAP_S);
		// printf("MIN DIM %d\n",map_ctx.min_dim );
	}
	return (map_ctx);
}

void	init_map(void)
{
	ctx_img_display(map_ctx().img, 0, 0);
	map_ctx().img->enabled = false;
	map_ctx().img->instances->z = Z_MINI_MAP;
	draw_minimap(map_ctx().img);

}

static void	draw_minimap(mlx_image_t *mini_map_img)
{
	t_color		wall_c;
	t_color		space_c;

	wall_c = color_hex_alpha(S_WHT, A050);
	space_c = color_hex_alpha(S_BLK, A050);
	t_ivec2	grid_pos = (t_ivec2){0, 0};
	while (grid_pos.y < map_ctx().grid_dim.y)
	{
		grid_pos.x = 0;
		while (grid_pos.x < map_ctx().grid_dim.x)
		{
			if (map_ctx().grid[grid_pos.y * map_ctx().grid_dim.x + grid_pos.x] == 1)
				draw_cube(mini_map_img, grid_pos, wall_c);
			else
				draw_cube(mini_map_img, grid_pos, space_c);
			grid_pos.x++;
		}
		grid_pos.y++;
	}
}

static void	draw_cube(mlx_image_t *mini_map_img, t_ivec2 grd_pos, t_color c)
{
	t_color	c1;
	int	p;
	int	size;
	int	nb_pixels;

	size = map_ctx().min_dim;
	nb_pixels = size * size;
	p = 0;
	while (p < nb_pixels)
	{
		if (p % size == 0 || p % size == (size -1) || p / size == 0 || p / size  >= (size - 1))
			c1 = color_hex_alpha(D_GREY, A100);
		else
			c1 = c;
		mlx_put_pixel(mini_map_img, (p % size) + grd_pos.x * size, (p / size) + grd_pos.y * size, c1.value);
		p++;
	}
}

int	get_min_dim(t_ivec2 grid)
{
	t_ivec2	dim;
	int		min_dim;

	dim = (t_ivec2){MINI_MAP_S / grid.x, MINI_MAP_S / grid.y};
	return ((dim.x <= dim.y) * dim.x + (dim.y < dim.x) * dim.y);
}
