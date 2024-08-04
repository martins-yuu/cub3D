/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:38:13 by tforster          #+#    #+#             */
/*   Updated: 2024/08/04 13:30:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdint.h>
// #include <stdio.h>

#include <math.h>
#include "ctx/ctx.h"
#include "graph_lib/graph_func.h"
#include "ray_casting/dda.h"

static void	draw_2drays(t_player *plr, t_vec2 ray_dir, int cube_size);

void	ray_casting(t_player *plr, int cube_size)
{
	const mlx_t	*instance = ctx();
	int			ray_nb;
	int			total_rays;
	float		ray_del;
	float		ray_theta_dgr;

	int			pixels = 1;
	total_rays = instance->width / pixels;
	ray_del = 60.0 / total_rays;
	ray_theta_dgr = fix_angle(plr->dgr + 30);
	ray_nb = 0;
	while (ray_nb < total_rays)
	{
		t_ray	ray;
		ray = dda(plr, ray_theta_dgr);
		draw_2drays(plr, ray.dir, cube_size);
		// DRAW VIEW
		float view_theta = fix_angle(((float) plr->dgr - ray_theta_dgr));
		ray.dist = ray.dist * cosf(deg_rad(view_theta));	// FIX FOR FISHEYE
		int line_h = (1 * instance->height) / (ray.dist);
		if (line_h > instance->height)
		{
			line_h = instance->height;
		}
		int	line_offset = instance->height / 2 - (line_h / 2);
		t_color	c;
		// c = color_hex_alpha(RED, A100);
		c = ray.color;
		int	j = 0;
		// int pixels = pixels;
		while (j < line_h)
		{
			int	i = 0;
			while (i < pixels)
			{
				mlx_put_pixel(plr->view, ray_nb * pixels + i, line_offset + j, c.value);
				i++;
			}
			j++;
		}
		ray_theta_dgr = fix_angle(ray_theta_dgr - ray_del);
		ray_nb++;
	}
}

static void	draw_2drays(t_player *plr, t_vec2 ray_dir, int cube_size)
{
	t_mat2	scale;
	t_vec2	n_vec[2];
	t_ivec2	pixel[2];

	if (plr->to_draw.rays)
	{
		scale = mat2_scale((t_vec2){(float) cube_size, (float) cube_size});
		n_vec[0] = mat2_vec2_mult(scale, plr->p0);
		n_vec[1] = mat2_vec2_mult(scale, ray_dir);
		pixel[0] = (t_ivec2){(int) n_vec[0].x, (int) n_vec[0].y};
		pixel[1] = (t_ivec2){(int) n_vec[1].x, (int) n_vec[1].y};
		t_color	c = color_hex_alpha(RED, A100);
		t_line	line = {pixel[0], pixel[1], c, c};
		bresenham(plr->map, &line);
	}
}
