/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:42:49 by tforster          #+#    #+#             */
/*   Updated: 2024/07/22 20:39:50 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color/color.h"
#include "ft_string.h"
#include "graph_lib/graph_func.h"
#include "graph_lib/graph_types.h"
#include "ray_casting/ray_casting.h"
#include "game/game.h"

#include <stdio.h>	// DELETE THIS
#include "MLX42/MLX42.h"
#include "ctx/ctx.h"

static void		transf_geometry(t_player *plr);
static t_mat2	transf_matrix_org(t_player *plr);
static void		draw_geometry(t_player *plr, t_mat2 *mat);
static void		draw_xy_axis(t_player *plr);


// typedef void (*mlx_resizefunc)(int32_t width, int32_t height, void* param);

static void	resize(int32_t width, int32_t height, void* param)
{
	mlx_t *instance = ctx();
	instance->width = 512;
	instance->height = 320;
}

void	draw_player(void *param)
{
	t_color		c;
	t_player	*plr;

	plr = param;
	ft_memset(plr->map->pixels, 0, plr->map->width * plr->map->height * 4);
	ft_memset(plr->view->pixels, 0, plr->view->width * plr->view->height * 4);
	ray_casting(plr);
	transf_geometry(plr);
	if (plr->to_draw.xy_axis)
		draw_xy_axis(plr);

	// TEST
	mlx_t *instance = ctx();
	if (plr->cam_view.x != instance->width || plr->cam_view.y != instance->height)
	{
		if (instance->width < 512 || instance->height < 320)
		{
			t_ivec2	can_view = {512, 320};
			mlx_resize_hook(instance, resize, &can_view);
			instance->width = 512;
			instance->height = 320;
		}
		printf(">>> START WIDHT[%d] HEIGHT[%d]\n", instance->width, instance->height);
		plr->cam_view = (t_ivec2){instance->width, instance->height};
	}
	// TEST
}

void	transf_geometry(t_player *plr)
{
	t_mat2	mat;

	mat = transf_matrix_org(plr);
	draw_geometry(plr, &mat);
}

static t_mat2	transf_matrix_org(t_player *plr)
{
	float	obj_deg;
	t_mat2	rotate;
	t_mat2	translate;

	obj_deg = plr->dgr - 90;
	rotate = mat2_rotate(&obj_deg);
	translate = mat2_translate(&plr->p0);
	return (mat2_mat2_mult(&translate, &rotate));
}

void	draw_geometry(t_player *plr, t_mat2 *mat)
{
	int		p;
	t_vec2	new_p[2];
	t_ivec2	int_p[2];
	t_line	plr_line;
	t_color	plr_c;

	plr_c = color_hex_alpha(YELLOW, A100);
	p = 0;
	while (p < 10)
	{
		new_p[0] = mat2_vec2_mult(mat, &plr->geometry[p % 10]);
		new_p[1] = mat2_vec2_mult(mat, &plr->geometry[(p + 1) % 10]);
		int_p[0] = (t_ivec2){(int) new_p[0].x, (int) new_p[0].y};
		int_p[1] = (t_ivec2){(int) new_p[1].x, (int) new_p[1].y};
		plr_line = (t_line){int_p[0], int_p[1], plr_c, plr_c};
		bresenham(plr->map, &plr_line);
		p++;
	}
}

void	draw_xy_axis(t_player *plr)
{
	t_color	c;
	t_line	line_h;
	t_line	line_v;

	c = color_hex_alpha(WHITE, A100);
	line_h = (t_line){{plr->p0.x, 60}, {plr->p0.x, 500}, c, c};
	line_v = (t_line){{60, plr->p0.y}, {500, plr->p0.y}, c, c};
	bresenham(plr->map, &line_h);
	bresenham(plr->map, &line_v);
}
