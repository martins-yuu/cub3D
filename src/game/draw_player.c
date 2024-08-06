/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:42:49 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 19:23:22 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color/color.h"
#include "ft_string.h"
#include "graph_lib/graph_func.h"
#include "graph_lib/graph_types.h"
#include "ray_casting/ray_casting.h"
#include "game/game.h"

#include <stdint.h>
#include <stdio.h>	// DELETE THIS
#include "MLX42/MLX42.h"
#include "ctx/ctx.h"

static void		draw_planes(mlx_image_t	*view);
static void		draw_geometry(t_player *plr, const t_mat2 mat);
static t_mat2	transf_matrix_org(t_vec2 p0, const float drg);
static void		draw_xy_axis(mlx_image_t *map, const t_vec2 p0);

/**
 * @brief Draws the player on the screen.
 * @details Cleans the image buffer.
 * Run the ray_casting() function
 * Auto scale player and rays for the mini map size.
 *
 * @param param Pointer to the player parameter.
 * @note @param param will be cast to a @struct t_player.
 */
void	draw_player(void *param)
{
	t_player	*plr;
	t_vec2		normal_p0;

	plr = param;
	ft_memset(plr->shape->pixels, 0,
		plr->shape->width * plr->shape->height * 4);
	draw_planes(plr->view);
	ray_casting(plr);
	normal_p0 = (t_vec2)
	{
		(float) map_ctx().min_dim * plr->p0.x,
		(float) map_ctx().min_dim * plr->p0.y,
		1,
	};
	draw_geometry(plr, transf_matrix_org(normal_p0, plr->dgr));
	if (plr->to_draw.xy_axis)
		draw_xy_axis(plr->shape, normal_p0);
}
	// printf("DELTA[%f] FPS [%f]\n", ctx()->delta_time, 1/ctx()->delta_time);

static void	draw_planes(mlx_image_t	*view)
{
	t_ivec2			i;
	const int		height = ctx()->height;
	const int		width = ctx()->width;
	const t_color	floor = color_hex_alpha(L_GREY, A100);
	t_color			ceiling;

	i.y = 0;
	while (i.y < height)
	{
		ceiling = color_lerp(color_hex_alpha(WHITE, A100),
				color_hex_alpha(BLUE, A100), (float) i.y / height);
		i.x = 0;
		while (i.x < width)
		{
			if (i.y < height / 2)
				mlx_put_pixel(view, i.x, i.y, ceiling.value);
			else
				mlx_put_pixel(view, i.x, i.y, floor.value);
			i.x++;
		}
		i.y++;
	}
}

/**
 * @brief Creates a transformation matrix based on the origin point and degree.
 * @details Rotate the geometry (shape) on the origin.
 * Then apply a translation to the point @param p0.
 * Multiply both matrix for the final transformation. *
 * @param drg The degree for the rotation.
 * @param p0 The translation point.
 * @return The transformation matrix.
 */
static t_mat2	transf_matrix_org(t_vec2 p0, const float drg)
{
	return (mat2_mat2_mult(mat2_translate(p0), mat2_rotate(drg - 90)));
}

/**
 * @brief Draws the geometry of the player using the transformation matrix.
 * @param plr Pointer to the player structure.
 * @param mat The transformation matrix.
 */
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

/**
 * @brief Draws the XY axis of the player on the mini_map image. *
 * @param map Pointer to the map image.
 * @param p0 The origin point for the axis.
 */
static void	draw_xy_axis(mlx_image_t *map, const t_vec2 p0)
{
	const t_color	c = color_hex_alpha(WHITE, A100);
	const int		v_len = map->width;
	const int		h_len = map->height;
	t_line			line_v;
	t_line			line_h;

	line_v = (t_line){{30, p0.y}, {v_len - 30, p0.y}, c, c};
	line_h = (t_line){{p0.x, 30}, {p0.x, h_len - 30}, c, c};
	bresenham(map, &line_v);
	bresenham(map, &line_h);
}
