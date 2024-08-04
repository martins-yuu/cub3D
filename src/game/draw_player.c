/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:42:49 by tforster          #+#    #+#             */
/*   Updated: 2024/08/04 17:55:29 by tforster         ###   ########.fr       */
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

static void		transf_geometry(t_player *plr, t_vec2 p0);
static t_mat2	transf_matrix_org(t_vec2 p0, float drg);
static void		draw_geometry(t_player *plr, t_mat2 mat);
static void		draw_xy_axis(mlx_image_t *map, t_vec2 p0, int cube_size);

void	draw_player(void *param)
{
	t_color		c;
	t_player	*plr;

	plr = param;
	ft_memset(plr->shape->pixels, 0, plr->shape->width * plr->shape->height * 4);
	ft_memset(plr->view->pixels, 0, plr->view->width * plr->view->height * 4);

	// Normalize coord for the minimap
	int	cube_size;
	cube_size = get_min_dim((plr->dof));
	t_vec2 normal_p0;
	normal_p0.x = ((float) cube_size) * plr->p0.x;
	normal_p0.y = ((float) cube_size) * plr->p0.y;

	ray_casting(plr, cube_size);
	transf_geometry(plr, normal_p0);
	if (plr->to_draw.xy_axis)
		draw_xy_axis(plr->shape, normal_p0, cube_size);
	// printf("DELTA[%f] PS [%f]\n", ctx()->delta_time, 1/ctx()->delta_time);
}

static void	transf_geometry(t_player *plr, t_vec2 p0)
{
	t_mat2	mat;

	mat = transf_matrix_org(p0, plr->dgr);
	draw_geometry(plr, mat);
}

static t_mat2	transf_matrix_org(t_vec2 p0, float drg)
{
	float	obj_deg;
	t_mat2	rotate;
	t_mat2	translate;

	obj_deg = drg - 90;
	rotate = mat2_rotate(obj_deg);
	translate = mat2_translate(p0);
	return (mat2_mat2_mult(translate, rotate));
}

static void	draw_geometry(t_player *plr, t_mat2 mat)
{
	int		p;
	t_vec2	shape[10];
	t_vec2	new_p[2];
	t_ivec2	int_p[2];
	t_line	plr_line;

	player_shape(shape);
	p = 0;
	while (p < 10)
	{
		new_p[0] = mat2_vec2_mult(mat, shape[p % 10]);
		new_p[1] = mat2_vec2_mult(mat, shape[(p + 1) % 10]);
		int_p[0] = (t_ivec2){(int) new_p[0].x, (int) new_p[0].y};
		int_p[1] = (t_ivec2){(int) new_p[1].x, (int) new_p[1].y};
		plr_line = (t_line)
		{
			int_p[0], int_p[1],
			color_hex_alpha(YELLOW, A100),
			color_hex_alpha(YELLOW, A100),
		};
		bresenham(plr->shape, &plr_line);
		p++;
	}
}

static void	draw_xy_axis(mlx_image_t *map, t_vec2 p0, int cube_size)
{
	t_color	c;
	t_line	line_v;
	t_line	line_h;

	int	v_len = map->width;
	int	h_len = map->height;

	c = color_hex_alpha(WHITE, A100);
	line_v = (t_line){{30, p0.y}, {v_len - 30, p0.y}, c, c};
	line_h = (t_line){{p0.x, 30}, {p0.x, h_len - 30}, c, c};
	bresenham(map, &line_v);
	bresenham(map, &line_h);
}
