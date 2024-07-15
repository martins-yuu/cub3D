/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:01 by yuuko             #+#    #+#             */
/*   Updated: 2024/07/15 20:22:42 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "color/color.h"
#include "ctx/constants.h"
#include "ctx/ctx.h"
#include "ft_string.h"
#include "map/map.h"
#include <stdint.h>
#include <stdlib.h>

// LEGAL?
#include <stdio.h>
// LEGAL?

void	draw_cube(mlx_image_t *img_mini, t_map *map, int x, int y, t_color c)
{
	t_color	c1;
	int	p;
	int	size = map->cube_s;
	int	nb_pixels = size * size;

	p = 0;
	while (p < nb_pixels)
	{
		if (p % size == 0 || p % size == (size -1) || p / size == 0 || p / size >= (size - 1))
			c1 = color(0x646464FF);
		else
			c1 = c;
		mlx_put_pixel(img_mini, (p % 64) + x * size, (p / 64) + y * size, c1.value);
		p++;
	}
}


static void	draw_minimap(void *param, t_map *map)
{
	uint32_t	i;
	uint32_t	size;
	t_color		c[2];
	mlx_image_t	*img_mini;

	int	x, y, x0, y0;
	img_mini = param;
	i = 0;
	size = img_mini->width * img_mini->height;

	int	l = 0;
	c[0] = color(0xf0f0f0FF);
	c[1] = color(0x272727ff);
	x = 0;
	y = 0;
	while (y < map->len_y)
	{
		x = 0;
		while (x < map->len_x)
		{
			if (map->grid[y * map->len_x + x] == 1)
				draw_cube(img_mini, map, x ,y, c[0]);
			else
				draw_cube(img_mini, map, x ,y, c[1]);
			x++;
		}
		y++;
	}
}

static void	draw_player(void *param)
{
	uint32_t	i;
	uint32_t	size;
	t_color		c;
	mlx_image_t	*img;

	img = param;
	i = 0;
	// size = img->width * img->height;
	size = 49;
	while (i < size)
	{
		c = color(0xFFFF00FF);
		// mlx_put_pixel(img, i % img->width, i / img->width, c.value);
		mlx_put_pixel(img, i % 7, i / 7, c.value);
		i++;
	}
}

void	basic_keys(mlx_key_data_t data, void *param)
{
	mlx_image_t	*img;

	img = param;
	if (data.key == MLX_KEY_ESCAPE && data.action == MLX_PRESS)
		mlx_close_window(ctx());
}

#include <math.h>

float deg_rad(int theta)
{
	return(theta * M_PI/180.0);
}

void	fix_angle(int *theta)
{
	if (*theta > 359)
		*theta -= 360;
	if (*theta < 0)
		*theta += 360;
}

void	handle_movement(void *param)
{
	t_player	*player;

	player = param;
	//  LEFT
	if (mlx_is_key_down(ctx(), MLX_KEY_A))
	{
		player->theta += 5;
		player->dx = cosf(deg_rad (player->theta));
		player->dy = -sinf(deg_rad (player->theta));
	}
	// RIGHT
	if (mlx_is_key_down(ctx(), MLX_KEY_D))
	{
		player->theta -= 5;
		player->dx = cosf(deg_rad (player->theta));
		player->dy = -sinf(deg_rad (player->theta));
	}
	// UP
	if (mlx_is_key_down(ctx(), MLX_KEY_W))
	{
		// printf("W THETA %d dy[%f] dx[%f] \n", player->theta, player->dy, player->dx);
		player->img->instances[0].x += (int) (5.0 * player->dx);
		player->img->instances[0].y += (int) (5.0 * player->dy);
	}
	// DOWN
	if (mlx_is_key_down(ctx(), MLX_KEY_S))
	{
		// printf("S THETA %d dy[%f] dx[%f] \n", player->theta, player->dy, player->dx);
		player->img->instances[0].x -= (int) (5.0 * player->dx);
		player->img->instances[0].y -= (int) (5.0 * player->dy);
	}
}

void	init_player(t_player *player, int x0, int y0)
{
		mlx_image_t	*img;

		player->x0 = x0;
		player->y0 = y0;
		player->theta = 90;
		player->dx = cosf(deg_rad(player->theta));
		player->dy = -sinf(deg_rad(player->theta));
		img = ctx_img_new(512, 512);
		ctx_img_display(img, x0, y0);
		player->img = img;
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	t_map		map;
	t_player	player;
	mlx_image_t	*img_mini;

	init_map(&map);
	ctx();
	img_mini = ctx_img_new(512, 512);
	ctx_img_display(img_mini, 0, 0);
	draw_minimap(img_mini, &map);

	init_player(&player, 300, 300);
	draw_player(player.img);

	ctx_on_key(basic_keys, NULL);
	ctx_on_loop(handle_movement, &player);

	mlx_loop(ctx());
	mlx_terminate(ctx());
	return (EXIT_SUCCESS);
}
