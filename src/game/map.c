/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:17:56 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 19:22:03 by tforster         ###   ########.fr       */
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
static int	get_min_dim(const t_ivec2 grid);

int	*map_0(int *grid_x, int *grid_y)
{
	static int	grid[] = {
		#include "map0.cub"
	};

	*grid_x = 13;
	*grid_y = 13;
	return (grid);
}

int	*map_1(int *grid_x, int *grid_y)
{
	static int	grid[] = {
		#include "map1.cub"
	};

	*grid_x = 30;
	*grid_y = 8;
	return (grid);
}

int	*map_2(int *grid_x, int *grid_y)
{
	static int	grid[] = {
		#include "map2.cub"
	};

	*grid_x = 30;
	*grid_y = 48;
	return (grid);
}

int	*map_3(int *grid_x, int *grid_y)
{
	static int	grid[] = {
		#include "map3.cub"
	};

	*grid_x = 8;
	*grid_y = 48;
	return (grid);
}

float	get_orientation(char ch)
{
	return ((ch == 'N') * 90.0 + (ch == 'S') * 270.0
		+ (ch == 'E') * 0.0 + (ch == 'W') * 180.0);
}

t_map_ctx	map_ctx(void)
{
	static t_map_ctx	map_ctx;
	int					grid_x;
	int					grid_y;

	if (map_ctx.grid == NULL)
	{
		map_ctx.grid = map_2(&grid_x, &grid_y);
		map_ctx.grid_dim = (t_ivec2){grid_x, grid_y};
		map_ctx.grid_p0 = (t_ivec2){(float) 6, (float) 4};
		map_ctx.orientation = get_orientation('N');
		map_ctx.min_dim = get_min_dim(map_ctx.grid_dim);
		map_ctx.img = ctx_img_new(MINI_MAP_S, MINI_MAP_S);
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
	const t_color	wall_c = color_hex_alpha(BROWN, A050);
	const t_color	space_c = color_hex_alpha(S_BLK, A050);
	t_ivec2			grid_pos;

	grid_pos.y = 0 ;
	while (grid_pos.y < map_ctx().grid_dim.y)
	{
		grid_pos.x = 0;
		while (grid_pos.x < map_ctx().grid_dim.x)
		{
			if (map_ctx().grid[grid_pos.y * map_ctx().grid_dim.x
					+ grid_pos.x] == 1)
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
	t_color		c1;
	int			p;
	const int	size = map_ctx().min_dim;
	const int	nb_pixels = size * size;

	p = 0;
	while (p < nb_pixels)
	{
		if (p % size == 0 || p % size == (size -1)
			|| p / size == 0 || p / size >= (size - 1))
			c1 = color_hex_alpha(D_GREY, A100);
		else
			c1 = c;
		mlx_put_pixel(mini_map_img, (p % size) + grd_pos.x * size,
			(p / size) + grd_pos.y * size, c1.value);
		p++;
	}
}

static int	get_min_dim(const t_ivec2 grid)
{
	const t_ivec2	dim = (t_ivec2)
	{
		MINI_MAP_S / grid.x,
		MINI_MAP_S / grid.y,
	};

	return ((dim.x <= dim.y) * dim.x + (dim.y < dim.x) * dim.y);
}
