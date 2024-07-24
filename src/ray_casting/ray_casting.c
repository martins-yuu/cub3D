/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:38:13 by tforster          #+#    #+#             */
/*   Updated: 2024/07/24 17:56:27 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <math.h>

#include "ctx/ctx.h"
#include "color/color.h"
#include "graph_lib/graph_func.h"
#include "ray_casting/ray_casting.h"

static void	draw_2drays(t_player *plr, float rx, float ry);

void	ray_casting(t_player *plr)
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

	mlx_t *instance = ctx();

	ray_theta_deg = fix_angle(plr->dgr + 30);

	int		total_rays;
	float	del_drg;

	total_rays = instance->width / 4 - 2; // 1 pixel border on both sides
	del_drg = 60.0 / total_rays;
	ray_nb = 0;
	while (ray_nb <= total_rays)
	{
		// printf("%d[%.2f]\n", ray_nb, ray_theta_deg);
		ray_theta_rad = deg_rad(ray_theta_deg);
		// VERTICAL
		dof = 0;
		float tg = tanf(ray_theta_rad);
		dist_v = 100000;
		if (cos(ray_theta_rad) > 0.001)
		{
			rx = (((int) plr->p0.x >> 6) << 6) + 64;
			ry = (plr->p0.x - rx) * tg + plr->p0.y;
			xo = 64;
			yo = -xo * tg;
		} // LEFT
		else if (cos(ray_theta_rad) < -0.001)
		{
			rx = (((int) plr->p0.x >> 6) << 6) - 0.0001;
			ry = (plr->p0.x - rx) * tg + plr->p0.y;
			xo = -64;
			yo = -xo * tg;
		} // RIGHT
		else
		{
			rx = plr->p0.x;
			ry = plr->p0.y;
			dof = plr->dof.x;
		} // looking straight up or down
		while (dof < plr->dof.x)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * plr->dof.x + mx;
			if (mp > 0 && mp < (plr->dof.x * plr->dof.y) && plr->grid[mp] == 1)
			{
				dof = plr->dof.x;
				dist_v = cosf(ray_theta_rad) * (rx - plr->p0.x) - sinf(ray_theta_rad) * (ry - plr->p0.y);
			} // HIT
			else
			{
				rx += xo;
				ry += yo;
				dof +=1;
			} // CHECK NEXT VERTICAL
		}
		vx = rx;
		vy = ry;

		// HORIZONTAL
		dof = 0;
		float inv_tg = 1.0 / tg;
		dist_h = 100000;
		if (sinf(ray_theta_rad) > 0.001)
		{
			ry = (((int) plr->p0.y >> 6) << 6) - 0.0001;
			rx = (plr->p0.y - ry) * inv_tg + plr->p0.x;
			yo = -64;
			xo = -yo*inv_tg;
		} // UP
		else if (sinf(ray_theta_rad) < -0.001)
		{
			ry = (((int) plr->p0.y >> 6) << 6) + 64;
			rx = (plr->p0.y - ry) * inv_tg + plr->p0.x;
			yo = 64;
			xo = -yo*inv_tg;
		} // DOWN
		else
		{
			rx = plr->p0.x;
			ry = plr->p0.y;
			dof = plr->dof.y;
		} // looking straight left or right
		while (dof < plr->dof.y)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * plr->dof.x + mx;
			if (mp > 0 && mp < (plr->dof.x * plr->dof.y) && plr->grid[mp] == 1)
			{
				dof = plr->dof.y;
				dist_h = cosf(ray_theta_rad) * (rx - plr->p0.x) - sinf(ray_theta_rad) * (ry - plr->p0.y);

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

		draw_2drays(plr, rx, ry);

		// DRAW VIEW
		// printf("[%d]DIST_H[%.2f]", ray_nb, dist_h);
		float view_theta = fix_angle(( (float) plr->dgr - ray_theta_deg));
		dist_h = dist_h * cosf(deg_rad(view_theta));	// FIX FOR FISHEYE
		// printf("ANGs[%.2f][%.2f][%.2f]NEW[%.2f]\n",  plr->dgr, ray_theta_deg, view_theta, dist_h);

		int line_h = (64 * instance->height) / (dist_h);
		if (line_h > instance->height)
		{
			line_h = instance->height;
		}
		int	line_off = instance->height / 2 - (line_h / 2);

		t_color	c = color_hex_alpha(RED, A100);
		int	j = 0;
		int pixel_per_ray = 4;
		while (j < line_h)
		{
			int	i = 0;
			while (i < pixel_per_ray)
			{
				mlx_put_pixel(plr->view, ray_nb * pixel_per_ray + i, line_off + j, c.value);
				i++;
			}
			j++;
		}
		ray_theta_deg = fix_angle(ray_theta_deg - del_drg);
		ray_nb++;
	}
	// printf("ANG[%f][%f]\n", plr->dgr, ray_theta_rad);
}

static void	draw_2drays(t_player *plr, float rx, float ry)
{
	if (plr->to_draw.rays)
	{
		t_ivec2 ivec[2];
		ivec[0].x =  (plr->p0.x);
		ivec[0].y =  (plr->p0.y);
		ivec[1].x =  rx;
		ivec[1].y =  ry;
		t_color	c = color_hex_alpha(RED, A100);
		t_line	line = {ivec[0], ivec[1], c, c};
		bresenham(plr->map, &line);
	}
}
