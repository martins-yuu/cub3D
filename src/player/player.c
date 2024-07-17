/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:35:03 by tforster          #+#    #+#             */
/*   Updated: 2024/07/17 13:47:30 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player/player.h"
#include "ctx/ctx.h"
#include "color/color.h"
#include "vector/angle.h"
#include "vector/bresenham.h"
#include "ft_string.h"


#include "stdio.h"

static void	orientation_vec(t_player *player, int center);
static void	draw_2drays(t_player *player);

void	init_player(t_map *map, t_player *player, int x0, int y0)
{
	mlx_image_t	*img;

	player->p0.x = (float) (map->cube_s * map->player_pos0.x + map->cube_s / 2);
	player->p0.y = (float) (map->cube_s * map->player_pos0.y + map->cube_s / 2);
	player->theta_dg = 90;
	player->del.x = cosf(deg_rad(player->theta_dg));
	player->del.y = -sinf(deg_rad(player->theta_dg));
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
	draw_2drays(player);
	orientation_vec(player, player->size / 2 - 1);
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
	float	theta_rad;
	float	xo;
	float	yo;

	float	dist_v;
	float	dist_h;

	// theta_rad = fix_angle(player->theta_dg + 30);
	// theta_rad = deg_rad(player->theta_dg);
	// float	degree = player->theta_dg;
	theta_rad = deg_rad(fix_angle (player->theta_dg));
	// theta_rad = fix_angle(player->theta_dg);
	// theta_rad = player->theta_dg;

	nb_ray = 0;
	while (nb_ray < 1)
	{
		// VERTICAL
		dof = 0;
		float tg = tanf(theta_rad);
		dist_v = 100000;
		if (cos(theta_rad) > 0.001)
		{
			rx = (((int) player->p0.x >> 6) << 6) + 64;
			ry = (player->p0.x - rx) * tg + player->p0.y;
			xo = 64;
			yo = -xo * tg;
		} // LEFT
		else if (cos(theta_rad) < -0.001)
		{
			rx = (((int) player->p0.x >> 6) << 6) - 0.0001;
			ry = (player->p0.x - rx) * tg + player->p0.y;
			xo = -64;
			yo = -xo * tg;
		} // RIGHT
		else
		{
			rx = player->p0.x;
			ry = player->p0.y;
			dof = 8;
		} // looking straight up or down
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;

			mp = my * 8 + mx;
			if (mp > 0 && mp < (8 * 8) && player->grid[mp] == 1)
			{
				dof = 8;
				dist_v = cosf(theta_rad) * (rx - player->p0.y) - sinf(theta_rad) * (ry - player->p0.y);
			} // HIT
			else
			{
				rx += xo;
				ry += yo;
				dof +=1;
			} // CHECK NEXT HORIZONTAL
		}
		vx = rx;
		vy = ry;

		// HORIZONTAL
		dof = 0;
		float inv_tg = 1.0 / tg;
		dist_h = 100000;
		if (sinf(theta_rad) > 0.001)
		{
			ry = (((int)player->p0.y>>6)<< 6) - 0.0001;
			rx = (player->p0.y - ry) * inv_tg + player->p0.x;
			yo = -64;
			xo = -yo*inv_tg;
		} // UP
		else if (sinf(theta_rad) < -0.001)
		{
			ry = (((int) player->p0.y >> 6) << 6) + 64;
			rx = (player->p0.y - ry) * inv_tg + player->p0.x;
			yo = 64;
			xo = -yo*inv_tg;
		} // DOWN
		else
		{
			rx = player->p0.x;
			ry = player->p0.y;
			dof = 8;
		} // looking straight left or right
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;

			mp = my * 8 + mx;
			if (mp > 0 && mp < (8 * 8) && player->grid[mp] == 1)
			{
				dof = 8;
				dist_h = cosf(theta_rad) * (rx - player->p0.y) - sinf(theta_rad) * (ry - player->p0.y);

			} // HIT
			else
			{
				rx += xo;
				ry += yo;
				dof +=1;
			} // CHECK NEXT HORIZONTAL
		}
		if (dist_v < dist_h)
		{
			rx = vx;
			ry = vy;
			dist_h = dist_v;
		}
		nb_ray++;
		t_fvec2 fvec[2];
		fvec[0].x = player->p0.x + player->size / 2 - 1;
		fvec[0].y = player->p0.y + player->size / 2 - 1;

		fvec[1].x = rx;
		fvec[1].y = ry;
		t_color	c = color(0xFF0000FF);
		bresenham(player->img, fvec, c);
	}
	// printf("ANG[%f][%f]\n", player->theta_dg, theta_rad);
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
