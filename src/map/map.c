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

#include "map/map.h"
#include "ctx/ctx.h"
#include "color/color.h"

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
	t_color		c[2];

	int	x, y, x0, y0;
	i = 0;

	int	l = 0;
	c[0] = color(0xf0f0f0FF);
	c[1] = color(0x272727ff);
	x = 0;
	y = 0;
	while (y < mini_map->grid_size.y)
	{
		x = 0;
		while (x < mini_map->grid_size.x)
		{
			if (mini_map->grid[y * mini_map->grid_size.x + x] == 1)
				draw_cube(mini_map, x ,y, c[0]);
			else
				draw_cube(mini_map, x ,y, c[1]);
			x++;
		}
		y++;
	}

	// t_fvec2 v0 = {100, 100};
	// t_fvec2 v1 = {400, 400};
	// bresenham(mini_map->img, &v0, &v1);
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
			c1 = color(0x646464FF);
		else
			c1 = c;
		mlx_put_pixel(mini_map->img, (p % 64) + x * size, (p / 64) + y * size, c1.value);
		p++;
	}
}
