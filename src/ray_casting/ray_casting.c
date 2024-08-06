/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:38:13 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 17:06:57 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdint.h>
// #include <stdio.h>

#include <math.h>
#include <stdint.h>
#include "ctx/ctx.h"
#include "game/game.h"
#include "graph_lib/graph_func.h"
#include "graph_lib/graph_types.h"
#include "ray_casting/dda.h"
#include "ray_casting/ray_types.h"

static void	loop_rays(t_player *plr, float ray_theta_dgr);
static void	draw_2drays(t_player *plr, const t_vec2 ray_dir);
static void	draw_view(t_player *plr, const t_ray ray,
				const float view_theta, const int ray_nb);
static int	get_line_height(const float dist, const float view_theta);

void	ray_casting(t_player *plr)
{
	const float	ray_theta_dgr = fix_angle(plr->dgr + plr->fov / 2);

	loop_rays(plr, ray_theta_dgr);
}

static void	loop_rays(t_player *plr, float ray_theta_dgr)
{
	int			ray_nb;
	float		ray_theta_del;
	t_ray		ray;
	const int	total_rays = ctx()->width / plr->pixel;

	ray_theta_del = plr->fov / total_rays;
	ray_nb = 0;
	while (ray_nb < total_rays)
	{
		ray = dda(plr, ray_theta_dgr);
		draw_2drays(plr, ray.dir);
		draw_view(plr, ray, fix_angle((plr->dgr - ray_theta_dgr)), ray_nb);
		ray_theta_dgr = fix_angle(ray_theta_dgr - ray_theta_del);
		ray_nb++;
	}
}

static void	draw_2drays(t_player *plr, const t_vec2 ray_dir)
{
	t_mat2			scale;
	t_vec2			n_vec[2];
	t_ivec2			pixel[2];
	t_line			line;
	const t_color	c = color_hex_alpha(RED, A100);

	if (plr->to_draw.rays)
	{
		scale = mat2_scale((t_vec2){map_ctx().min_dim, map_ctx().min_dim, 1});
		n_vec[0] = mat2_vec2_mult(scale, plr->p0);
		n_vec[1] = mat2_vec2_mult(scale, ray_dir);
		pixel[0] = (t_ivec2){(int) n_vec[0].x, (int) n_vec[0].y};
		pixel[1] = (t_ivec2){(int) n_vec[1].x, (int) n_vec[1].y};
		line = (t_line){pixel[0], pixel[1], c, c};
		bresenham(plr->shape, &line);
	}
}

static void	draw_view(t_player *plr, const t_ray ray,
				const float view_theta, const int ray_nb)
{
	t_ivec2			i;
	const int		line_h = get_line_height(ray.dist, view_theta);
	const int		line_offset = ctx()->height / 2 - (line_h / 2);
	const t_color	c = ray.color;

	i.y = 0;
	while (i.y < line_h)
	{
		i.x = 0;
		while (i.x < plr->pixel)
		{
			mlx_put_pixel(plr->view, ray_nb * plr->pixel + i.x,
				line_offset + i.y, c.value);
			i.x++;
		}
		i.y++;
	}
}

static int	get_line_height(const float dist, const float view_theta)
{
	int	line_h;

	line_h = (1 * ctx()->height) / (dist * cosf(deg_rad(view_theta)));
	if (line_h > ctx()->height)
		line_h = ctx()->height;
	return (line_h);
}
