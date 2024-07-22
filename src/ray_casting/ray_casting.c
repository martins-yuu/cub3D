/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:38:13 by tforster          #+#    #+#             */
/*   Updated: 2024/07/22 18:07:53 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <math.h>
#include "color/color.h"
#include "graph_lib/graph_func.h"
#include "ray_casting/ray_casting.h"

static void	draw_2drays(t_player *player, float rx, float ry);

void	ray_casting(t_player *player)
{
	int		ray_nb;
	// t_ivec2	ivec;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	// int		side;
	// t_vec2	f_rays;
	float	rx;
	float	ry;
	float	vx;
	float	vy;
	float	ray_theta_deg;
	float	ray_theta_rad;
	float	xo;
	float	yo;

	float	dist_v;
	float	dist_h;

	// ray_theta_rad = fix_angle(player->dgr + 30);
	// ray_theta_rad = deg_rad(player->dgr);
	// float	dgr = player->dgr;
	ray_theta_deg = fix_angle(player->dgr + 30);
	// ray_theta_rad = fix_angle(player->dgr);
	// ray_theta_rad = player->dgr;

	ray_nb = 0;
	// int	total_rays = 61;
	int	total_rays = 257;
	while (ray_nb < total_rays)
	{
		// printf("%d[%.2f]\n", ray_nb, ray_theta_deg);
		ray_theta_rad = deg_rad(ray_theta_deg);
		// VERTICAL
		dof = 0;
		float tg = tanf(ray_theta_rad);
		dist_v = 100000;
		if (cos(ray_theta_rad) > 0.001)
		{
			rx = (((int) player->p0.x >> 6) << 6) + 64;
			ry = (player->p0.x - rx) * tg + player->p0.y;
			xo = 64;
			yo = -xo * tg;
		} // LEFT
		else if (cos(ray_theta_rad) < -0.001)
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
				dist_v = cosf(ray_theta_rad) * (rx - player->p0.x) - sinf(ray_theta_rad) * (ry - player->p0.y);
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
		if (sinf(ray_theta_rad) > 0.001)
		{
			ry = (((int) player->p0.y >> 6) << 6) - 0.0001;
			rx = (player->p0.y - ry) * inv_tg + player->p0.x;
			yo = -64;
			xo = -yo*inv_tg;
		} // UP
		else if (sinf(ray_theta_rad) < -0.001)
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
				dist_h = cosf(ray_theta_rad) * (rx - player->p0.x) - sinf(ray_theta_rad) * (ry - player->p0.y);

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

		draw_2drays(player, rx, ry);

		// DRAW VIEW
		// printf("[%d]DIST_H[%.2f]", ray_nb, dist_h);
		float view_theta = fix_angle(( (float) player->dgr - ray_theta_deg));
		dist_h = dist_h * cosf(deg_rad(view_theta));
		// dist_h = dist_h * cosf(deg_rad(ray_theta_deg));
		// printf("ANGs[%.2f][%.2f][%.2f]NEW[%.2f]\n",  player->dgr, ray_theta_deg, view_theta, dist_h);
		// dist_h = dist_h * cosf(view_theta);

		// int line_h = (64 * 320) / (dist_h);
		// if (line_h > 320)
		// {
		// 	line_h = 320;
		// }
		// int	line_off = 160 - (line_h / 2);

		int line_h = (64 * 640) / (dist_h);
		if (line_h > 640)
		{
			line_h = 640;
		}
		int	line_off = 320 - (line_h / 2);

		// int	line_with = 8;
		t_color	c = color_hex_alpha(RED, A100);
		int	j = 0;
		// int pixel_per_ray = 16;
		// int pixel_per_ray = 8;
		int pixel_per_ray = 4;
		while (j < line_h)
		{
			int	i = 0;
			while (i < pixel_per_ray)
			{
				mlx_put_pixel(player->view, ray_nb * pixel_per_ray + i, line_off + j, c.value);
				i++;
			}
			j++;
		}
		// ray_theta_deg = fix_angle(ray_theta_deg - 1);
		// ray_nb++;
		// ray_theta_deg = fix_angle(ray_theta_deg - 0.46875);
		ray_theta_deg = fix_angle(ray_theta_deg - 0.234375);
		ray_nb++;
	}
	// printf("ANG[%f][%f]\n", player->dgr, ray_theta_rad);
}

static void	draw_2drays(t_player *player, float rx, float ry)
{
	if (player->to_draw.rays)
	{
		t_ivec2 ivec[2];
		ivec[0].x =  (player->p0.x);
		ivec[0].y =  (player->p0.y);
		ivec[1].x =  rx;
		ivec[1].y =  ry;
		t_color	c = color_hex_alpha(RED, A100);
		t_line	line = {ivec[0], ivec[1], c, c};
		bresenham(player->map, &line);
	}
}
