/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:03 by tforster          #+#    #+#             */
/*   Updated: 2024/07/16 22:10:57 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player/player.h"
#include "ctx/ctx.h"
#include "color/color.h"
#include "vector/angle.h"
#include "vector/bresenham.h"
#include "ft_string.h"

static void	orientation_vec(t_player *player, int center);
static void	draw_2drays(t_player *player);

void	init_player(t_map *map, t_player *player, int x0, int y0)
{
	mlx_image_t	*img;

	player->p0.x = (map->cube_s * map->player_pos0.x + map->cube_s / 2);
	player->p0.y = (map->cube_s * map->player_pos0.y + map->cube_s / 2);
	player->theta = 90;
	player->del.x = cosf(deg_rad(player->theta));
	player->del.y = -sinf(deg_rad(player->theta));
	player->size = PLAYER_SIZE;
	player->img = ctx_img_new(512, 512);
	player->grid = map->grid;
	ctx_img_display(player->img, 0, 0);
}

void	draw_player(void *param)
{
	uint32_t	i;
	uint32_t	size;
	t_color		c;
	t_player	*player;

	player = param;
	i = 0;
	ft_memset(player->img->pixels, 0,
		player->img->width * player->img->width * 4);
	size = player->size * player->size;
	while (i < size)
	{
		c = color(0xFFFF00FF);
		mlx_put_pixel(
			player->img,
			(i % player->size) + player->p0.x,
			(i / player->size) + player->p0.y, c.value);
		i++;
	}
	orientation_vec(player, player->size / 2 - 1);
	draw_2drays(player);
}

static void	draw_2drays(t_player *player)
{
	int		nb_ray;
	// t_ivec2	ivec;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		side;
	// t_fvec2	f_rays;
	float	rx;
	float	ry;
	float	vx;
	float	vy;
	float	ray_theta;
	float	xo;
	float	yo;

	ray_theta = player->theta;
	nb_ray = 0;
	while (nb_ray < 1)
	{
		float	tg;

		// vertical
		dof = 0;
		tg = tanf(deg_rad(ray_theta));

		// HORIZONTAL
		dof = 0;
		tg = 1 / tanf(ray_theta);
		if (sinf(deg_rad(ray_theta)) > 0.001)
		{
			ry = (((int) player->p0.y >> 6) << 6) - 0.0001;
			rx = (player->p0.y - ry) * tg + player->p0.x;
			yo = -64;
			xo = -yo * tg;
		} // UP
		else if (sinf(deg_rad(ray_theta)) < -0.001)
		{
			ry = (((int) player->p0.y >> 6) << 6) + 64;
			rx = (player->p0.y - ry) * tg + player->p0.x;
			yo = 64;
			xo = -yo * tg;
		} // DOWN
		else
		{
			rx = player->p0.x;
			ry = player->p0.y;
			dof = 8;
		} // looking straight left or right
		while (dof < 8)
		{
			mx = (int) rx >> 6;
			my = (int) ry >> 6;
			mp = my * player->img->width + mx;
			if (mp > 0 && mp < (player->img->width * player->img->height) && player->grid[mp] == 0)
			{
				dof = 8;
			} // HIT
			else
			{
				rx += xo;
				ry += yo;
				dof +=1;
			} // CHECK NEXT HORIZONTAL
		}
		nb_ray++;
		t_fvec2 fvec[2];
		fvec[0].x = player->p0.x + player->size / 2 - 1;
		fvec[0].y = player->p0.y + player->size / 2 - 1;

		fvec[1].x = rx;
		fvec[1].y = ry;

		bresenham(player->img, fvec);
	}
}

void	orientation_vec(t_player *player, int center)
{
	t_color			c;
	const t_fvec2	fvec[2] = {
	{player->p0.x + center, player->p0.y + center},
	{(player->p0.x + center + 50 * player->del.x),
		(player->p0.y + center + 50 * player->del.y),}};
	c = color(0xFFFF00FF);
	bresenham(player->img, (t_fvec2 *) fvec, c);
}
