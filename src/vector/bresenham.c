/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:58:08 by tforster          #+#    #+#             */
/*   Updated: 2024/07/16 21:20:08 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector/bresenham.h"
#include "player/player.h"
#include <stdlib.h>
#include <math.h>

static void	init_ctrl_pts(t_ctrl *ctrl, t_ivec2 iv[2]);
static void	draw_line(mlx_image_t *img, t_ivec2 iv[2], t_ctrl *ctrl, t_color c);
static void	point_in_vp(mlx_image_t *img, t_ivec2 iv[2], t_ctrl *ctrl, t_color c);

// float	dist_2d(t_fvec2 *v0, t_fvec2 *v1)
// {
// 	return (sqrtf(powf(v1->x - v0->x, 2) + powf(v1->y - v0->y, 2)));
// }

void	bresenham(mlx_image_t *img, t_fvec2 fv[2], t_color c)
{
	t_ctrl	ctrl;
	t_ivec2	iv[2];

	iv[0].x = (uint32_t) fv[0].x;
	iv[0].y = (uint32_t) fv[0].y;
	iv[1].x = (uint32_t) fv[1].x;
	iv[1].y = (uint32_t) fv[1].y;

	init_ctrl_pts(&ctrl, iv);
	// ctrl.dist = (float) 1 / dist_2d(v0, v1);
	draw_line(img, iv, &ctrl, c);
}

static void	init_ctrl_pts(t_ctrl *ctrl, t_ivec2 iv[2])
{
	ctrl->dx = abs(iv[1].x - iv[0].x);
	ctrl->sx = (1 * (iv[0].x < iv[1].x) - 1 * (iv[0].x >= iv[1].x));
	ctrl->dy = -abs(iv[1].y - iv[0].y);
	ctrl->sy = (1 * (iv[0].y < iv[1].y) - 1 * (iv[0].y >= iv[1].y));
	ctrl->err = ctrl->dx + ctrl->dy;
	ctrl->dist = 0;
	ctrl->step = 0;
}

static void	draw_line(mlx_image_t *img, t_ivec2 iv[2], t_ctrl *ctrl, t_color c)
{
	while (1)
	{
		point_in_vp(img, iv, ctrl, c);
		if (iv[0].x == iv[1].x
			&& iv[0].y == iv[1].y)
			break ;
		ctrl->e2 = 2 * ctrl->err;
		if (ctrl->e2 >= ctrl->dy)
		{
			if (iv[0].x == iv[1].x)
				break ;
			ctrl->err += ctrl->dy;
			iv[0].x += ctrl->sx;
		}
		if (ctrl->e2 <= ctrl->dx)
		{
			if (iv[0].y == iv[1].y)
				break ;
			ctrl->err += ctrl->dx;
			iv[0].y += ctrl->sy;
		}
	}
}

static void	point_in_vp(mlx_image_t *img, t_ivec2 iv[2], t_ctrl *ctrl, t_color c)
{
	if ((3 <= iv[0].x && iv[0].x < img->width - 3)
		&& (3 <= iv[0].y && iv[0].y < img->height - 3))
	{
		// color = intrplt_color(iv[0]->color, iv[1]->color, ctrl->step);
		// ctrl->step += (ctrl->step <= 1) * ctrl->dist + (ctrl->step > 1) * 1;
		// mlx_put_pixel(img, iv[0].x, iv[0].y, 0xFF0000FF);
		mlx_put_pixel(img, iv[0].x, iv[0].y, c.value);
	}
}
