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

#include "color/color.h"
#include "ctx/ctx.h"
#include "graph_lib/graph_func.h"
#include "game/game.h"

// #include "vector/bresenham.h"

static void	draw_minimap(t_map *mini_map);
static void	draw_cube(t_map *mini_map, int x, int y, t_color c);

void	init_map(t_map *mini_map, int width, int height)
{
	static int grid[8 * 8] =
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0,78, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};

	mini_map->grid = grid;
	mini_map->grid_size.x = 8;
	mini_map->grid_size.y = 8;
	mini_map->cube_s = 64;
	mini_map->player_pos0.x = 4;
	mini_map->player_pos0.y = 4;
	mini_map->img = ctx_img_new(width, height);
	ctx_img_display(mini_map->img, 0, 0);
	draw_minimap(mini_map);
}

static void	draw_minimap(t_map *mini_map)
{
	uint32_t	i;
	t_color		wall_c;
	t_color		space_c;

	int	x, y;
	i = 0;

	wall_c = color(S_WHT);
	space_c = color(S_BLK);
	x = 0;
	y = 0;
	while (y < mini_map->grid_size.y)
	{
		x = 0;
		while (x < mini_map->grid_size.x)
		{
			if (mini_map->grid[y * mini_map->grid_size.x + x] == 1)
				draw_cube(mini_map, x ,y, wall_c);
			else
				draw_cube(mini_map, x ,y, space_c);
			x++;
		}
		y++;
	}
}

static void	draw_cube(t_map *mini_map, int x, int y, t_color c)
{
	t_color	c1;
	int	p;
	int	size = mini_map->cube_s;
	int	nb_pixels = size * size;

	p = 0;
	while (p < nb_pixels)
	{
		if (p % size == 0 || p % size == (size -1) || p / size == 0 || p / size >= (size - 1))
			c1 = color(D_GREY);
		else
			c1 = c;
		mlx_put_pixel(mini_map->img, (p % 64) + x * size, (p / 64) + y * size, c1.value);
		p++;
	}
}
