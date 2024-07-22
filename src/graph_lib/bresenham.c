/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:58:08 by tforster          #+#    #+#             */
/*   Updated: 2024/07/22 17:25:25 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "graph_lib/graph_func.h"

static void	init_ctrl_pts(t_ctrl *ctrl, t_ivec2 *iv0, t_ivec2 *iv1);
static void	draw_line(mlx_image_t *img, t_line *line, t_ctrl *ctrl);
static void	point_in_vp(mlx_image_t *img, t_line *line, t_ctrl *ctrl);

void	bresenham(mlx_image_t *img, t_line *line)
{
	t_ctrl	ctrl;

	init_ctrl_pts(&ctrl, &line->ivec0, &line->ivec1);
	// ctrl.dist = (float) 1 / dist_2d(v0, v1);
	draw_line(img, line, &ctrl);
}

static void	init_ctrl_pts(t_ctrl *ctrl, t_ivec2 *ivec0, t_ivec2 *ivec1)
{
	ctrl->dx = abs(ivec1->x - ivec0->x);
	ctrl->sx = (1 * (ivec0->x < ivec1->x) - 1 * (ivec0->x >= ivec1->x));
	ctrl->dy = -abs(ivec1->y - ivec0->y);
	ctrl->sy = (1 * (ivec0->y < ivec1->y) - 1 * (ivec0->y >= ivec1->y));
	ctrl->err = ctrl->dx + ctrl->dy;
	ctrl->dist = 0;
	ctrl->step = 0;
}

static void	draw_line(mlx_image_t *img, t_line *line, t_ctrl *ctrl)
{
	while (1)
	{
		point_in_vp(img, line, ctrl);
		if (line->ivec0.x == line->ivec1.x
			&& line->ivec0.y == line->ivec1.y)
			break ;
		ctrl->e2 = 2 * ctrl->err;
		if (ctrl->e2 >= ctrl->dy)
		{
			if (line->ivec0.x == line->ivec1.x)
				break ;
			ctrl->err += ctrl->dy;
			line->ivec0.x += ctrl->sx;
		}
		if (ctrl->e2 <= ctrl->dx)
		{
			if (line->ivec0.y == line->ivec1.y)
				break ;
			ctrl->err += ctrl->dx;
			line->ivec0.y += ctrl->sy;
		}
	}
}

static void	point_in_vp(mlx_image_t *img, t_line *line, t_ctrl *ctrl)
{
	(void) ctrl;

	if ((3 <= line->ivec0.x && line->ivec0.x < (int) img->width - 3)
		&& (3 <= line->ivec0.y && line->ivec0.y < (int) img->height - 3))
	{
		// color = intrplt_color_hex_alpha(iv[0]->color, iv[1]->color, ctrl->step);
		// ctrl->step += (ctrl->step <= 1) * ctrl->dist + (ctrl->step > 1) * 1;
		// mlx_put_pixel(img, line->ivec0->x, line->ivec0->y, 0xFF0000FF);
		mlx_put_pixel(img, line->ivec0.x, line->ivec0.y, line->c0.value);
	}
}
