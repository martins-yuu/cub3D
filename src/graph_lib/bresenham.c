/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:58:08 by tforster          #+#    #+#             */
/*   Updated: 2024/08/06 17:15:01 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "graph_lib/graph_func.h"
#include "graph_lib/graph_types.h"

static t_ctrl	init_ctrl_pts(const t_ivec2 ivec0, const t_ivec2 vec1);
static void		draw_line(mlx_image_t *img, t_line *line, t_ctrl *ctrl);
static void		point_in_vp(mlx_image_t *img, t_line *line, t_ctrl *ctrl);

void	bresenham(mlx_image_t *img, t_line *line)
{
	t_ctrl	ctrl;

	ctrl = init_ctrl_pts(line->ivec0, line->ivec1);
	draw_line(img, line, &ctrl);
}

static t_ctrl	init_ctrl_pts(const t_ivec2 ivec0, const t_ivec2 ivec1)
{
	return ((t_ctrl)
		{
			abs(ivec1.x - ivec0.x),
			(1 * (ivec0.x < ivec1.x) - 1 * (ivec0.x >= ivec1.x)),
			-abs(ivec1.y - ivec0.y),
			(1 * (ivec0.y < ivec1.y) - 1 * (ivec0.y >= ivec1.y)),
			abs(ivec1.x - ivec0.x) - abs(ivec1.y - ivec0.y),
			0, 0, 0,
		}
	);
}

static void	draw_line(mlx_image_t *img, t_line *line, t_ctrl *ctrl)
{
	while (true)
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
		mlx_put_pixel(img, line->ivec0.x, line->ivec0.y, line->c0.value);
}
