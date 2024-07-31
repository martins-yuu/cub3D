/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:38:13 by tforster          #+#    #+#             */
/*   Updated: 2024/07/31 16:17:30 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

#include <math.h>

#include "ctx/ctx.h"
#include "color/color.h"
#include "game/game.h"
#include "graph_lib/graph_func.h"
#include "graph_lib/graph_types.h"
#include "ray_casting/ray_casting.h"

static void	draw_2drays(t_player *plr, float rx, float ry, int cube_size);

void	ray_casting(t_player *plr, int cube_size)
{
	const mlx_t	*instance = ctx();
	int			ray_nb;
	int			total_rays;
	float		ray_del;
	float		ray_theta_deg;

	// total_rays = instance->width / 4 - 2; // 1 pixel border on both sides
	total_rays = instance->width / 4;
	ray_del = 60.0 / total_rays;
	ray_theta_deg = fix_angle(plr->dgr + 30);



	ray_nb = 0;
	while (ray_nb <= total_rays)
	{
		float	ray_theta_rad;
		float	cos_theta;
		float	sin_theta;

		ray_theta_rad = deg_rad(ray_theta_deg);
		cos_theta = cosf(ray_theta_rad);
		sin_theta = sinf(ray_theta_rad);

		int		dof;

		t_ivec2	grid;
		int		index;
		t_vec2	ray_dir;
		t_vec2	vertical;
		t_vec2	step;

		float	dist_v;
		float	dist_h;

		// VERTICAL
		dof = 0;
		float tg;	// = tanf(ray_theta_rad);
		tg = sin_theta / cos_theta;
		dist_v = 10000;
		if (cos_theta > 0.001)
		{
			ray_dir.x = (int) plr->p0.x + 1,
			ray_dir.y = (plr->p0.x - ray_dir.x) * tg + plr->p0.y;
			step = (t_vec2) {1, -tg};
		} // LEFT
		else if (cos_theta < -0.001)
		{
			ray_dir.x = (int) plr->p0.x - 0.0001;
			ray_dir.y = (plr->p0.x - ray_dir.x) * tg + plr->p0.y;
			step = (t_vec2) {-1, tg};
		} // RIGHT
		else
		{
			ray_dir = (t_vec2){plr->p0.x, plr->p0.y};
			dof = plr->dof.x;
		} // looking straight up or down
		while (dof < plr->dof.x)
		{
			grid = (t_ivec2){(int) ray_dir.x, (int) ray_dir.y};
			index = grid.y * plr->dof.x + grid.x;
			if (index > 0 && index < (plr->dof.x * plr->dof.y) && plr->grid[index] == 1)
			{
				dof = plr->dof.x;
				dist_v = cos_theta * (ray_dir.x - plr->p0.x) - sin_theta * (ray_dir.y - plr->p0.y);
			} // HIT
			else
			{
				ray_dir = (t_vec2){ray_dir.x + step.x, ray_dir.y + step.y};
				dof +=1;
			} // CHECK NEXT VERTICAL
		}
		vertical = (t_vec2){ray_dir.x, ray_dir.y};
		// HORIZONTAL
		dof = 0;
		float inv_tg = 1.0 / tg;
		dist_h = 10000;
		if (sin_theta > 0.001)
		{
			ray_dir.y = (int) plr->p0.y - 0.0001;
			ray_dir.x = (plr->p0.y - ray_dir.y) * inv_tg + plr->p0.x;
			step = (t_vec2){inv_tg, -1};
		} // UP
		else if (sin_theta < -0.001)
		{
			ray_dir.y = (int) plr->p0.y + 1;
			ray_dir.x = (plr->p0.y - ray_dir.y) * inv_tg + plr->p0.x;
			step = (t_vec2){-inv_tg, 1};
		} // DOWN
		else
		{
			ray_dir = (t_vec2){plr->p0.x, plr->p0.y};
			dof = plr->dof.y;
		} // looking straight left or right
		while (dof < plr->dof.y)
		{
			grid = (t_ivec2){(int) ray_dir.x, (int) ray_dir.y};
			index = grid.y * plr->dof.x + grid.x;
			if (index > 0 && index < (plr->dof.x * plr->dof.y) && plr->grid[index] == 1)
			{
				dof = plr->dof.y;
				dist_h = cos_theta * (ray_dir.x - plr->p0.x) - sin_theta * (ray_dir.y - plr->p0.y);
			} // HIT
			else
			{
				ray_dir = (t_vec2){ray_dir.x + step.x, ray_dir.y + step.y};
				dof +=1;
			} // CHECK NEXT HORIZONTAL
		}
		if (dist_v < dist_h)
		{
			ray_dir.x = vertical.x;
			ray_dir.y = vertical.y;
			dist_h = dist_v;
		}

		draw_2drays(plr, ray_dir.x, ray_dir.y, cube_size);

		// DRAW VIEW
		// printf("[%d]DIST_H[%.2f]", ray_nb, dist_h);
		float view_theta = fix_angle(( (float) plr->dgr - ray_theta_deg));
		dist_h = dist_h * cosf(deg_rad(view_theta));	// FIX FOR FISHEYE
		// printf("ANGs[%.2f][%.2f][%.2f]NEW[%.2f]\n",  plr->dgr, ray_theta_deg, view_theta, dist_h);

		int line_h = (1 * instance->height) / (dist_h);
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
		ray_theta_deg = fix_angle(ray_theta_deg - ray_del);
		ray_nb++;
	}
	// printf("ANG[%f][%f]\n", plr->dgr, ray_theta_rad);
}

static void	draw_2drays(t_player *plr, float rx, float ry, int cube_size)
{
	if (plr->to_draw.rays)
	{
		// t_ivec2 ivec[2];
		// ivec[0].x =  (plr->p0.x);
		// ivec[0].y =  (plr->p0.y);
		// ivec[1].x =  rx;
		// ivec[1].y =  ry;

		// t_color	c = color_hex_alpha(RED, A10);
		// t_line	line = {ivec[0], ivec[1], c, c};
		// bresenham(plr->map, &line);

		t_vec2 vec[2];
		vec[0].x =  (plr->p0.x);
		vec[0].y =  (plr->p0.y);
		vec[1].x =  rx;
		vec[1].y =  ry;

		t_vec2 n_vec[2];
		t_mat2 scale;
		t_vec2	ratio;
		ratio = (t_vec2){(float) cube_size / 1, (float) cube_size / 1};
		scale = mat2_scale(ratio);

		// n_vec[0] = mat2_vec2_mult(scale, vec[0]);
		// n_vec[1] = mat2_vec2_mult(scale, vec[1]);
		n_vec[0] = mat2_vec2_mult(scale, plr->p0);
		n_vec[1] = mat2_vec2_mult(scale, vec[1]);


		t_ivec2	ivec[2];
		ivec[0] = (t_ivec2){(int) n_vec[0].x, (int) n_vec[0].y};
		ivec[1] = (t_ivec2){(int) n_vec[1].x, (int) n_vec[1].y};

		t_color	c = color_hex_alpha(RED, A100);
		t_line	line = {ivec[0], ivec[1], c, c};
		bresenham(plr->map, &line);
	}
}
